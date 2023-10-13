#include "../include/heap.hpp"

#include <iostream>
using namespace std;

int main(){
    int n; cin >> n;
    Heap hp(n);

    for(int i = 0; i < n; i++){
        int m; cin >> m; hp.Inserir(m);
    }

    while(!hp.Vazio()) 
        cout << hp.Remover() << " ";
    cout << endl;
    
    exit(0);
}
