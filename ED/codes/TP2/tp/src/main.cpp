#include "../include/sorting_algorithms.h"
#include "../include/verifying_coloring.h"
#include "../include/linked_list.h"

#include <iostream>
using namespace std;

#define BUBBLE 'b'
#define SELECTION 's'
#define INSERTION 'i'
#define QUICK 'q'
#define MERGE 'm'
#define HEAP 'h'
#define MINE 'y'

int main(){
    char c; int n; cin >> c >> n;
    ListaAdjacencia* v = new ListaAdjacencia(n);
    int colors[n]; 

    for(int i = 0; i < n; i++){
        int m; cin >> m;
        for(int j = 0; j < m; j++){
            int a; cin >> a; a--; v->adicionaAresta(i, a); 
        }
    } 

    for(int i = 0; i < n; i++){ int a; cin >> a; a--; colors[i] = a; }
    v->adicionaCores(colors);

    for(int i = 0; i < n; i++){ cout << i << ": "; v->imprime(i); cout << endl << "cor: " << v->getCor(i) << endl; }

    if(!verify_coloring(v)) { cout << 0 << endl; exit(0); }
    cout << 1 << " ";

    switch(c){
        case BUBBLE:
            // verify_coloring(v, colors, bubble_sort(v, colors));
            break;
    } 


    cout << endl;
    delete v;
    exit(0);
}

