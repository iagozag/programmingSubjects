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

const int MAX = 110, MOD = 1e9+7;

void solve(){
    int n; cin >> n;
    vi v = vi(n); forr(x, v) cin >> x;
    
    vector<vi> memo(3, vi(n));

    rep(i, 1, 3) if(v[0] != 0 and v[0] != i) memo[i][0] = 1;

    rep(i, 1, n){
        memo[0][i] = max({memo[0][i-1], memo[1][i-1], memo[2][i-1]});
        
        if(v[i] == 0){
            memo[1][i] = max({memo[0][i-1], memo[1][i-1], memo[2][i-1]});
            memo[2][i] = max({memo[0][i-1], memo[1][i-1], memo[2][i-1]});
        }
        else if(v[i] == 1){
            memo[1][i] = max({memo[0][i-1], memo[1][i-1], memo[2][i-1]});
            memo[2][i] = max({memo[0][i-1]+1, memo[1][i-1]+1, memo[2][i-1]});
        }
        else if(v[i] == 2){
            memo[1][i] = max({memo[0][i-1]+1, memo[1][i-1], memo[2][i-1]+1});
            memo[2][i] = max({memo[0][i-1], memo[1][i-1], memo[2][i-1]});
        }
        else{
            memo[1][i] = max({memo[0][i-1]+1, memo[1][i-1], memo[2][i-1]+1});
            memo[2][i] = max({memo[0][i-1]+1, memo[1][i-1]+1, memo[2][i-1]});
        }
    }

    int ma = 0;
    rep(i, 0, 3) ma = max(ma, memo[i][n-1]);
    
    cout << n-ma << endl;
}

int main(){ _
    int ttt = 1;

    while(ttt--) solve();

    exit(0);
}
