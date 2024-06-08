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

    pair<ll, bitset<3601>> memo[n][2];

    function<pair<ll, bitset<3601>>(int, bool)> dp = [&](int i, bool can) -> pair<ll, bitset<3601>>{
        pair<ll, bitset<3601>>& p = memo[i][can];

        if(p.ff != -1) return p;

        bool b = false;
        pair<ll, bitset<3601>> ma, ma2; ma = ma2 = {0, bitset<3601>()}; 
        forr(ve, g[i]) if(!p.ss.test(ve)){
            b = true;
            if(can){
                pair<ll, bitset<3601>> m1 = dp(ve, 0);
                if(ma.ff < val[i]+m1.ff) ma = m1, ma.ss.set(i);
            }
            pair<ll, bitset<3601>> m2 = dp(ve, 1);
            if(ma2.ff < m2.ff) ma2 = m2;
        }

        if(!b){
            pair<ll, bitset<3601>> got = {val[i], bitset<3601>()}; got.ss.set(i);
            pair<ll, bitset<3601>> ngot = {0, bitset<3601>()}; 
            return (can ? got : ngot);
        }

        return ma.ff > ma2.ff ? ma : ma2;
    };

    set<int> ok; vector<pii> vert;
    rep(i, 0, n) rep(j, 0, 2) memo[i][j] = {-1, bitset<3601>()};
    rep(i, 0, n){
        if(ok.count(id[i])) continue;
        pair<ll, bitset<3601>> a = dp(i, 0);
        pair<ll, bitset<3601>> b = dp(i, 1);
        if(a.ff > b.ff){
            ans += a.ff;
            rep(j, 0, n) if(a.ss.test(j)) vert.eb(mp_r[j]);
        } else{
            ans += b.ff;
            rep(j, 0, n) if(b.ss.test(j)) vert.eb(mp_r[j]);
        }

        ok.insert(id[i]);
    }

    cout << ans << endl;
    rep(i, 0, sz(vert)) cout << vert[i].ff << " " << vert[i].ss << " \n"[i==sz(vert)-1];
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}

