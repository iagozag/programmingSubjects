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

const int MAX = 310, MOD = 1e9+7;

int n, m, k;

void solve(){
    vector<vi> mat(n, vi(m)), pref(n, vi(m+1));

    rep(i, 0, n){
        string s; cin >> s;
        rep(j, 0, m) mat[i][j] = (s[j] == '.');
    }

    rep(i, 0, n) rep(j, 1, m+1) pref[i][j] = pref[i][j-1]+mat[i][j-1];
    
    int ans = m*n;
    rep(l, 0, m) rep(r, l, m){
        int u = 0, d = 0, qnt = 0;
        while(d < n){
            qnt += pref[d][r+1]-pref[d][l];
            while(u <= d and qnt >= k)
                ans = min(ans, (r-l+1)*(d-u+1)), qnt -= pref[u][r+1]-pref[u][l], u++;
            d++;
        }
    }

    cout << ans << endl;
}

int main(){ _
    while(cin >> n >> m >> k){ if(n == 0) break; solve(); }

    exit(0);
}
