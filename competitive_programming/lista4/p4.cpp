#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,x,n) for(auto i=x;i<n;i++)
#define repr(i,n,x) for(auto i=n;i>=x;i--)
#define forr(x, v) for(auto& x: v)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())
#define endl '\n'
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const ll MAX = 1e9+10, TAM = sqrt(MAX)+1;
ll MOD;

bitset<TAM> is_c;
vl primes;

void sieve(){
    is_c.set(0), is_c.set(1);
    rep(i, 2, TAM) if(!is_c.test(i)){
        primes.eb(i);
        for(int j = i*i; j < TAM; j += i) is_c.set(j);
    }
}

ll fexp(ll a, ll b){
    ll ans = 1;
    while(b){
        if(b&1) ans = ans*a%MOD;
        a = a*a%MOD, b >>= 1;
    }
    return ans;
}

ll extended_gcd(ll a, ll b, ll& x, ll& y){
    if(!b){
        x = 1, y = 0;
        return a;
    }
    ll x1, y1, d = extended_gcd(b, a%b, x1, y1);
    x = y1, y = x1-y1*(a/b);
    return d;
}

void solve(){
    ll n, e, c; cin >> n >> e >> c;
    MOD = n;

    sieve();

    ll p = 1, q = 1;
    rep(i, 1, sz(primes)){
        bool can = false;
        if(n%primes[i] == 0){
            int a = n/primes[i]; can = true;
            rep(j, 0, sz(primes)){
                if(primes[j] > sqrt(a)) break;
                if(a%primes[j] == 0) can = false;
            }
            if(can){ p = primes[i], q = a; break; }
        }
    }

    ll phi = (p-1)*(q-1), d, a;
    extended_gcd(e, phi, d, a);
    d = (d%phi+phi)%phi;

    ll ans = fexp(c, d);
    cout << ans << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
