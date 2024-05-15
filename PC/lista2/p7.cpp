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

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 1010, MOD = 1e9+7;

/* int dp(int k, int i, int j){
    if(i > j) return 0;

    if(memo[i][j] != -1) return memo[i][j];

    if(k%2 == 0) return memo[i][j] = max(dp(k+1, i+1, j)+v[i],  dp(k+1, i, j-1)+v[j]);
    return memo[i][j] = min(dp(k+1, i+1, j), dp(k+1, i, j-1));
}*/

void solve(int n){
    n *= 2;
    vi v(n); rep(i, 0, n) cin >> v[i], v[i] = (v[i]%2 == 0);

    int memo[n+1][n+1]; rep(i, 0, n) memo[i][i] = 0;
    rep(i, 1, n) rep(j, 0, n){
        int k = i+j; if(k >= n) break;

        if(i&1) memo[j][k] = max(memo[j+1][k]+v[j], memo[j][k-1]+v[k]);
        else memo[j][k] = min(memo[j+1][k], memo[j][k-1]);
    }

    cout << memo[0][n-1] << endl;
}

int main(){ _
    int n;
    while(cin >> n){ if(n == 0) break; solve(n); }

    exit(0);
}
