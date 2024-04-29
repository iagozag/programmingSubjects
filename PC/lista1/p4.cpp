#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,x,n) for(auto i=x;i<n;i++)
#define repr(i,n,x) for(auto i=n;i>=x;i--)
#define forr(x, v) for(auto& x: v)
#define all(a) (a).begin(), (a).end()
#define endl '\n'
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<ll> vl;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void DBG() {
    cerr << "]" << endl;
}

void DBGC() {
    cerr << "]" << endl;
}

template<class H, class... T> void DBG(H h, T... t) {
    cerr << to_string(h);
    if(sizeof...(t)) cerr << ", ";
    DBG(t...);
}

template<class H, class... T> void DBGC(H h, T... t) {
    for(auto& x: h) cerr << x << " ";
    if(sizeof...(t)) cerr << "], [ ";
    DBGC(t...);
}

#ifndef _DEBUG
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define dbgc(...) cerr << "["<< #__VA_ARGS__ << "]: [ "; DBGC(__VA_ARGS__) 
#else
#define dbg(...) 0
#define dbgc(...) 0
#endif

void no(){ cout << "impossivel" << endl; }
void yes(){ cout << "YES" << endl; }

const ll MAX = 2e5+10;

ll check(ll n, ll m, ll l, ll k, map<ll,ll,greater<ll>> mp){
    ll cnt = mp[m]; if(cnt >= n/l) return n/l;

    ll tt = cnt;
    forr(x, mp){
        if(x.ss <= 0) continue;
        if(mp[m-x.ff] > 0){
            if(2*x.ff == m and x.ss == 1) continue;
            
            ll mi = 2*x.ff != m ? min(x.ss, mp[m-x.ff]) : x.ss/2, need = n/l-tt;
            mp[m-x.ff] -= mi, x.ss -= mi, cnt += min(need*2, mi*2), tt += min(mi, need); 
        }
        if(tt >= n/l) return cnt;
    }
    
    return INF;
}

void solve(ll n, ll m){
    n *= 100, m *= 100;
    ll l, k; cin >> l >> k; bool bn = n%l == 0, bm = m%l == 0;
    map<ll, ll, greater<ll>> mp; rep(i, 0, k){ ll a; cin >> a; mp[a*100]++; }
    if(!bn and !bm) return no();

    ll ans = INF;
    if(bn) ans = min(ans, check(n, m, l, k, mp));
    if(bm) ans = min(ans, check(m, n, l, k, mp));

    if(ans == INF) return no();
    cout << ans << endl;
}

int main(){ _
    ll n, m;
    while(cin >> n >> m){ if(n == 0 or m == 0) break; solve(n, m); }

    exit(0);
}
