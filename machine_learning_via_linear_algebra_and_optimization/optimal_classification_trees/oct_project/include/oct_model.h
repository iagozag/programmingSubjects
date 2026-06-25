#pragma once
#include "tree.h"
#include "datagen.h"

// Parameters for the OCT model
struct OCTParams {
    int D;          // max depth for the model
    int Nmin;       // minimum samples per leaf
    double alpha;   // complexity penalty
    double epsilon; // small epsilon for strict inequality (default 1e-4)
    double time_limit; // seconds (default 1200 = 20 min)
};

// Solve the OCT model using CPLEX
// Returns the solution (or best found within time limit)
OCTSolution solveOCT(const Dataset& train,
                     const OCTParams& params);
