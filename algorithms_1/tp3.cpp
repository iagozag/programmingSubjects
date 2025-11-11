#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,x,n) for(auto i=x;i<n;i++)
#define repr(i,n,x) for(auto i=n;i>=x;i--)
#define endl '\n'
#define eb emplace_back
#define ff first
#define ss second

typedef pair<int,int> pii;
typedef pair<bool,bool> pbb;
typedef vector<int> vi;

const int INF = 0x3f3f3f3f;

int l, c, n;
vector<vector<pbb>> adj;

bool val(int i, int a){
    rep(j, 0, c) if(a&(1<<j) and a&(1<<(j+1)%c) and adj[i][j].ff) return false;
    return true;
}

bool val2(int i, int a, int b){
    rep(j, 0, c) if(a&(1<<j) and b&(1<<j) and adj[i][j].ss) return false;
    return true;
}

int main(){ _
    cin >> l >> c >> n;
    vector<vi> v(l, vi(c)); adj = vector<vector<pbb>>(l, vector<pbb>(c));
    rep(i, 0, n){
        int x, y, val, di, ci, ei, bi; cin >> x >> y >> val >> di >> ci >> ei >> bi; --x, --y;
        v[x][y] = val, adj[x][y] = {di, ci};
    }

    int maxc = 1<<c; vector<vi> sum(l, vi(maxc)); 
    rep(i, 0, l) rep(j, 0, maxc) if(val(i, j))
        rep(k, 0, c) if(j&(1<<k)) sum[i][j] += v[i][k];

    vector<vector<vi>> dp(l, vector<vi>(maxc, vi(maxc, -INF))); vi pos;
    rep(j, 0, 1<<c) if(val(0, j)) dp[0][j][j] = sum[0][j], pos.eb(j);

    rep(i, 1, l) rep(m, 0, pos.size()) rep(j, 0, maxc) if(val(i, j)) 
        rep(k, 0, maxc) if(val2(i, j, k)) 
            dp[i][pos[m]][j] = max(dp[i][pos[m]][j], dp[i-1][pos[m]][k]+sum[i][j]);

    rep(j, 0, maxc) rep(m, 0, pos.size())
        if(dp[l-1][pos[m]][j] >= 0 and !val2(0, pos[m], j)) dp[l-1][pos[m]][j] = -INF;

    int ans = 0, idxm, idxj;
    rep(j, 0, maxc) rep(m, 0, pos.size()) if(ans < dp[l-1][pos[m]][j]) 
        ans = dp[l-1][pos[m]][j], idxm = pos[m], idxj = j;

    vector<pii> crystals;
    rep(j, 0, c) if(idxj&(1<<j)) crystals.eb(l, j+1); 

    repr(i, l-2, 0) rep(j, 0, maxc) 
        if(dp[i][idxm][j]+sum[i+1][idxj] == dp[i+1][idxm][idxj] and val2(i+1, idxj, j)){
            rep(k, 0, c) if(j&(1<<k)) crystals.eb(i+1, k+1);
            idxj = j; break;
        }
    
    cout << crystals.size() << " " << ans << endl;
    rep(i, 0, crystals.size()) cout << crystals[i].ff << " " << crystals[i].ss << endl;

    exit(0);
}
