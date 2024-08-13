#ifndef FACT_H
#define FACT_H

#include <utils.h>

const long long INF = 0x3f3f3f3f3f3f3f3fll;

class FACT{
    mc root;
    ll B;
    mc intervalSize;
    vm factBase;
    int MAX_IT;

    public:
        void initialize(const mc &n);
        bool quadSieve(const mc &n, mc &fact1, mc &fact2);
        void createFB(const mc &n);
        void genSmooth(const mc &n, vm &smooths, vm &xlist);
        Matrix genMat(const vm &smooth, const mc &n);
        void gauss(vector<vm> &a, vm& ans);
        vector<int> find_dep(const pair<vm, int> &solution, Matrix &mat, vm &flagged);

};

#endif // FACT_H

