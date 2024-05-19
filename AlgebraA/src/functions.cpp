#include "../include/functions.h"

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
        x = x*x%n;
        if(x == n-1) return false;
    }
    return true;
}

Functions::Functions(ll _n, ll _a):
    p(_n), a(_a) {}

void Functions::MillerRabin(){
    if(!(p&1)) p--;

    int cnt = 0; bool found = false;
    while(!found){
        p += 2, found = true, cnt++;
        ll s = 0, d = p-1;
        while(!(d&1)) d >>= 1, s++;

        for(auto pp: primes){
            if(p == pp){ found = true; break; }
            if(composite(p, pp, d, s)) found = false;
        }
    }
    
    cout << "p: " << p << ", cnt: " << cnt << endl;
}

void Functions::Generator(){
    vector<ll> fact;
    ll phi = p-1, n = phi;
    for (ll i = 2; i*i <= n; i++)
        if (n%i == 0) {
            fact.push_back (i);
            while(n%i == 0) n /= i;
        }
    if(n) fact.push_back(n);

    for (ll ans=2; ans<=p; ans++) {
        bool ok = true;
        for (size_t i = 0; i < fact.size() and ok; i++)
            ok &= fexp(ans, phi/fact[i], p) != 1;
        if(ok){ g = ans; break; }
    }
    
    cout << "Generator: " << g << endl;
}

void Functions::DiscreteLogarithm(){
    a %= p, g %= p;
    ll n = sqrt(p) + 1, ans = -1;
    unordered_map<ll, ll> vals;
    for (ll p = 1; p <= n; ++p)
        vals[fexp(a, p * n, p)] = p;
    for (ll q = 0; q <= n; ++q) {
        ll cur = (fexp(a, q, p) * g) % p;
        if (vals.count(cur)) {
            ans = vals[cur] * n - q;
            break;
        }
    }
    
    cout << "Discrete Log of a module p in base g = " << ans << endl;
}
