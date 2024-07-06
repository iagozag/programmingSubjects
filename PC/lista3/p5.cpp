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

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 2e5+10, MOD = 1e9+7;

struct Edge{
    int u, v;
    ll cap, f = 0;
    Edge(int _u, int _v, int _cap): u(_u), v(_v), cap(_cap) {}
};

struct Dinitz{
    vector<Edge> edges;
    vector<vi> g;
    vi ptr, level;
    int n, m = 0, s, t;
    queue<int> q;

    Dinitz(int _n, int source, int sink): n(_n), s(source), t(sink) {
        g.resize(n), ptr.resize(n), level.resize(n);
    }

    void add(int u, int v, int c){
        edges.eb(u, v, c);
        edges.eb(v, u, 0);
        g[u].eb(m++), g[v].eb(m++);
    }

    bool bfs(){
        fill(all(level), -1);
        q.push(s); level[s] = 0;
        while(!q.empty()){
            int v = q.front(); q.pop();
            forr(ve, g[v]){
                if(edges[ve].cap-edges[ve].f < 1 or level[edges[ve].v] != -1) continue;
                level[edges[ve].v] = level[v]+1;
                q.push(edges[ve].v);
            }
        }

        return level[t] != -1;
    }

    ll dfs(int v, ll pushed){
        if(!pushed or v == t) return pushed;
        for(int& cid = ptr[v]; cid < sz(g[v]); cid++){
            int id = g[v][cid], ve = edges[id].v;
            if(level[ve] != level[v]+1 or edges[id].cap-edges[id].f < 1) continue;
            ll tr = dfs(ve, min(pushed, edges[id].cap-edges[id].f));
            if(!tr) continue;
            edges[id].f += tr;
            edges[id^1].f -= tr;
            return tr;
        }

        return 0;
    }

    ll Flow(){
        ll f = 0;
        while(bfs()){
            fill(all(ptr), 0);
            while(ll push = dfs(s, LINF))
                f += push;
        }
        return f;
    }
};

int n, m, k;
vector<vector<pii>> g;
vector<vi> g_t;
vi dist;

void bfs(int s){
    dist = vi(n, INF); dist[s] = 0;
    queue<int> q; q.push(s); 
    while(!q.empty()){
        auto v = q.front(); q.pop();

        forr(ve, g_t[v]) if(dist[ve] > dist[v]+1)
            dist[ve] = dist[v]+1, q.push(ve); 
    }
}

bool check(int x){
    int mp[n][x+1]; int l = 1;
    rep(i, 0, n) rep(j, 1, x+1) mp[i][j] = l++;

    Dinitz G(l+1, 0, l);
    rep(i, 1, x+1) G.add(0, mp[0][i], k);
    rep(i, 1, x+1) G.add(mp[n-1][i], l, k);

    int vis[n][x+1]; memset(vis, 0, sizeof vis);
    queue<pii> q; rep(i, 1, x+1) q.push({0, i});
    while(!q.empty()){
        auto [v, t] = q.front(); q.pop();
        if(v == n-1 or t >= x or vis[v][t]) continue;

        vis[v][t] = 1;
        forr(ve, g[v]) if(dist[ve.ff]+t <= x)
            G.add(mp[v][t], mp[ve.ff][t+1], ve.ss), q.push({ve.ff, t+1});
    }

    return G.Flow() >= k;
}

void solve(){
    g = vector<vector<pii>>(n), g_t = vector<vi>(n);
    rep(i, 0, m){
        int x, y, z; cin >> x >> y >> z; --x, --y;
        g[x].eb(y, z), g_t[y].eb(x);
    }

    bfs(n-1);

    int lo = 0, hi = 1, ans;
    while(!check(hi)) lo = hi, hi <<= 1;
    while(lo <= hi){
        int mid = lo+(hi-lo)/2;
        if(check(mid)) ans = mid, hi = mid-1;
        else lo = mid+1;
    }

    cout << ans-1 << endl;
}

int main(){ _
    while(cin >> n >> m >> k and n) solve();
    cout << endl;

    exit(0);
}
