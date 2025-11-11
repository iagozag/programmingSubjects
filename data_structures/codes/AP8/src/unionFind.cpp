#include "../include/unionFind.hpp"
#include <iostream>

UnionFind::UnionFind(int n){
    tamanho = n;
    subconjuntos = new Subconjunto[tamanho];
}

UnionFind::~UnionFind(){
    delete subconjuntos;
}

void UnionFind::Make(int x){
    subconjuntos[x].representante = x;
    subconjuntos[x].rank = 0;
}

int UnionFind::Find(int x){
    if (x == subconjuntos[x].representante)
        return x;
    return subconjuntos[x].representante = Find(subconjuntos[x].representante);
}

void UnionFind::Union(int x, int y){
    x = Find(x);
    y = Find(y);
    if (x != y) {
        if(subconjuntos[x].rank < subconjuntos[y].rank)
            std::swap(x, y);
        subconjuntos[y].representante = x;
        if(subconjuntos[x].rank == subconjuntos[y].rank)
            subconjuntos[x].rank++;
    }
}
