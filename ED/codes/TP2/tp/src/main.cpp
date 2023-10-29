#include "../include/sorting_algorithms.h"
#include "../include/graph.h"

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
    Grafo g(n);
    int colors[n]; 

    for(int i = 0; i < n; i++){
        int m; cin >> m;
        for(int j = 0; j < m; j++){
            int a; cin >> a; a--; g.InsereAresta(i, a); 
        }
    } 

    for(int i = 0; i < n; i++){ int a; cin >> a; colors[i] = a; }
    g.adicionaCores(colors);

    if(!g.verify_coloring()) { cout << 0 << endl; exit(0); }

    cout << 1 << " ";

    switch(c){
        case BUBBLE:
            // verify_coloring(v, colors, bubble_sort(v, colors));
            break;
    } 

    cout << endl;
    exit(0);
}

