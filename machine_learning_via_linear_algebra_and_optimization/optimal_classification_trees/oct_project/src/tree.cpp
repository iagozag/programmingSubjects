#include "tree.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

// ─── TreeStructure ───────────────────────────────────────────────────────────

void TreeStructure::build(int depth) {
    D = depth;
    TB.clear();
    TL.clear();
    parent.clear();

    // Complete binary tree: nodes 1 .. 2^(D+1)-1
    int total = (1 << (D + 1)) - 1;
    int first_leaf = 1 << D; // 2^D

    for (int v = 1; v <= total; v++) {
        if (v < first_leaf) TB.push_back(v);
        else                TL.push_back(v);
    }

    // Parent for each branching node
    parent.resize(TB.size(), 0);
    for (int idx = 0; idx < (int)TB.size(); idx++) {
        int m = TB[idx];
        if (m == 1) parent[idx] = 0; // root has no parent
        else        parent[idx] = m / 2;
    }

    // For each leaf, compute AL and AR
    AL.resize(TL.size());
    AR.resize(TL.size());
    for (int ti = 0; ti < (int)TL.size(); ti++) {
        int leaf = TL[ti];
        // Walk from leaf up to root
        int v = leaf;
        while (v > 1) {
            int par = v / 2;
            if (v == 2 * par)     AR[ti].push_back(par); // v is LEFT child of par (right turn taken at par means going to 2*par+1, left is 2*par)
            else                  AL[ti].push_back(par); // v is RIGHT child of par
            v = par;
        }
    }
    // Note: In the standard binary tree numbering:
    //   left child  of m = 2*m
    //   right child of m = 2*m+1
    // A sample goes LEFT at m if a^T x < b_m  (constraint 10: AT(m)(xi+e) <= bm + ...)
    // A sample goes RIGHT at m if a^T x >= b_m (constraint 9)
    // So AR(t) = ancestors where path goes RIGHT = ancestors where leaf is in RIGHT subtree
    //          = ancestors m where TL[ti] is under 2*m+1
    // So if v = 2*par+1 => we came from RIGHT subtree => par in AR
    //    if v = 2*par   => we came from LEFT subtree  => par in AL
    // Redo with correct logic:
    AL.assign(TL.size(), {});
    AR.assign(TL.size(), {});
    for (int ti = 0; ti < (int)TL.size(); ti++) {
        int v = TL[ti];
        while (v > 1) {
            int par = v / 2;
            if (v == 2 * par)         AL[ti].push_back(par); // left child => LEFT branch => par in AL(t)
            else /* v == 2*par+1 */   AR[ti].push_back(par); // right child => RIGHT branch => par in AR(t)
            v = par;
        }
    }

    // For each branching node m, compute set of leaves in its LEFT subtree
    // Left subtree of m: root is 2*m
    leftLeaves.resize(TB.size());
    for (int mi = 0; mi < (int)TB.size(); mi++) {
        int m = TB[mi];
        int left_root = 2 * m;
        // BFS/DFS to collect all leaves under left_root
        std::vector<int> stack = {left_root};
        while (!stack.empty()) {
            int v = stack.back(); stack.pop_back();
            if (v >= first_leaf) {
                // It's a leaf
                int li = leafIndex(v);
                if (li >= 0) leftLeaves[mi].push_back(li);
            } else {
                stack.push_back(2 * v);
                stack.push_back(2 * v + 1);
            }
        }
    }
}

int TreeStructure::leafIndex(int leaf_id) const {
    for (int i = 0; i < (int)TL.size(); i++)
        if (TL[i] == leaf_id) return i;
    return -1;
}

int TreeStructure::branchIndex(int node_id) const {
    for (int i = 0; i < (int)TB.size(); i++)
        if (TB[i] == node_id) return i;
    return -1;
}

// ─── OCTSolution ─────────────────────────────────────────────────────────────

int OCTSolution::predict(const std::vector<double>& x,
                         const TreeStructure& ts,
                         int p,
                         int K) const {
    // Navigate tree from root
    int v = 1;
    int first_leaf = 1 << ts.D;
    while (v < first_leaf) {
        int mi = ts.branchIndex(v);
        // Compute a^T x
        double atx = 0.0;
        for (int j = 0; j < p; j++) atx += a[mi][j] * x[j];
        if (atx >= b[mi]) v = 2 * v + 1; // go RIGHT
        else              v = 2 * v;      // go LEFT
    }
    int ti = ts.leafIndex(v);
    // Find class predicted at this leaf
    for (int k = 0; k < K; k++) {
        if (c[k][ti] > 0.5) return k;
    }
    // Fallback: class 0
    return 0;
}

double OCTSolution::computeError(const Dataset& ds, const TreeStructure& ts) const {
    int wrong = 0;
    for (int i = 0; i < ds.n; i++) {
        int pred = predict(ds.X[i], ts, ds.p, ds.K);
        if (pred != ds.y[i]) wrong++;
    }
    return (double)wrong / ds.n;
}
