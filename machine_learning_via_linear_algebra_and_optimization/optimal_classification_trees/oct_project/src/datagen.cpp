#include "datagen.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <iostream>

// ─── GroundTruthTree ─────────────────────────────────────────────────────────

void GroundTruthTree::generate(int dtrue, int p_feat, int K_classes, std::mt19937& rng) {
    Dtrue = dtrue;
    p = p_feat;
    K = K_classes;

    ts.build(Dtrue);

    split_feature.resize(ts.TB.size());
    split_threshold.resize(ts.TB.size());
    leaf_class.resize(ts.TL.size());

    std::uniform_int_distribution<int> feat_dist(0, p - 1);
    std::uniform_real_distribution<double> thresh_dist(0.0, 1.0);

    // Assign splits to branching nodes
    for (int mi = 0; mi < (int)ts.TB.size(); mi++) {
        split_feature[mi] = feat_dist(rng);
        split_threshold[mi] = thresh_dist(rng);
    }

    // Assign classes to leaves such that siblings have different classes
    // Process leaves level by level (pairs of siblings)
    std::uniform_int_distribution<int> class_dist(0, K - 1);

    // Initialize all leaves to -1
    std::fill(leaf_class.begin(), leaf_class.end(), -1);

    for (int ti = 0; ti < (int)ts.TL.size(); ti++) {
        int leaf = ts.TL[ti];
        int par = leaf / 2;
        int sibling = (leaf % 2 == 0) ? leaf + 1 : leaf - 1;

        if (leaf % 2 == 0) {
            // This is left child, assign random class
            leaf_class[ti] = class_dist(rng);
        } else {
            // This is right child, must differ from left sibling
            int sibling_idx = ts.leafIndex(sibling);
            int sibling_class = (sibling_idx >= 0) ? leaf_class[sibling_idx] : -1;
            int cls;
            if (K < 2) cls = 0;
            else {
                do { cls = class_dist(rng); } while (cls == sibling_class);
            }
            leaf_class[ti] = cls;
        }
    }
}

int GroundTruthTree::classify(const std::vector<double>& x) const {
    int v = 1;
    int first_leaf = 1 << Dtrue;
    while (v < first_leaf) {
        int mi = ts.branchIndex(v);
        double val = x[split_feature[mi]];
        if (val >= split_threshold[mi]) v = 2 * v + 1; // RIGHT
        else                            v = 2 * v;      // LEFT
    }
    int ti = ts.leafIndex(v);
    return leaf_class[ti];
}

// ─── Dataset Generation ──────────────────────────────────────────────────────

Dataset generateDataset(const GroundTruthTree& gt, int n, std::mt19937& rng) {
    Dataset ds;
    ds.n = n;
    ds.p = gt.p;
    ds.K = gt.K;

    std::uniform_real_distribution<double> uni(0.0, 1.0);
    ds.X.resize(n, std::vector<double>(gt.p));
    ds.y.resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < gt.p; j++) ds.X[i][j] = uni(rng);
        ds.y[i] = gt.classify(ds.X[i]);
    }
    return ds;
}

void splitDataset(const Dataset& full, Dataset& train, Dataset& val,
                  double train_ratio, std::mt19937& rng) {
    int n = full.n;
    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::shuffle(idx.begin(), idx.end(), rng);

    int n_train = (int)(n * train_ratio);
    int n_val   = n - n_train;

    train.n = n_train; train.p = full.p; train.K = full.K;
    val.n   = n_val;   val.p   = full.p; val.K   = full.K;

    train.X.resize(n_train); train.y.resize(n_train);
    val.X.resize(n_val);     val.y.resize(n_val);

    for (int i = 0; i < n_train; i++) {
        train.X[i] = full.X[idx[i]];
        train.y[i] = full.y[idx[i]];
    }
    for (int i = 0; i < n_val; i++) {
        val.X[i] = full.X[idx[n_train + i]];
        val.y[i] = full.y[idx[n_train + i]];
    }
}

void saveDataset(const Dataset& ds, const std::string& filename) {
    std::ofstream f(filename);
    if (!f) throw std::runtime_error("Cannot open file: " + filename);

    // Header: n, p, K on first line
    f << ds.n << "," << ds.p << "," << ds.K << "\n";
    // Each row: x1,x2,...,xp,y
    for (int i = 0; i < ds.n; i++) {
        for (int j = 0; j < ds.p; j++) {
            f << ds.X[i][j];
            if (j < ds.p - 1) f << ",";
        }
        f << "," << ds.y[i] << "\n";
    }
}

Dataset loadDataset(const std::string& filename) {
    std::ifstream f(filename);
    if (!f) throw std::runtime_error("Cannot open file: " + filename);

    std::string line;
    std::getline(f, line);
    std::istringstream hss(line);
    std::string tok;
    std::getline(hss, tok, ','); int n = std::stoi(tok);
    std::getline(hss, tok, ','); int p = std::stoi(tok);
    std::getline(hss, tok, ','); int K = std::stoi(tok);

    Dataset ds;
    ds.n = n; ds.p = p; ds.K = K;
    ds.X.resize(n, std::vector<double>(p));
    ds.y.resize(n);

    for (int i = 0; i < n; i++) {
        std::getline(f, line);
        std::istringstream ss(line);
        for (int j = 0; j < p; j++) {
            std::getline(ss, tok, ',');
            ds.X[i][j] = std::stod(tok);
        }
        std::getline(ss, tok, ',');
        ds.y[i] = std::stoi(tok);
    }
    return ds;
}
