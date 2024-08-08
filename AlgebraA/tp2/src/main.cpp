#include "../include/functions.h" 

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

int main(){ _
    ll a, b; cin >> a >> b;

    cout << "Fatorando A: " << endl;
    quadraticSieve(a);
    cout << "Fatorando B: " << endl;
    quadraticSieve(b);

    exit(0);
}
