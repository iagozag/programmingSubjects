#ifndef SEGTREE_H
#define SEGTREE_H

#include "utils.h"

class Segtree{
    private:
        
    public:
        long long*** seg;
        Segtree(int length);

        ~Segtree();

        void build(int node, int tl, int tr);

        void update(int node, int tl, int tr, int idx, long long mat[][2]);

        long long** query(int node, int tl, int tr, int a, int b);

        void destroySegtree(int node);
};

#endif
