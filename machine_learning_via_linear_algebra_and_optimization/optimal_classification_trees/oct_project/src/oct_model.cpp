#include "oct_model.h"
#include <ilcplex/ilocplex.h>
#include <chrono>
#include <iostream>
#include <cmath>
#include <algorithm>

ILOSTLBEGIN

OCTSolution solveOCT(const Dataset& train, const OCTParams& params) {
    int n  = train.n;
    int p  = train.p;
    int K  = train.K;
    int D  = params.D;
    int Nmin = params.Nmin;
    double alpha   = params.alpha;
    double eps     = params.epsilon;
    double time_lim = params.time_limit;

    // ── Compute epsilon_max = max over j,i of x[i][j] ──
    double x_max = 0.0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p; j++)
            if (train.X[i][j] > x_max) x_max = train.X[i][j];

    // Build tree structure
    TreeStructure ts;
    ts.build(D);
    int nTB = ts.TB.size();
    int nTL = ts.TL.size();

    IloEnv env;
    OCTSolution sol;
    sol.D = D;

    try {
        IloModel model(env);

        // ── Decision Variables ──────────────────────────────────────────────

        // a[m][j]: binary, feature j used at branching node m
        IloArray<IloBoolVarArray> a(env, nTB);
        for (int mi = 0; mi < nTB; mi++) {
            a[mi] = IloBoolVarArray(env, p);
            for (int j = 0; j < p; j++) {
                char name[64]; sprintf(name, "a_%d_%d", ts.TB[mi], j);
                a[mi][j] = IloBoolVar(env, name);
            }
        }

        // b[m]: continuous in [0,1], threshold at branching node m
        IloNumVarArray b(env, nTB, 0.0, 1.0, ILOFLOAT);
        for (int mi = 0; mi < nTB; mi++) {
            char name[64]; sprintf(name, "b_%d", ts.TB[mi]);
            b[mi].setName(name);
        }

        // d[m]: binary, branching node m is active
        IloBoolVarArray d(env, nTB);
        for (int mi = 0; mi < nTB; mi++) {
            char name[64]; sprintf(name, "d_%d", ts.TB[mi]);
            d[mi] = IloBoolVar(env, name);
        }

        // z[i][t]: binary, sample i assigned to leaf t
        IloArray<IloBoolVarArray> z(env, n);
        for (int i = 0; i < n; i++) {
            z[i] = IloBoolVarArray(env, nTL);
            for (int ti = 0; ti < nTL; ti++) {
                char name[64]; sprintf(name, "z_%d_%d", i, ts.TL[ti]);
                z[i][ti] = IloBoolVar(env, name);
            }
        }

        // l[t]: binary, leaf t is active (has at least Nmin samples)
        IloBoolVarArray l(env, nTL);
        for (int ti = 0; ti < nTL; ti++) {
            char name[64]; sprintf(name, "l_%d", ts.TL[ti]);
            l[ti] = IloBoolVar(env, name);
        }

        // c[k][t]: binary, leaf t predicts class k
        IloArray<IloBoolVarArray> c(env, K);
        for (int k = 0; k < K; k++) {
            c[k] = IloBoolVarArray(env, nTL);
            for (int ti = 0; ti < nTL; ti++) {
                char name[64]; sprintf(name, "c_%d_%d", k, ts.TL[ti]);
                c[k][ti] = IloBoolVar(env, name);
            }
        }

        // Nkt[k][t]: continuous, count of class-k samples at leaf t
        IloArray<IloNumVarArray> Nkt(env, K);
        for (int k = 0; k < K; k++) {
            Nkt[k] = IloNumVarArray(env, nTL, 0.0, n, ILOFLOAT);
            for (int ti = 0; ti < nTL; ti++) {
                char name[64]; sprintf(name, "Nkt_%d_%d", k, ts.TL[ti]);
                Nkt[k][ti].setName(name);
            }
        }

        // Nt[t]: continuous, total samples at leaf t
        IloNumVarArray Nt(env, nTL, 0.0, n, ILOFLOAT);
        for (int ti = 0; ti < nTL; ti++) {
            char name[64]; sprintf(name, "Nt_%d", ts.TL[ti]);
            Nt[ti].setName(name);
        }

        // Lt[t]: continuous, misclassification count at leaf t
        IloNumVarArray Lt(env, nTL, 0.0, n, ILOFLOAT);
        for (int ti = 0; ti < nTL; ti++) {
            char name[64]; sprintf(name, "Lt_%d", ts.TL[ti]);
            Lt[ti].setName(name);
        }

        // ── Objective (1) ────────────────────────────────────────────────────
        // min (1/Lhat) * sum_t Lt  +  alpha * sum_m dm
        // Lhat = n (upper bound on total misclassification)
        IloExpr obj(env);
        double Lhat = (double)n;
        for (int ti = 0; ti < nTL; ti++) obj += Lt[ti];
        obj /= Lhat;
        for (int mi = 0; mi < nTB; mi++) obj += alpha * d[mi];
        model.add(IloMinimize(env, obj));
        obj.end();

        // ── Constraints ──────────────────────────────────────────────────────

        // (2) dm = sum_j ajm   for m in TB
        for (int mi = 0; mi < nTB; mi++) {
            IloExpr sum_a(env);
            for (int j = 0; j < p; j++) sum_a += a[mi][j];
            model.add(d[mi] == sum_a);
            sum_a.end();
        }

        // (3) bm <= dm  for m in TB
        for (int mi = 0; mi < nTB; mi++)
            model.add(b[mi] <= d[mi]);

        // (4) 0 <= bm  (already enforced by variable bounds)

        // (5) dm <= d_{p(m)}  for m in TB \ {root}
        for (int mi = 0; mi < nTB; mi++) {
            int m = ts.TB[mi];
            if (m == 1) continue; // root has no parent
            int par = ts.parent[mi];
            int pi = ts.branchIndex(par);
            model.add(d[mi] <= d[pi]);
        }

        // (6) sum_t zit = 1  for i in [n]
        for (int i = 0; i < n; i++) {
            IloExpr sum_z(env);
            for (int ti = 0; ti < nTL; ti++) sum_z += z[i][ti];
            model.add(sum_z == 1);
            sum_z.end();
        }

        // (7) zit <= lt  for i in [n], t in TL
        for (int i = 0; i < n; i++)
            for (int ti = 0; ti < nTL; ti++)
                model.add(z[i][ti] <= l[ti]);

        // (8) Nmin * lt <= sum_i zit  for t in TL
        for (int ti = 0; ti < nTL; ti++) {
            IloExpr sum_z(env);
            for (int i = 0; i < n; i++) sum_z += z[i][ti];
            model.add((double)Nmin * l[ti] <= sum_z);
            sum_z.end();
        }

        // (9) a^T xi >= bm - (1 - zit)  for m in AR(t), i in [n], t in TL
        //    => a^T xi + (1 - zit) >= bm
        //    => sum_j ajm * xi[j] + 1 - zit >= bm
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

        // (10) a^T (xi + eps) <= bm + (1 + eps_max)(1 - zit)  for m in AL(t), i in [n], t in TL
        //    => sum_j ajm*(xi[j]+eps) <= bm + (1+eps_max)*(1-zit)
        //    since sum_j ajm = dm and dm in {0,1}, sum_j ajm*eps = eps*dm
        //    But dm = sum_j ajm, and since ajm in {0,1} and sum_j ajm in {0,1}:
        //    => sum_j ajm*(xi[j]+eps) = sum_j ajm*xi[j] + eps*sum_j ajm
        //    = a^T xi + eps * dm  (linearized via a[mi][j])
        // We write: sum_j a[mi][j]*(xi[j] + eps) <= bm + (1+eps_max)*(1-zit)
        double M10 = 1.0 + x_max; // upper bound
        for (int ti = 0; ti < nTL; ti++) {
            for (int m : ts.AL[ti]) {
                int mi = ts.branchIndex(m);
                for (int i = 0; i < n; i++) {
                    IloExpr lhs(env);
                    for (int j = 0; j < p; j++)
                        lhs += a[mi][j] * (train.X[i][j] + eps);
                    model.add(lhs <= b[mi] + M10 * (1.0 - z[i][ti]));
                    lhs.end();
                }
            }
        }

        // (11) dm >= sum_{t in T^esq_L(m)} zit  for m in TB, i in [n]
        // i.e., if any sample is assigned to a left-subtree leaf of m, m must be active
        // (one constraint per (m, i))
        for (int mi = 0; mi < nTB; mi++) {
            for (int i = 0; i < n; i++) {
                IloExpr rhs(env);
                for (int tl_idx : ts.leftLeaves[mi])
                    rhs += z[i][tl_idx];
                model.add(d[mi] >= rhs);
                rhs.end();
            }
        }

        // (12) Nkt = sum_{i: yi=k} zit  for k in [K], t in TL
        for (int k = 0; k < K; k++) {
            for (int ti = 0; ti < nTL; ti++) {
                IloExpr sum_z(env);
                for (int i = 0; i < n; i++)
                    if (train.y[i] == k) sum_z += z[i][ti];
                model.add(Nkt[k][ti] == sum_z);
                sum_z.end();
            }
        }

        // (13) Nt = sum_i zit  for t in TL
        for (int ti = 0; ti < nTL; ti++) {
            IloExpr sum_z(env);
            for (int i = 0; i < n; i++) sum_z += z[i][ti];
            model.add(Nt[ti] == sum_z);
            sum_z.end();
        }

        // (14) lt = sum_k ckt  for t in TL
        for (int ti = 0; ti < nTL; ti++) {
            IloExpr sum_c(env);
            for (int k = 0; k < K; k++) sum_c += c[k][ti];
            model.add(l[ti] == sum_c);
            sum_c.end();
        }

        // (15) Lt >= Nt - Nkt - n*(1-ckt)  for t in TL, k in [K]
        for (int ti = 0; ti < nTL; ti++) {
            for (int k = 0; k < K; k++) {
                model.add(Lt[ti] >= Nt[ti] - Nkt[k][ti] - (double)n * (1.0 - c[k][ti]));
            }
        }

        // (16) Lt <= Nt - Nkt + n*ckt  for t in TL, k in [K]
        for (int ti = 0; ti < nTL; ti++) {
            for (int k = 0; k < K; k++) {
                model.add(Lt[ti] <= Nt[ti] - Nkt[k][ti] + (double)n * c[k][ti]);
            }
        }

        // (17) Lt >= 0  (enforced by variable bound)

        // ── Solve ─────────────────────────────────────────────────────────────
        IloCplex cplex(model);
        cplex.setParam(IloCplex::Param::TimeLimit, time_lim);
        cplex.setParam(IloCplex::Param::Threads, 4);
        cplex.setParam(IloCplex::Param::MIP::Tolerances::MIPGap, 1e-4);
        // Suppress output (set to 0 for verbose)
        cplex.setParam(IloCplex::Param::MIP::Display, 0);
        cplex.setParam(IloCplex::Param::Simplex::Display, 0);

        auto t_start = std::chrono::steady_clock::now();
        bool solved = cplex.solve();
        auto t_end   = std::chrono::steady_clock::now();
        sol.solve_time = std::chrono::duration<double>(t_end - t_start).count();

        IloCplex::CplexStatus status = cplex.getCplexStatus();
        sol.optimal = (status == IloCplex::Optimal);
        sol.mip_gap = solved ? cplex.getMIPRelativeGap() : 1.0;
        sol.obj_value = solved ? cplex.getObjValue() : -1.0;

        // ── Extract Solution ──────────────────────────────────────────────────
        sol.a.resize(nTB, std::vector<double>(p, 0.0));
        sol.b.resize(nTB, 0.0);
        sol.d.resize(nTB, 0.0);
        sol.c.resize(K, std::vector<double>(nTL, 0.0));
        sol.l.resize(nTL, 0.0);

        if (solved && cplex.getSolnPoolNsolns() >= 0) {
            for (int mi = 0; mi < nTB; mi++) {
                sol.d[mi] = cplex.getValue(d[mi]);
                sol.b[mi] = cplex.getValue(b[mi]);
                for (int j = 0; j < p; j++)
                    sol.a[mi][j] = cplex.getValue(a[mi][j]);
            }
            for (int ti = 0; ti < nTL; ti++) {
                sol.l[ti] = cplex.getValue(l[ti]);
                for (int k = 0; k < K; k++)
                    sol.c[k][ti] = cplex.getValue(c[k][ti]);
            }
        } else if (!solved) {
            // No solution found at all – return trivial solution (predict class 0 everywhere)
            std::cerr << "[OCT] No feasible solution found within time limit.\n";
            // Set up trivial leaf: all samples go to leaf 1 (first leaf), class 0
            // This is just to avoid crashing; errors will be reported
            sol.d[0] = 0.0;
            for (int ti = 0; ti < nTL; ti++) {
                sol.l[ti] = 0.0;
                sol.c[0][ti] = 1.0; // predict class 0
            }
        }

        // Compute train error from solution
        sol.train_error = sol.computeError(train, ts);
        sol.val_error   = -1.0; // to be computed externally with val set

    } catch (IloException& e) {
        std::cerr << "CPLEX exception: " << e.getMessage() << "\n";
        env.end();
        throw;
    }

    env.end();
    return sol;
}
