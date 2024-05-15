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

const int MAX = 110, MAXXY = 21, MOD = 1e9+7;

int n, m, xmax, ymax;
int v[MAX][MAX];
int memo[MAX][MAX][MAXXY][MAXXY];

int dp(int i, int j, int x, int y, int d){
    if(i >= n or j < 0 or j >= m) return INF;

    if(v[i][j] == 0) x--;
    else if(v[i][j] < 0) y--;
    
    if(x < 0 or y < 0) return INF;

    int& p = memo[i][j][x][y];
    if(p != INF) return p;

    if(i == n-1 and j == m-1) return p = v[i][j];

    return p = v[i][j]+min({ d != 1 ? dp(i, j-1, x, y, -1) : p,
                             d != -1 ? dp(i, j+1, x, y, 1) : p,
                             dp(i+1, j, x, y, 0)
                           });
}

void solve(){
    rep(i, 0, n) rep(j, 0, m) cin >> v[i][j];

    memset(memo, INF, sizeof memo);
    int ans = dp(0, 0, xmax, ymax, 0);

    // rep(i, 0, n) rep(j, 0, m) cout << memo[i][j] << " \n"[j == m-1];

    if(ans > 1e6){ cout << "Impossivel" << endl; return; }
    cout << ans << endl;
}

int main(){ _
    while(cin >> n >> m >> xmax >> ymax) solve();

    exit(0);
}
