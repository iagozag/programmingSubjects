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
    int c, n; cin >> c >> n;
    ListaAdjacencia v(n);
    LinkedList colors; 

    for(int i = 0; i < n; i++){
        int m; cin >> m;
        for(int j = 0; j < m; j++){
            int a; cin >> a; a--; v.adicionaAresta(i, a); 
        }
    } 

    for(int i = 0; i < n; i++){ int a; cin >> a; colors.insert(a); }

    if(!verify_coloring(v)) { cout << 0 << endl; return(0); }

    switch(c){
        case BUBBLE:
            // verify_coloring(v, colors, bubble_sort(v, colors));
            break;
    } 

    for(int i = 0; i < n; i++) v.imprime(i);
    colors.print();

    exit(0);
}

