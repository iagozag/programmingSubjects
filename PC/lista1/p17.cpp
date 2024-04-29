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
typedef pair<int,int> ii;
typedef vector<int> vi;
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

ll MAX;

int is_stripped(ll d){
    int p = 1;
    rep(i, 2, sqrt(d)){
        if(d%(i*1LL*i*1LL) == 0) return 0;
        if(d%i == 0) p = 0;
    }

    return !p;
}

void solve(){
    ll n; cin >> n;
    if(n == 1){ cout << 0 << endl; return; }

    ll ans = is_stripped(n);
    rep(i, 2, sqrt(n)+1){
        if(n%i == 0){ ans += is_stripped(i); if(n/i != i) ans += is_stripped(n/i); }
    }

    cout << ans << endl;
}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}
