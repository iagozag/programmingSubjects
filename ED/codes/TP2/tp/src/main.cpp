#include "../include/sorting_algorithms.h"
#include "../include/graph.h"
#include "../include/pair.h"
#include "../include/memlog.h"

#include <iostream>
#include <numeric>
using namespace std;

#define BUBBLE 'b'
#define SELECTION 's'
#define INSERTION 'i'
#define QUICK 'q'
#define MERGE 'm'
#define HEAP 'h'
#define MINE 'y'

int main(){
    char lognome[100] = "teste/data.out";
    iniciaMemLog(lognome);

    ativaMemLog();

    char c; int n; cin >> c >> n;

    defineFaseMemLog(0);
    Graph g(n);
    int colors[n]; 

    for(int i = 0; i < n; i++){
        int m; cin >> m;
        for(int j = 0; j < m; j++){
            int a; cin >> a; g.insertEdge(i, a); 
        }
    } 

    for(int i = 0; i < n; i++){ int a; cin >> a; colors[i] = a; }
    g.addColors(colors);

    defineFaseMemLog(1);
    if(!g.verify_coloring()) { cout << 0 << endl; exit(0); }

    Pair* ans = new Pair[n];
    for(int i = 0; i < n; i++){
        Pair p; p.vert = i, p.color = colors[i];
        ans[i] = p;
        escreveMemLog((long int)(&(ans[i])),sizeof(Pair),1);
    }

    switch(c){
        case BUBBLE:
            bubble_sort(ans, n); 
            break;
        case SELECTION:
            selection_sort(ans, n);
            break;
        case INSERTION:
            insertion_sort(ans, n);
            break;
        case QUICK:
            quick_sort(ans, 0, n-1);
            break;
        case MERGE:
            merge_sort(ans, 0, n-1);
            break;
        case HEAP:
            heap_sort(ans, n);
            break;
        case MINE:
            my_sort(ans, n);
            break;
        default:
            exit(0);
    } 

    cout << 1 << " ";
    for(int i = 0; i < n; i++){
        cout << ans[i].vert << " ";
        leMemLog((long int)(&(ans[i])),sizeof(Pair),1);
    }
    cout << endl;

    defineFaseMemLog(2);
    for(int i = 0; i < n; i++) leMemLog((long int)(&(ans[i])),sizeof(Pair),1);
    delete[] ans;
    return finalizaMemLog(); 
}

