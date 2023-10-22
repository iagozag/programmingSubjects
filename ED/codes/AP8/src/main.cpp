#include<iostream>
#include "../include/heap.hpp"

using namespace std;

int main(){
    int n, m; cin >> n >> m;

    Heap hp(m);
    for(int i = 0; i < m; i++){
        int u, v, c; cin >> u >> v >> c;
        Aresta a; a.u = u; a.v = v; a.custo = c;
        hp.Inserir(a);
    }

    UnionFind uf(n);
    for(int i = 0; i < n; i++) uf.Make(i);

    int cnt = 0, cost = 0;
    while(!hp.Vazio()){
        Aresta a = hp.Remover();
        if(uf.Find(a.u) != uf.Find(a.v))
            uf.Union(a.u, a.v), cnt++, cost += a.custo;

        if(cnt == n-1) break;
    }

    cout << cost << endl;

    exit(0);
}
