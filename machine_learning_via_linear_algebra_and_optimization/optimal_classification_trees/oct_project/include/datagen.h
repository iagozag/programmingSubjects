#pragma once
#include "tree.h"
#include <random>

// Generate a random ground-truth classification tree of depth Dtrue with p features and K classes
// Returns the tree splits (aj[m], bm) and leaf labels
struct GroundTruthTree {
    int Dtrue;
    int p;
    int K;
    // For each branching node m (1-indexed, stored at index m-1):
    std::vector<int> split_feature;  // which feature j is used (0-indexed)
    std::vector<double> split_threshold;
    // For each leaf t (1-indexed via TL): class label
    std::vector<int> leaf_class;

    TreeStructure ts;

    void generate(int Dtrue, int p, int K, std::mt19937& rng);
    int classify(const std::vector<double>& x) const;
};

// Split dataset into train/val (80/20)
void splitDataset(const Dataset& full,
                  Dataset& train,
                  Dataset& val,
                  double train_ratio,
                  std::mt19937& rng);

// Generate full dataset from a ground truth tree
Dataset generateDataset(const GroundTruthTree& gt, int n, std::mt19937& rng);

// Save dataset to CSV
void saveDataset(const Dataset& ds, const std::string& filename);


