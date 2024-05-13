#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);

typedef int256_t ll;

ll fexp(ll a, ll b, ll m){
    ll ans = 1; a %= m;
    while(b > 0){
        if(b&1) ans = ans*a%m;
        a = a*a%m, b >>= 1;
    }
    return ans;
}

bool composite(ll n, ll a, ll d, ll s){
    ll x = fexp(a, d, n);
    if(x == 1 or x == n-1) return false;
    for(ll i = 1; i < s; i++){
        x = fexp(x, 2, n);
        if(x == n-1) return false;
    }
    return true;
}

bool MillerRabin(ll n){
    if(n < 4) return n == 2 or n == 3; 

    ll s = 0, d = n-1;
    while(!(d&1)) d >>= 1, s++;

    for(int i = 0; i < 5; i++){
        ll a = 2+rand()%(n-3);
        if(composite(n, a, d, s)) return false;
    }
    return true;
}

int main(){ _
    ll n, cnt = 1; cin >> n; n++; if(!(n&1)) n++;
    while(!MillerRabin(n)) cout << n << endl, n += 2, cnt++;
    cout << "p = " << n << ", cnt = " << cnt << endl;

    exit(0);
}
