#include "../include/segtree.h"

#include <iostream>
using namespace std;

int main(){
    int n, m, mod = 1e8; cin >> n >> m;
    Segtree* segt = new Segtree(n);

    for(int i = 0; i < m; i++){
        char op; int idx, a, b, c, d; cin >> op;
        if(op == 'u'){
            cin >> idx >> a >> b >> c >> d;

            Matrix m(a, b, c, d); 
            segt->update(1, 0, n-1, idx, m);
        } else{
            cin >> a >> b >> c >> d;
            Matrix m = segt->query(1, 0, n-1, a, b);

            Matrix ans = multiply(m, Matrix(c, 0, d, 0));
            cout << ans.getIdx(0, 0) % mod << " " << ans.getIdx(1, 0) % mod << endl;
        }
    }

    delete segt;
    exit(0);
}
