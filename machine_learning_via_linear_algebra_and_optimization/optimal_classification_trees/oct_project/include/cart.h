#pragma once
#include "tree.h"

// Run CART (sklearn DecisionTreeClassifier) via Python subprocess
// Writes train/val data to temp CSV, calls python script, reads back errors
struct CARTResult {
    double train_error;
    double val_error;
    int n_branches; // number of internal nodes used
};

CARTResult runCART(const Dataset& train,
                   const Dataset& val,
                   int max_depth,
                   int min_samples_leaf);
