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

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 1e6+10, MOD = 1e9+7;

ll dp(ll n){
    if(n < 10) return n*(n+1)/2;

    ll d = log10(n), p = pow(10, d), c = ;

    return dp(n-(n/p)*p)*c+45*p;
}

ll naive(ll n){
    ll sum = 0;
    rep(i, 1, n+1){
        string s = to_string(i);
        forr(x, s) sum += x-'0';
    }

    return sum;
}

void solve(ll l, ll r){
    cout << "dp(" << r << "): " << dp(r) << ", dp(" << l-1 << "): " << dp(l-1) << endl;
    cout << "naive(" << r << "): " << naive(r) << ", naive(" << l-1 << "): " << naive(l-1) << endl;
    cout << "dp: " << (dp(r)%MOD-dp(l-1)%MOD+MOD)%MOD << endl; 
    cout << "naive: " << naive(r)-naive(l-1) << endl;
}

int main(){ _
    ll l, r;

    while(cin >> l >> r) solve(l, r);

    exit(0);
}