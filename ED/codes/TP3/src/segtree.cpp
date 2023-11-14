#include "../include/segtree.h"

Segtree::Segtree(int length){
    seg = new long long**[4*length];
}

Segtree::~Segtree(){
    destroySegtree(1);
}

void Segtree::build(int node, int tl, int tr){
    if(tl == tr){
        seg[node] = new long long*[2];
        for(int i = 0; i < 2; ++i){
            seg[node][i] = new long long[2];
            for(int j = 0; j < 2; ++j)
                seg[node][i][j] = (i == j) ? 1 : 0;
        }
        return;
    }

    int tm = (tl+tr)>>1;
    build(node*2, tl, tm);
    build(node*2+1, tm+1, tr);

    seg[node] = new long long*[2];
    for(int i = 0; i < 2; ++i){
        seg[node][i] = new long long[2];
        for(int j = 0; j < 2; ++j)
            seg[node][i][j] = (i == j) ? 1 : 0;
    }
}

void Segtree::update(int node, int tl, int tr, int idx, long long mat[][2]){
    if(tl == tr){
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                seg[node][i][j] = mat[i][j];
        return;
    }

    int tm = (tl+tr)>>1;
    if(tl <= idx && idx <= tm) update(node*2, tl, tm, idx, mat);
    else update(node*2+1, tm+1, tr, idx, mat);

    multiply(seg[node], seg[node*2], seg[node*2+1]);
}

long long** Segtree::query(int node, int tl, int tr, int a, int b){
    if(b < tl || a > tr){
        long long** v = new long long*[2];
        for(int i = 0; i < 2; ++i){
            v[i] = new long long[2];
            for(int j = 0; j < 2; ++j)
                v[i][j] = (i == j) ? 1 : 0;
        }
        return v;
    }

    if(a <= tl && b >= tr) return seg[node];

    int tm = (tl+tr)>>1;
    query(node*2, tl, tm, a, b);
    query(node*2+1, tm+1, tr, a, b);
    multiply(seg[node], seg[node*2], seg[node*2+1]);

    return seg[node];
}

void Segtree::destroySegtree(int node) {
    if (seg[node] != nullptr) {
        for (int i = 0; i < 2; ++i)
            delete[] seg[node][i];
        delete[] seg[node];

        destroySegtree(node * 2);
        destroySegtree(node * 2 + 1);
    }
}
