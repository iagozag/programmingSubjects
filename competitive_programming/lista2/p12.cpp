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

const int MAX = 1e3+10, MOD = 1e9+7;

int n, k;
vector<double> v, p;
vector<vector<double>> dp;

void solve(){
    v = p = vector<double>(n+1), dp = vector<vector<double>>(n+1, vector<double>(k+1, 0)); 
    rep(i, 0, n) cin >> v[i]; 
    rep(i, 0, n) cin >> p[i], p[i] /= 100.0;

    repr(i, n-1, 0) rep(j, 0, k+1){
        if(j > 0) dp[i][j] = max(p[i]*(v[i]+dp[i+1][j]), v[i]+dp[i+1][j-1]);
        else dp[i][j] = p[i]*(v[i]+dp[i+1][j]);
    }

    cout << fixed << setprecision(2) << dp[0][k] << endl;
}

int main(){ _
    while(cin >> n >> k) solve();

    exit(0);
}
