#include "../include/functions.h"

ll fexp(ll x, ll b, ll m){
    ll ans = 1; 
    if(m != -1) x %= m;
    while(b > 0){
        if(b&1){
            if(m != -1) ans = ans*x%m;
            else ans = ans*x;
        }
        if(m != -1) x = x*x%m;
        else x = x*x;

        b >>= 1;
    }
    return ans;
}

ll legendreSymbol(ll a, ll p){
    ll res = fexp(a, (p-1)>>1, p); 
    return (res > 1 ? -1 : res);
}

vector<ll> sieve(const ll& n, int b){
    vector<ll> fact;
    vector<bool> isp(b+1);
    for(int i = 2; i <= b; ++i) if(!isp[i]){
        if(legendreSymbol(n, i) == 1) fact.emplace_back(i);
        if((ll)i*(ll)i > (ll)1e8) continue;
        for(int j = i*i; j <= b; j += i) isp[j] = 1;
    }
    return fact;
}

pair<ll, ll> tonelliShanks(ll n, ll p){
    if(p == 2) return {n, n};

    ll q = p - 1;
    ll s = 0;
    while (q % 2 == 0) q >>= 1, ++s;

    ll z = 2;
    while(legendreSymbol(z, p) != -1) z++;

    ll c = fexp(z, q, p),
       r = fexp(n, (q + 1)>>1, q),
       t = fexp(n, 1, p),
       m = s;

    while(t%p != 1) {
        ll i = 1;
        while(fexp(t, fexp(2, i, -1), p) != 1) i++;

        ll b = fexp(c, fexp(2, m-i-1, -1), p);

        r = r*b%p;
        t = t*b*b%p;
        c = b*b%p;
        m = i;
    }

    return {r, p-r};
}

ll gauss(vector<dynamic_bitset<>> a, int n, int m, dynamic_bitset<>& ans){
    vector<int> where(m, -1);
    for(int col = 0, row = 0; col < m && row < n; col++){
        for(int i = row; i < n; i++) if(a[i][col]){
            swap(a[i], a[row]);
            break;
        }
        if(!a[row][col]) continue;
        where[col] = row;

        for(int i = 0; i < n; i++) if(i != row && a[i][col])
            a[i] ^= a[row];
        row++;
    }

    ans.resize(m);
    ans.reset();
    for(int i = 0; i < m; ++i) if(where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for(int i = 0; i < n; i++){
        int sum = 0;
        for(int j = 0; j < m; j++) sum += ans[j]*a[i][j];
        if(sum == a[i][m]) return 0;
    }

    for(int i = 0; i < m; i++) if(where[i] == -1)
        return INF;

    return 1;
}

ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a%b);
}

void quadraticSieve(const ll& n){
    typedef number<cpp_dec_float<50>> PreciseFloat;
    PreciseFloat precise_n(n.str());
    const int b = (int)min((ll)10000000, (ll)(MIN_BOUND + ceil(exp(PreciseFloat(0.55) * sqrt(log(precise_n) * log(log(precise_n))))))+1);

    
    vector<ll> factBase = sieve(n, b);

    for(auto x: factBase) cout << x << " ";
    cout << endl;

    cout << "Limite superior para os primos: " << b << endl;
    cout << "Número de primos na base de fatores: " << sz(factBase) << endl;

    ll root = sqrt(n);
    vector<pair<ll, vector<int>>> smoothNumbers;
    vector<dynamic_bitset<>> exps;

    for(ll x = root+1; x <= root+b; x++){
        ll val = x*x-n, temp = abs(val);
        vector<int> exp(sz(factBase), 0);

        for(int i = 0; i < sz(factBase); i++)
            while(temp%factBase[i] == 0) temp /= factBase[i], exp[i]++;

        if(temp == 1){
            smoothNumbers.emplace_back(x, exp);
            dynamic_bitset<> bitExp(sz(factBase));
            for(int i = 0; i < sz(factBase); i++) bitExp[i] = exp[i]%2;
            exps.push_back(bitExp);
        }
        if(sz(smoothNumbers) >= sz(factBase)+20) break;
    }

    for(int i = 0; i < sz(smoothNumbers); i++){
        cout << smoothNumbers[i].first << ": ";
        for(int j = 0; j < sz(smoothNumbers[i].second); j++) cout << smoothNumbers[i].second[j] << " ";
        cout << endl;
    }

    cout << "Tamanho do vetor de índices j: " << sz(smoothNumbers) << "\n";

    ll a, b_;
    do{
        a = 1;
        b_ = 1;
        dynamic_bitset<> ans;
        if(gauss(exps, exps.size(), sz(factBase), ans) == INF){
            cout << "Impossível" << endl;
            return;
        }

        vector<int> combined_exponents(sz(factBase), 0);

        for(int i = 0; i < sz(smoothNumbers); i++){
            if(ans[i]){
                a = (a * smoothNumbers[i].first) % n;
                for(int j = 0; j < sz(factBase); j++) {
                    combined_exponents[j] += smoothNumbers[i].second[j];
                }
            }
        }

        for(int i = 0; i < sz(factBase); i++) {
            if (combined_exponents[i] > 0) {
                b_ = (b_ * fexp(factBase[i], combined_exponents[i] / 2, n)) % n;
            }
        }

        a = (a + n) % n;
        b_ = (b_ + n) % n;
    } while(!a or !b or (a%n == b_%n) or a%n == (-b_)%n+n);

    cout << "x = " << a << endl;
    cout << "y = " << b_ << endl;
    cout << "mdc(x - y, N) = " << gcd(a-b_, n) << endl;
    cout << "mdc(x + y, N) = " << gcd(a+b_, n) << endl;
    
}
