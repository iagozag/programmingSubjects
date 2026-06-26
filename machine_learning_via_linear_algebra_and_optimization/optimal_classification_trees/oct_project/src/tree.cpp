#include "tree.h"
#include <stdexcept>
#include <algorithm>
#include <cmath>

void TreeStructure::build(int depth) {
    D = depth;
    TB.clear();
    TL.clear();
    parent.clear();

    int total = (1 << (D + 1)) - 1;
    int first_leaf = 1 << D;

    for (int v = 1; v <= total; v++) {
        if (v < first_leaf) TB.push_back(v);
        else                TL.push_back(v);
    }

    parent.resize(TB.size(), 0);
    for (int idx = 0; idx < (int)TB.size(); idx++) {
        int m = TB[idx];
        if (m == 1) parent[idx] = 0; 
        else        parent[idx] = m / 2;
    }

    AL.assign(TL.size(), {});
    AR.assign(TL.size(), {});
    for (int ti = 0; ti < (int)TL.size(); ti++) {
        int v = TL[ti];
        while (v > 1) {
            int par = v / 2;
            if (v == 2 * par) AL[ti].push_back(par); // ancestral onde fomos a esquerda
            else              AR[ti].push_back(par); // ancestral onde fomos a direita
            v = par;
        }
    }

    // mapeia todas as folhas na subarvore esquerda de cada no interno
    leftLeaves.resize(TB.size());
    for (int mi = 0; mi < (int)TB.size(); mi++) {
        int m = TB[mi];
        int left_root = 2 * m;
        
        std::vector<int> stack = {left_root};
        while (!stack.empty()) {
            int v = stack.back(); stack.pop_back();
            if (v >= first_leaf) {
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
    for (int i = 0; i < (int)TL.size(); i++) {
        if (TL[i] == leaf_id) return i;
    }
    return -1;
}

int TreeStructure::branchIndex(int node_id) const {
    for (int i = 0; i < (int)TB.size(); i++) {
        if (TB[i] == node_id) return i;
    }
    return -1;
}

int OCTSolution::predict(const std::vector<double>& x, const TreeStructure& ts, int p, int K) const {
    int v = 1;
    int first_leaf = 1 << ts.D;
    
    while (v < first_leaf) {
        int mi = ts.branchIndex(v);
        double atx = 0.0;
        for (int j = 0; j < p; j++) atx += a[mi][j] * x[j];
        
        if (atx >= b[mi]) v = 2 * v + 1; // direita
        else              v = 2 * v;     // esquerda
    }
    
    int ti = ts.leafIndex(v);
    for (int k = 0; k < K; k++) {
        if (c[k][ti] > 0.5) return k;
    }
    
    return 0; // fallback default
}

double OCTSolution::computeError(const Dataset& ds, const TreeStructure& ts) const {
    int wrong = 0;
    for (int i = 0; i < ds.n; i++) {
        int pred = predict(ds.X[i], ts, ds.p, ds.K);
        if (pred != ds.y[i]) wrong++;
    }
    return (double)wrong / ds.n;
}