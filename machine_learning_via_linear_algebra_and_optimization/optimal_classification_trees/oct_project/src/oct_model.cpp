#include "oct_model.h"
#include <ilcplex/ilocplex.h>
#include <chrono>
#include <iostream>
#include <cmath>
#include <algorithm>

ILOSTLBEGIN

OCTSolution solveOCT(const Dataset& train, const OCTParams& params) {
    int n = train.n;
    int p = train.p;
    int K = train.K;
    int D = params.D;
    int Nmin = params.Nmin;
    double alpha = params.alpha;
    double eps = params.epsilon;
    double time_lim = params.time_limit;

    // encontra o valor maximo nos dados para usar no big-m da restricao 10
    double x_max = 0.0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            if (train.X[i][j] > x_max) x_max = train.X[i][j];
        }
    }

    TreeStructure ts;
    ts.build(D);
    int nTB = ts.TB.size();
    int nTL = ts.TL.size();

    IloEnv env;
    OCTSolution sol;
    sol.D = D;

    try {
        IloModel model(env);

        IloArray<IloBoolVarArray> a(env, nTB);
        for (int mi = 0; mi < nTB; mi++) {
            a[mi] = IloBoolVarArray(env, p);
            for (int j = 0; j < p; j++) a[mi][j] = IloBoolVar(env);
        }

        IloNumVarArray b(env, nTB, 0.0, 1.0, ILOFLOAT);
        IloBoolVarArray d(env, nTB);

        IloArray<IloBoolVarArray> z(env, n);
        for (int i = 0; i < n; i++) {
            z[i] = IloBoolVarArray(env, nTL);
            for (int ti = 0; ti < nTL; ti++) z[i][ti] = IloBoolVar(env);
        }

        IloBoolVarArray l(env, nTL);
        IloArray<IloBoolVarArray> c(env, K);
        for (int k = 0; k < K; k++) {
            c[k] = IloBoolVarArray(env, nTL);
            for (int ti = 0; ti < nTL; ti++) c[k][ti] = IloBoolVar(env);
        }

        IloArray<IloNumVarArray> Nkt(env, K);
        for (int k = 0; k < K; k++) {
            Nkt[k] = IloNumVarArray(env, nTL, 0.0, n, ILOFLOAT);
        }

        IloNumVarArray Nt(env, nTL, 0.0, n, ILOFLOAT);
        IloNumVarArray Lt(env, nTL, 0.0, n, ILOFLOAT);

        // funcao objetivo
        IloExpr obj(env);
        double Lhat = (double)n;
        for (int ti = 0; ti < nTL; ti++) obj += Lt[ti];
        obj /= Lhat;
        for (int mi = 0; mi < nTB; mi++) obj += alpha * d[mi];
        model.add(IloMinimize(env, obj));
        obj.end();

        // restricoes estruturais 2, 3, e 5
        for (int mi = 0; mi < nTB; mi++) {
            IloExpr sum_a(env);
            for (int j = 0; j < p; j++) sum_a += a[mi][j];
            model.add(d[mi] == sum_a);
            sum_a.end();
            
            model.add(b[mi] <= d[mi]);

            int m = ts.TB[mi];
            if (m != 1) { // no nao eh raiz
                int par = ts.parent[mi];
                int pi = ts.branchIndex(par);
                model.add(d[mi] <= d[pi]);
            }
        }

        // restricoes de designacao 6, 7, 8
        for (int i = 0; i < n; i++) {
            IloExpr sum_z(env);
            for (int ti = 0; ti < nTL; ti++) {
                sum_z += z[i][ti];
                model.add(z[i][ti] <= l[ti]);
            }
            model.add(sum_z == 1);
            sum_z.end();
        }

        for (int ti = 0; ti < nTL; ti++) {
            IloExpr sum_z(env);
            for (int i = 0; i < n; i++) sum_z += z[i][ti];
            model.add((double)Nmin * l[ti] <= sum_z);
            sum_z.end();
        }

        // restricao de roteamento 9 (ramificacao direita)
        for (int ti = 0; ti < nTL; ti++) {
            for (int m : ts.AR[ti]) {
                int mi = ts.branchIndex(m);
                for (int i = 0; i < n; i++) {
                    IloExpr lhs(env);
                    for (int j = 0; j < p; j++) lhs += a[mi][j] * train.X[i][j];
                    lhs += (1.0 - z[i][ti]);
                    model.add(lhs >= b[mi]);
                    lhs.end();
                }
            }
        }

        // restricao de roteamento 10 (ramificacao esquerda - linearizada)
        double M10 = 1.0 + x_max;
        for (int ti = 0; ti < nTL; ti++) {
            for (int m : ts.AL[ti]) {
                int mi = ts.branchIndex(m);
                for (int i = 0; i < n; i++) {
                    IloExpr lhs(env);
                    for (int j = 0; j < p; j++) {
                        lhs += a[mi][j] * (train.X[i][j] + eps);
                    }
                    model.add(lhs <= b[mi] + M10 * (1.0 - z[i][ti]));
                    lhs.end();
                }
            }
        }

        // restricao 11 (forca no a ser ativo se amostra cai em folha a esquerda)
        for (int mi = 0; mi < nTB; mi++) {
            for (int i = 0; i < n; i++) {
                IloExpr rhs(env);
                for (int tl_idx : ts.leftLeaves[mi]) rhs += z[i][tl_idx];
                model.add(d[mi] >= rhs);
                rhs.end();
            }
        }

        // contagem e classificacao 12, 13, 14
        for (int ti = 0; ti < nTL; ti++) {
            IloExpr sum_z_tot(env);
            for (int i = 0; i < n; i++) sum_z_tot += z[i][ti];
            model.add(Nt[ti] == sum_z_tot);
            sum_z_tot.end();

            for (int k = 0; k < K; k++) {
                IloExpr sum_z_k(env);
                for (int i = 0; i < n; i++) {
                    if (train.y[i] == k) sum_z_k += z[i][ti];
                }
                model.add(Nkt[k][ti] == sum_z_k);
                sum_z_k.end();
            }

            IloExpr sum_c(env);
            for (int k = 0; k < K; k++) sum_c += c[k][ti];
            model.add(l[ti] == sum_c);
            sum_c.end();
        }

        // limites de perda 15, 16
        for (int ti = 0; ti < nTL; ti++) {
            for (int k = 0; k < K; k++) {
                model.add(Lt[ti] >= Nt[ti] - Nkt[k][ti] - (double)n * (1.0 - c[k][ti]));
                model.add(Lt[ti] <= Nt[ti] - Nkt[k][ti] + (double)n * c[k][ti]);
            }
        }

        IloCplex cplex(model);
        cplex.setParam(IloCplex::Param::TimeLimit, time_lim);
        cplex.setParam(IloCplex::Param::Threads, 4);
        cplex.setParam(IloCplex::Param::MIP::Tolerances::MIPGap, 1e-4);
        cplex.setParam(IloCplex::Param::MIP::Display, 0);
        cplex.setParam(IloCplex::Param::Simplex::Display, 0);

        auto t_start = std::chrono::steady_clock::now();
        bool solved = cplex.solve();
        auto t_end = std::chrono::steady_clock::now();
        sol.solve_time = std::chrono::duration<double>(t_end - t_start).count();

        IloCplex::CplexStatus status = cplex.getCplexStatus();
        sol.optimal = (status == IloCplex::Optimal);
        sol.mip_gap = solved ? cplex.getMIPRelativeGap() : 1.0;
        sol.obj_value = solved ? cplex.getObjValue() : -1.0;

        sol.a.resize(nTB, std::vector<double>(p, 0.0));
        sol.b.resize(nTB, 0.0);
        sol.d.resize(nTB, 0.0);
        sol.c.resize(K, std::vector<double>(nTL, 0.0));
        sol.l.resize(nTL, 0.0);

        if (solved && cplex.getSolnPoolNsolns() >= 0) {
            for (int mi = 0; mi < nTB; mi++) {
                sol.d[mi] = cplex.getValue(d[mi]);
                sol.b[mi] = cplex.getValue(b[mi]);
                for (int j = 0; j < p; j++) sol.a[mi][j] = cplex.getValue(a[mi][j]);
            }
            for (int ti = 0; ti < nTL; ti++) {
                sol.l[ti] = cplex.getValue(l[ti]);
                for (int k = 0; k < K; k++) sol.c[k][ti] = cplex.getValue(c[k][ti]);
            }
        } else if (!solved) {
            // gera solucao trivial para evitar quebra no teste de validacao fora de tempo
            sol.d[0] = 0.0;
            for (int ti = 0; ti < nTL; ti++) {
                sol.l[ti] = 0.0;
                sol.c[0][ti] = 1.0; 
            }
        }

        sol.train_error = sol.computeError(train, ts);
        sol.val_error = -1.0; 

    } catch (IloException& e) {
        std::cerr << "excecao cplex: " << e.getMessage() << "\n";
        env.end();
        throw;
    }

    env.end();
    return sol;
}