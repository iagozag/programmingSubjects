#ifndef FACT_H
#define FACT_H

#include <utils.h>

class FACT{
    mc root, intervalSize;
    ll B;
    vm factBase;
    int MAX_IT;

    public:
        void initialize(const mc &n);
        void createFB(const mc &n);
        void genSmooth(const mc &n, vm &smooths, vm &xlist);
        Matrix genMat(const vm &smooth, const mc &n);
        void gauss(vector<vm> &a, vector<bool> &ans);
        vector<int> find_dep(const pair<vm, int> &solution, Matrix &mat, vector<bool> &flagged);
        bool quadSieve(const mc &n, mc &fact1, mc &fact2);
};

#endif // FACT_H

