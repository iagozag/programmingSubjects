#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <random>
#include <iomanip>
#include <filesystem>
#include <chrono>

#include "tree.h"
#include "datagen.h"
#include "oct_model.h"
#include "cart.h"

namespace fs = std::filesystem;

const int Dtrue = 3;
const int K = 2;
const int ntrees = 5;
const double train_ratio = 0.8;
const int Nmin = 1;
const double time_limit = 1200.0;
const double eps = 1e-4;

const std::vector<int> P_vals = {2, 6};
const std::vector<int> N_vals = {100, 200};
const std::vector<double> Alpha_vals = {0.0, -1.0}; // -1 representa 2/n no codigo
const std::vector<int> D_vals = {1, 2, 3};

std::string results_dir = "results";
std::string data_dir = "data";

void ensureDirs() {
    fs::create_directories(results_dir);
    fs::create_directories(data_dir);
}

int main(int argc, char* argv[]) {
    ensureDirs();

    unsigned long seed = 42;
    if (argc > 1) seed = std::stoul(argv[1]);

    std::string res_path = results_dir + "/oct_results.csv";
    std::ofstream res(res_path);

    res << "Dtrue,D,p,n,alpha,tree_instance,"
        << "oct_train_error,oct_val_error,oct_solve_time,oct_optimal,oct_mip_gap,oct_active_branches,"
        << "cart_train_error,cart_val_error,cart_n_branches\n";
    res << std::fixed << std::setprecision(6);

    for (int p : P_vals) {
        for (int n_total : N_vals) {
            for (double alpha_spec : Alpha_vals) {
                double alpha = (alpha_spec < 0.0) ? 2.0 / n_total : alpha_spec;

                for (int tree_inst = 0; tree_inst < ntrees; tree_inst++) {
                    unsigned long inst_seed = seed + (unsigned long)p*1000000UL + (unsigned long)n_total*10000UL + (alpha_spec<0?1:0)*1000UL + tree_inst;
                    std::mt19937 rng(inst_seed);

                    GroundTruthTree gt;
                    gt.generate(Dtrue, p, K, rng);

                    Dataset full = generateDataset(gt, n_total, rng);
                    Dataset train, val;
                    splitDataset(full, train, val, train_ratio, rng);

                    for (int D : D_vals) {
                        OCTParams params;
                        params.D = D;
                        params.Nmin = Nmin;
                        params.alpha = alpha;
                        params.epsilon = eps;
                        params.time_limit = time_limit;

                        // print de inicio da iteracao
                        std::cout << "iniciando: p=" << p << " | n=" << n_total 
                                  << " | alpha=" << alpha << " | arvore=" << tree_inst 
                                  << " | D=" << D << "...\n";

                        OCTSolution oct_sol = solveOCT(train, params);

                        TreeStructure ts;
                        ts.build(D);
                        oct_sol.val_error = oct_sol.computeError(val, ts);

                        int active_branches = 0;
                        for (double dv : oct_sol.d) {
                            if (dv > 0.5) active_branches++;
                        }

                        CARTResult cart_res;
                        try {
                            cart_res = runCART(train, val, D, Nmin);
                        } catch (...) {
                            cart_res.train_error = -1.0;
                            cart_res.val_error = -1.0;
                            cart_res.n_branches = -1;
                        }

                        // print dos resultados comparativos
                        std::string status = oct_sol.optimal ? "otimo" : "tempo limite";
                        std::cout << "  -> oct  [tempo: " << std::setw(6) << oct_sol.solve_time << "s | gap: " 
                                  << std::setw(8) << oct_sol.mip_gap << " | erro val: " << oct_sol.val_error 
                                  << " | status: " << status << "]\n";
                        std::cout << "  -> cart [erro val: " << cart_res.val_error << "]\n\n";

                        res << Dtrue << "," << D << "," << p << "," << n_total << ","
                            << alpha << "," << tree_inst << "," << oct_sol.train_error << ","
                            << oct_sol.val_error << "," << oct_sol.solve_time << ","
                            << (int)oct_sol.optimal << "," << oct_sol.mip_gap << ","
                            << active_branches << "," << cart_res.train_error << ","
                            << cart_res.val_error << "," << cart_res.n_branches << "\n";
                        res.flush();
                    }
                }
            }
        }
    }
    res.close();
    
    std::cout << "experimentos concluidos. resultados salvos em " << res_path << "\n";
    return 0;
}