#include "../include/functions.h"

template <
    class result_t   = chrono::milliseconds,
    class clock_t    = chrono::steady_clock,
    class duration_t = chrono::milliseconds
>
auto since(chrono::time_point<clock_t, duration_t> const& start){
    return chrono::duration_cast<result_t>(clock_t::now() - start);
}

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

bool Functions::MillerRabin(ll pp){
    ll s = 0, d = pp-1;
    while(!(d&1)) d >>= 1, s++;

    bool found = true;
    for(auto x: primes){
        if(pp == x){ found = true; break; }
        if(composite(pp, x, d, s)) found = false;
    }
    return found;
}

Functions::Functions(ll _n, ll _a):
    p(_n), a(_a), g(1) {}

void Functions::NextPrime(){
    if(!(p&1)) p--;

    int cnt = 0;
    while(true){
        p += 2, cnt++;
        if(MillerRabin(p)) break;
    }
    
    cout << "p: " << p << ", iterations_cnt: " << cnt << endl;
}
void Functions::Generator(){
    vector<ll> fact, exp;
    ll phi = p-1, n = phi;
    for (long long i = 2; i*i <= n and i < 1e7; i++) if(n%i == 0) {
        fact.emplace_back(i), exp.emplace_back(0);
        while(n%i == 0) n /= i, exp[fact.size()-1]++;
    }

    bool parcial = (n != 1 and !MillerRabin(n));
    if(n) fact.emplace_back(n), exp.emplace_back(1);

    vector<ll> ord(fact.size()); ll min_order = 1;
    for(size_t i = 0; i < fact.size(); i++){
        ll a = 2+rand()%(p-2);
        while(fexp(a, phi/fact[i], p) == 1) a = 2+rand()%(p-2);
        g *= fexp(a, phi/(fexp(fact[i], exp[i], p)), p), g %= p;
        if(!parcial or i < fact.size()-1) min_order *= fexp(fact[i], exp[i], p);
    }
    
    cout << "g: " << g << endl;
    cout << "ord(g, p) is in: [" << min_order << ", " << phi << "]" << endl;
}

void Functions::DiscreteLogarithm(){
    auto start = chrono::steady_clock::now();

    a %= p;
    ll n = sqrt(p) + 1, ans = -1;
    map<ll, ll> vals;
    for (ll pp = 1; pp <= n; pp++)
        vals[fexp(a, pp * n, p)] = pp;
    for (ll q = 0; q <= n; ++q) {
        ll cur = (fexp(a, q, p) * g) % p;
        if (vals.count(cur)) {
            ans = vals[cur] * n - q;
            break;
        }
    }

    cout << "Elapsed(ms)=" << since(start).count() << std::endl;
    cout << "Discrete Logarithm of 'a' module 'p' in base 'g' = " << ans << endl;
}
