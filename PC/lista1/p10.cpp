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

const int MAX = 30;

int n, m, s1, s2;
vector<ii> moves = {{-2,-2}, {-2, 2}, {2, -2}, {2, 2}};
vector<vi> grid;
vector<vector<bool>> vis;

bool is_val(int i, int j, int ei, int ej){
    return i >= 0 and i < n and j >= 0 and j < m and !vis[ei][ej] 
           and grid[ei][ej] == 2 and (grid[i][j] == 0 or (i == s1 and j == s2));
}

int dfs(int i, int j){
    int ans = 0;
    for(auto [a, b]: moves){
        int ea = a/2+i, eb = b/2+j;
        if(!is_val(a+i, b+j, ea, eb)) continue;
        vis[ea][eb] = 1, ans = max(ans, dfs(a+i, b+j)+1);
        vis[ea][eb] = 0;
    }

    return ans;
}

void solve(){
    grid = vector<vi>(n, vi(m));

    int l = 0, k = 0; vector<ii> s;
    rep(tt, 0, (n*m+1)/2){
        int a; cin >> a;
        grid[l][k] = a; if(a == 1) s.eb(l, k);
        k += 2; if(k >= m) l++, k = l%2 ? 1 : 0;
        
    }

    // rep(i, 0, n) rep(j, 0, m) cout << grid[i][j] << " \n"[j == m-1];
    // rep(i, 0, s.size()) dbg(s[i].ff, s[i].ss); 

    int ans = 0;
    rep(i, 0, s.size()){
        s1 = s[i].ff, s2 = s[i].ss;
        vis = vector<vector<bool>>(n, vector<bool>(m));
        ans = max(ans, dfs(s1, s2));
    }
    cout << ans << endl;
}

int main(){ _
    while(cin >> n >> m){ if(n == 0 or m == 0) break; solve(); }

    exit(0);
}
