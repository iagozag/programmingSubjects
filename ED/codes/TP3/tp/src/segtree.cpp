#include "../include/segtree.h"
#include "../include/memlog.h"

#include <iostream>

Segtree::Segtree(int l){
    length_ = 4*l;
    seg = new Matrix[length_];
}

Segtree::~Segtree(){
    long long sum = 0;
    for(int i = 0; i < length_; i++)
        for(int j = 0; j < 2; j++)
            for(int k = 0; k < 2; k++)
                sum += seg->getIdx(j, k);

    delete[] seg; 
}

Matrix Segtree::update(int node, int tl, int tr, int idx, Matrix& mat){
    if(idx < tl || idx > tr) return seg[node];
    if(tl == tr){
        seg[node] = mat;
        escreveMemLog((long int)(&(seg[node][0][0])),sizeof(int),0);
        escreveMemLog((long int)(&(seg[node][0][1])),sizeof(int),0); 
        escreveMemLog((long int)(&(seg[node][1][0])),sizeof(int),0); 
        escreveMemLog((long int)(&(seg[node][1][1])),sizeof(int),0); 

        return seg[node];
    }

    int tm = (tl+tr)>>1;
    return seg[node] = multiply(update(node*2, tl, tm, idx, mat), update(node*2+1, tm+1, tr, idx, mat));
}

Matrix Segtree::query(int node, int tl, int tr, int a, int b){
    if(b < tl || a > tr) return Matrix();
    if(a <= tl && b >= tr) return seg[node];

    int tm = (tl+tr)>>1;
    return multiply(query(node*2, tl, tm, a, b), query(node*2+1, tm+1, tr, a, b));
}
