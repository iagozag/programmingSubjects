#include "../include/segtree.h"

#include <iostream>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

int main(){ _
    int n, m; cin >> n >> m;
    Segtree segt(n);
    segt.build(1, 0, n-1);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                cout << segt.seg[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    /*for(int i = 0; i < m; i++){
        char op; int idx, a, b, c, d; cin >> op;
        if(op == 'u'){
            cin >> idx >> a >> b >> c >> d;

            long long m[2][2] = {{a, b}, {c, d}}; 
            segt.update(1, 0, n-1, idx, m);
        } else{
            cin >> a >> b >> c >> d;
            long long** m = segt.query(1, 0, n-1, a, b);

            long long** aux = new long long*[2];
            long long** ans = new long long*[2];
            for (int i = 0; i < 2; ++i) 
                aux[i] = new long long[2], ans[i] = new long long[2];

            for(int i = 0; i < 2; i++)
                for(int j = 0; j < 2; j++)
                    aux[i][j] = 0, ans[i][j] = 0;

            multiply(ans, m, aux);
            cout << get_less_sig(ans[0][0]) << " " << get_less_sig(ans[1][0]) << endl;

            for (int i = 0; i < 2; ++i) {
                delete[] m[i];
                delete[] aux[i];
                delete[] ans[i];
            }
            delete[] m;
            delete[] aux;
            delete[] ans;
        }
    }*/

    exit(0);
}
