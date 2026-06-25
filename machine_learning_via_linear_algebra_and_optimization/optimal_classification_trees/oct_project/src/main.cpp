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

// ─── Experiment Parameters ───────────────────────────────────────────────────
const int    Dtrue    = 3;
const int    K        = 2;
const int    ntrees   = 5;
const double train_ratio = 0.8;
const int    Nmin     = 1;
const double time_limit = 1200.0; // 20 minutes
const double eps      = 1e-4;

const std::vector<int>    P_vals     = {2, 6};
const std::vector<int>    N_vals     = {100, 200};
const std::vector<double> Alpha_vals = {0.0, -1.0}; // -1 means alpha = 2/n (set at runtime)
const std::vector<int>    D_vals     = {1, 2, 3};   // D = 1..Dtrue

// ─── Helpers ─────────────────────────────────────────────────────────────────
std::string results_dir = "results";
std::string data_dir    = "data";

void ensureDirs() {
    fs::create_directories(results_dir);
    fs::create_directories(data_dir);
}

int main(int argc, char* argv[]) {
    ensureDirs();

    // Seed: use command-line arg or default
    unsigned long seed = 42;
    if (argc > 1) seed = std::stoul(argv[1]);

    // Open results CSV
    std::string res_path = results_dir + "/oct_results.csv";
    std::ofstream res(res_path);
    if (!res) { std::cerr << "Cannot open " << res_path << "\n"; return 1; }

    // CSV header
    res << "Dtrue,D,p,n,alpha,tree_instance,"
        << "oct_train_error,oct_val_error,oct_solve_time,oct_optimal,oct_mip_gap,oct_active_branches,"
        << "cart_train_error,cart_val_error,cart_n_branches\n";
    res << std::fixed << std::setprecision(6);

    std::cout << "=== Optimal Classification Tree Experiments ===\n";
    std::cout << "Dtrue=" << Dtrue << ", K=" << K << ", ntrees=" << ntrees
              << ", time_limit=" << time_limit << "s\n\n";

    int total_runs = 0;
    int total_optimal = 0;

    for (int p : P_vals) {
        for (int n_total : N_vals) {
            for (double alpha_spec : Alpha_vals) {
                double alpha = (alpha_spec < 0.0) ? 2.0 / n_total : alpha_spec;

                std::cout << "─── p=" << p << " n=" << n_total
                          << " alpha=" << alpha << " ───\n";

                for (int tree_inst = 0; tree_inst < ntrees; tree_inst++) {
                    // Unique seed per configuration + instance
                    unsigned long inst_seed = seed
                        + (unsigned long)p * 1000000UL
                        + (unsigned long)n_total * 10000UL
                        + (unsigned long)(alpha_spec < 0 ? 1 : 0) * 1000UL
                        + (unsigned long)tree_inst;
                    std::mt19937 rng(inst_seed);

                    // Generate ground-truth tree and dataset
                    GroundTruthTree gt;
                    gt.generate(Dtrue, p, K, rng);

                    Dataset full = generateDataset(gt, n_total, rng);
                    Dataset train, val;
                    splitDataset(full, train, val, train_ratio, rng);

                    // Save dataset for reference
                    std::string ds_path = data_dir + "/ds_p" + std::to_string(p)
                        + "_n" + std::to_string(n_total)
                        + "_a" + (alpha_spec < 0 ? "2n" : "0")
                        + "_t" + std::to_string(tree_inst);
                    saveDataset(train, ds_path + "_train.csv");
                    saveDataset(val,   ds_path + "_val.csv");

                    // Solve for each D
                    for (int D : D_vals) {
                        std::cout << "  D=" << D
                                  << " inst=" << tree_inst << " ... " << std::flush;

                        // ── OCT Model ──────────────────────────────────────
                        OCTParams params;
                        params.D          = D;
                        params.Nmin       = Nmin;
                        params.alpha      = alpha;
                        params.epsilon    = eps;
                        params.time_limit = time_limit;

                        OCTSolution oct_sol;
                        try {
                            oct_sol = solveOCT(train, params);
                        } catch (std::exception& e) {
                            std::cerr << "\n[ERROR] OCT failed: " << e.what() << "\n";
                            continue;
                        }

                        // Compute validation error using OCT solution
                        TreeStructure ts;
                        ts.build(D);
                        oct_sol.val_error = oct_sol.computeError(val, ts);

                        // Count active branching nodes
                        int active_branches = 0;
                        for (double dv : oct_sol.d)
                            if (dv > 0.5) active_branches++;

                        total_runs++;
                        if (oct_sol.optimal) total_optimal++;

                        std::cout << "OCT train=" << oct_sol.train_error
                                  << " val=" << oct_sol.val_error
                                  << " time=" << std::setprecision(1) << oct_sol.solve_time
                                  << "s opt=" << oct_sol.optimal;

                        // ── CART ───────────────────────────────────────────
                        CARTResult cart_res;
                        try {
                            cart_res = runCART(train, val, D, Nmin);
                        } catch (std::exception& e) {
                            std::cerr << "\n[ERROR] CART failed: " << e.what() << "\n";
                            cart_res.train_error = -1.0;
                            cart_res.val_error   = -1.0;
                            cart_res.n_branches  = -1;
                        }

                        std::cout << " | CART train=" << std::setprecision(6)
                                  << cart_res.train_error
                                  << " val=" << cart_res.val_error << "\n";

                        // ── Write to CSV ────────────────────────────────────
                        res << Dtrue << ","
                            << D << ","
                            << p << ","
                            << n_total << ","
                            << alpha << ","
                            << tree_inst << ","
                            << oct_sol.train_error << ","
                            << oct_sol.val_error << ","
                            << oct_sol.solve_time << ","
                            << (int)oct_sol.optimal << ","
                            << oct_sol.mip_gap << ","
                            << active_branches << ","
                            << cart_res.train_error << ","
                            << cart_res.val_error << ","
                            << cart_res.n_branches << "\n";
                        res.flush();
                    } // D loop
                } // tree_inst loop
            } // alpha loop
        } // n loop
    } // p loop

    res.close();

    std::cout << "\n=== Summary ===\n";
    std::cout << "Total OCT runs: " << total_runs << "\n";
    std::cout << "Solved to optimality: " << total_optimal
              << " (" << (total_runs > 0 ? 100.0 * total_optimal / total_runs : 0.0)
              << "%)\n";
    std::cout << "Results saved to: " << res_path << "\n";

    return 0;
}
