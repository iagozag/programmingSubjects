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
    int u, v, cap, f = 0;
    Edge(int _u, int _v, int _cap): u(_u), v(_v), cap(_cap) {}
};

int n, m, s, t;
vector<vi> g;
vector<Edge> edges;
vi level, ptr;

void add(int u, int v, int cap){
    edges.eb(u, v, cap);
    edges.eb(v, u, 0);
    g[u].eb(m++), g[v].eb(m++);
}

bool bfs(){
    fill(all(level), -1); 
    queue<int> q; q.push(s), level[s] = 0;
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

int dfs(int v, int pushed){
    if(!pushed or v == t) return pushed;
    for(int& cid = ptr[v]; cid < sz(g[v]); cid++){
        int id = g[v][cid], ve = edges[id].v;
        if(level[ve] != level[v]+1 or edges[id].cap-edges[id].f < 1) continue;
        int tr = dfs(ve, min(pushed, edges[id].cap-edges[id].f));
        if(!tr) continue;
        edges[id].f += tr, edges[id^1].f -= tr;
        return tr;
    }
    return 0;
}

int mflow(){
    int f = 0;
    while(bfs()){
        fill(all(ptr), 0);
        while(int push = dfs(s, INF)) f += push;
    }

    return f;
}

void solve(){
    int mm; cin >> n >> mm;
    g = vector<vi>(n), level = ptr = vi(n), edges.clear(), m = 0;

    map<pii, int> mp;
    rep(i, 0, mm){
        int a, b, c; cin >> a >> b >> c; --a, --b;
        mp[{min(a, b), max(a, b)}] = c;
    }
    for(auto x: mp) add(x.ff.ff, x.ff.ss, x.ss), add(x.ff.ss, x.ff.ff, x.ss);

    s = 0; int ans = INF;
    rep(i, 1, n){
        t = i;
        forr(x, edges) x.f = 0;
        ans = min(ans, mflow());
    }

    cout << ans << endl;
}

int main(){ _
    int ttt = 1; cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
