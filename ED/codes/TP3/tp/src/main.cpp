#include "../include/segtree.h"
#include "../include/memlog.h"

#include <iostream>
using namespace std;

int main(){
    char lognome[100] = "teste/data.out";
    iniciaMemLog(lognome);

    ativaMemLog();

    defineFaseMemLog(0);
    int n, m; cin >> n >> m;
    Segtree* segt = new Segtree(n);

    defineFaseMemLog(1);
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
            cout << ans.getIdx(0, 0) << " " << ans.getIdx(1, 0) << endl;
        }
    }

    defineFaseMemLog(2);
    delete segt;
    exit(0);
}
