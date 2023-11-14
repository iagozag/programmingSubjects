#ifndef SEGTREE_H
#define SEGTREE_H

#include "utils.h"

class Segtree{
    private:
        Matrix* seg;
    public:
        Segtree(int length);

        ~Segtree();

        Matrix update(int node, int tl, int tr, int idx, Matrix& mat);

        Matrix query(int node, int tl, int tr, int a, int b);

        void printSegTree(); 
};

#endif
