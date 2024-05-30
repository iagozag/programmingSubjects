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
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

void solve(){
    int l, c, n, ans = 0; cin >> l >> c >> n;
    map<pii, int> mp; map<int, pii> mp_r;
    vector<vi> g(l*c); vi val(l*c, -1); vector<vector<pii>> edges(n);

    rep(i, 0, n){
        int x, y, v, di, ci, ei, bi; cin >> x >> y >> v >> di >> ci >> ei >> bi; --x, --y;
        mp[{x, y}] = i, mp_r[i] = {x, y}; val[i] = v;

        if(di) edges[i].eb(x, (y+1)%c);
        if(ci) edges[i].eb((x-1+l)%l, y);
        if(ei) edges[i].eb(x, (y-1+c)%c);
        if(bi) edges[i].eb((x+1)%l, y);
    }
    rep(i, 0, n) forr(x, edges[i]) g[i].eb(mp[x]);

    vector<bool> vis(n); vi id(n);
    auto dfs = [&](auto self, int i, int p) -> void{
        id[i] = p, vis[i] = 1;
        forr(ve, g[i]) if(!vis[ve]) self(self, ve, p);
    };

    rep(i, 0, n) if(!vis[i]) dfs(dfs, i, i);

    auto dp = [&](auto self, int i, bool can, set<int> s) -> int{
        int ma = 0, ma2 = 0; s.insert(i);
        forr(ve, g[i]) if(!s.count(ve)){
            if(can) ma = max(ma, val[i]+self(self, ve, 0, s));
            ma2 = max(ma2, self(self, ve, 1, s));
        }

        return max(ma, ma2);
    };

    set<int> ok;
    rep(i, 0, n){
        if(ok.count(id[i])) continue;
        ans += dp(dp, i, 1, set<int>()), ok.insert(id[i]);
    }

    cout << ans << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}

