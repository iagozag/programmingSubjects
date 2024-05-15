#include "../include/functions.h" 

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

int main(){ _
    ll n, a; cin >> n >> a;

    Functions F(n, a);
    F.MillerRabin();
    F.Generator();

    exit(0);
}
