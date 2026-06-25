#pragma once
#include <vector>
#include <string>
#include <set>

// ─── Tree Node Sets ─────────────────────────────────────────────────────────
// For a complete binary tree of depth D:
//   nodes are numbered 1..2^(D+1)-1
//   TB (branching nodes): 1..2^D - 1
//   TL (leaf nodes):      2^D .. 2^(D+1) - 1

struct TreeStructure {
    int D;                         // max depth
    std::vector<int> TB;           // branching node ids
    std::vector<int> TL;           // leaf node ids
    // For each leaf t, ancestors on left and right path
    std::vector<std::vector<int>> AL; // AL[t_idx] = list of ancestor branching nodes where path goes LEFT
    std::vector<std::vector<int>> AR; // AR[t_idx] = list of ancestor branching nodes where path goes RIGHT
    // parent of each branching node (except root)
    std::vector<int> parent;       // parent[m_idx] = parent id (1-indexed), 0 if root
    // For each branching node m, set of leaves in its LEFT subtree
    std::vector<std::vector<int>> leftLeaves; // leftLeaves[m_idx] = leaf indices (into TL) in left subtree of m

    void build(int depth);
    int leafIndex(int leaf_id) const;
    int branchIndex(int node_id) const;
};

// ─── Dataset ─────────────────────────────────────────────────────────────────
struct Dataset {
    int n;        // number of samples
    int p;        // number of features
    int K;        // number of classes
    std::vector<std::vector<double>> X; // X[i][j] in [0,1]
    std::vector<int> y;                 // y[i] in {0,...,K-1}
};

// ─── OCT Solution ────────────────────────────────────────────────────────────
struct OCTSolution {
    // a[m_idx][j] = 1 if feature j is used at branching node m
    std::vector<std::vector<double>> a;
    // b[m_idx] = threshold at branching node m
    std::vector<double> b;
    // d[m_idx] = 1 if branching node m is active
    std::vector<double> d;
    // c[k][t_idx] = 1 if leaf t predicts class k
    std::vector<std::vector<double>> c;
    // l[t_idx] = 1 if leaf t is active
    std::vector<double> l;

    double obj_value;
    double train_error;
    double val_error;
    double solve_time;
    bool optimal;
    double mip_gap;
    int D;

    // Predict class for a single sample
    int predict(const std::vector<double>& x, const TreeStructure& ts, int p, int K) const;
    // Compute error on a dataset
    double computeError(const Dataset& ds, const TreeStructure& ts) const;
};

// ─── Experiment Result ───────────────────────────────────────────────────────
struct ExperimentResult {
    int D, p, n;
    double alpha;
    int tree_instance;
    // OCT stats
    double oct_train_error;
    double oct_val_error;
    double solve_time;
    bool optimal;
    double mip_gap;
    // CART stats
    double cart_train_error;
    double cart_val_error;
    int oct_active_branches; // number of active branching nodes in OCT solution
};
