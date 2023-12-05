#include "../include/segtree.h"
#include <iostream>

Segtree::Segtree(int length){
    seg = new Matrix[4*length];
}

Segtree::~Segtree(){
    delete[] seg; 
}

Matrix Segtree::update(int node, int tl, int tr, int idx, Matrix& mat){
    if(idx < tl || idx > tr) return seg[node];
    if(tl == tr) return seg[node] = mat;

    int tm = (tl+tr)>>1;
    return seg[node] = multiply(update(node*2, tl, tm, idx, mat), update(node*2+1, tm+1, tr, idx, mat));
}

Matrix Segtree::query(int node, int tl, int tr, int a, int b){
    if(b < tl || a > tr) return Matrix();
    if(a <= tl && b >= tr) return seg[node];

    int tm = (tl+tr)>>1;
    return multiply(query(node*2, tl, tm, a, b), query(node*2+1, tm+1, tr, a, b));
}

void Segtree::printSegTree(){
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                std::cout << seg[i].getIdx(j, k) << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
