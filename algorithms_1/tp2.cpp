#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>

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

typedef pair<int,int> ii;
typedef vector<int> vi;

const int INF = 0x3f3f3f3f;

int n, m, j, t, cash, k; 
vector<vector<ii>> g; vector<vi> g_t;

vector<vi> monsters; set<ii> block;
vi par; vi bfsdist; 
map<ii,ii> parr; map<ii, int> dist; map<ii, bool> viss;

void bfs(int s = 0){
    par = bfsdist = vi(n, INF), par[s] = s, bfsdist[s] = 0;
    queue<int> q; q.push(s);
    while(!q.empty()){
        int v = q.front(); q.pop();
        forr(ve, g_t[v]){
            if(bfsdist[v]+1 < bfsdist[ve]) bfsdist[ve] = bfsdist[v]+1, par[ve] = v, q.push(ve);
            else if(bfsdist[v]+1 == bfsdist[ve] and v < par[ve]) par[ve] = v;
        }
    }
}

ii dijkstra(int s = 0){
     dist[{s, 0}] = 0, parr[{s, 0}] = {s, 0};

    priority_queue<tuple<int,int,int, int>> pq; pq.push({0, 0, s, 0});
    while(!pq.empty()){
        auto [w, money, v, turn] = pq.top(); pq.pop();

        if(v == n-1) return {v, turn};
        if(viss[{v, turn}] or turn+1 > t) continue;

        viss[{v, turn}] = 1, w *= -1, money += cash, turn++;
        for(auto [ve, dd]: g[v]) if(!block.count({ve, turn-1}) and !block.count({ve, turn})){
            if(!dist.count({ve, turn})) dist[{ve, turn}] = INF;

            if(money >= dd and dist[{v, turn-1}]+dd < dist[{ve, turn}])
                parr[{ve, turn}] = {v, turn-1}, dist[{ve, turn}] = dist[{v, turn-1}]+dd, 
                pq.push({-dist[{ve, turn}], money-dd, ve, turn});
        }
    }

    return {-1, -1};
}

void printt(ii p){
    cout << dist[p] << " " << p.ss << endl;

    vi path;
    while(p != parr[p]) path.eb(p.ff), p = parr[p];
    path.eb(0);

    for(int i = path.size()-1; i >= 0; i--) cout << path[i]+1 << " \n"[i == 0];
}

int main(){ _
    cin >> n >> m >> j >> t >> cash;
    g = vector<vector<ii>>(n), g_t = vector<vi>(n);
    vi mon(j); monsters = vector<vi>(j);

    forr(x, mon) cin >> x, --x;

    rep(i, 0, n) g[i].eb(i, 1);
    rep(i, 0, m){ int a, b, w; cin >> a >> b >> w; --a, --b; g[a].eb(b, w), g_t[b].eb(a); }

    bfs();

    rep(i, 0, j){
        int b = 0;
        if(par[mon[i]] != INF){
            int p = mon[i];
            while(true){ monsters[i].eb(p), block.insert({p, b++}); if(p == 0) break; p = par[p]; }

            rep(l, b, t+1) block.insert({0, l});
        } else{
            monsters[i].eb(mon[i]);
            rep(l, 0, t+1) block.insert({mon[i], l});
        }
    }

    ii p = dijkstra();
    cout << (p.ff == -1 ? 0 : 1) << endl;
    forr(x, monsters){
        cout << x.size() << " ";
        rep(i, 0, x.size()) cout << x[i]+1 << " \n"[i == x.size()-1];
    }

    if(p.ff != -1) printt(p);
    else{
        int ve = 0, ma_t = 0;
        forr(x, dist){
            if(x.ss == INF) continue;
            if(x.ff.ss > ma_t or (x.ff.ss == ma_t and x.ss < dist[{ve, ma_t}]))
                ve = x.ff.ff, ma_t = x.ff.ss;
        }

        if(block.count({ve, ma_t+1})) 
            dist[{ve, ma_t+1}] = dist[{ve, ma_t}]+1, parr[{ve, ma_t+1}] = {ve, ma_t}, ma_t++;

        printt({ve, ma_t});
    }    

    exit(0);
}
