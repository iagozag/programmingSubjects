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

const int MAX = 2e5+10, MOD = 1e9+7;

int n, m;
map<ii, int> mp;
vector<vi> g;
vector<bool> vis;
vi par, id, cycw, dist;
set<int> comp;

void mkcycle(int u, int v){
    comp.insert(v);
    cycw[v] += mp[{u, v}], id[v] = v, id[u] = v;
    while(par[u] != v) cycw[v] += mp[{par[u], u}], u = par[u], id[u] = v;
    cycw[v] += mp[{u,v}], id[u] = v;
}

void dfs(int v, int p){
    vis[v] = 1, par[v] = p;
    forr(ve, g[v]){
        if(ve == p) continue;
        if(vis[ve]){ if(id[ve] == -1) mkcycle(v, ve); }
        else dfs(ve, v);
    }
}

void dijkstra(int s){
    priority_queue<pair<int, int>> pq; pq.push({0, s});
    while(!pq.empty()){
        auto [w, v] = pq.top(); w -= 2*w; pq.pop();
        if(w >= dist[v]) continue;
        dist[v] = w;
        forr(ve, g[v])
            if(mp[{v, ve}]+w < dist[ve]) pq.push({-mp[{v, ve}]-w, ve});
    }
}

void solve(){
    g = vector<vi>(n), vis = vector<bool>(n), par = cycw = vi(n); comp.clear(), mp.clear();
    id = vi(n, -1), dist = vi(n, INF); iota(all(par), 0);
    rep(i, 0, m){
        int a, b, w; cin >> a >> b >> w; --a, --b;
        g[a].eb(b), g[b].eb(a);
        mp[{a, b}] = w, mp[{b, a}] = w;
    }

    dfs(0, -1);
    int q; cin >> q;
    rep(i, 0, q){
        int a, b; cin >> a >> b; --a;

        dist = vi(n, INF);
        dijkstra(a);

        int mi = INF;
        rep(x, 0, n){
            if(x == a) continue;
            if(id[x] != -1 and cycw[id[x]] >= b) mi = min(mi, (id[x] != id[a] ? 2*dist[x] : 0)+cycw[id[x]]);
        }
        cout << (mi != INF ? mi : -1) << endl;
    }
}

int main(){ _
    while(cin >> n >> m) solve();

    exit(0);
}
