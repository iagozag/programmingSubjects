#ifndef SEGTREE_H
#define SEGTREE_H

#include "matrix.h"

class Segtree{
    private:
        Matrix* seg;
        int length_;
    public:
        Segtree(int l);

        ~Segtree();

        Matrix update(int node, int tl, int tr, int idx, Matrix& mat);

        Matrix query(int node, int tl, int tr, int a, int b);
};

#endif
