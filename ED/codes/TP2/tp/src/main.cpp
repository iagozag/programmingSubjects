#include <bits/stdc++.h>

#include "../include/sorting_algorithms.h"
#include "../include/verifying_coloring.h"
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
    vector<vector<int>> v(n);
    vector<int> colors(n);

    for(int i = 0; i < n; i++){
        int m; cin >> m;
        for(int j = 0; j < m; j++) cin >> v[i][j];
    } 

    for(int i = 0; i < n; i++) cin >> colors[i];

    switch(c){
        case BUBBLE:
            verify_coloring(v, colors, bubble_sort(v, colors));
    } 

    exit(0);
}

