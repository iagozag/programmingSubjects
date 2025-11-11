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

void no(){ cout << "N" << endl; }
void yes(){ cout << "Y" << endl; }

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

int n, m, g;

void solve(){
    vi p(n); int mp[n][n]; memset(mp, 0, sizeof mp);
    rep(i, 0, g){
        int a, b; char c; cin >> a >> c >> b;
        mp[min(a, b)][max(a, b)]++;
        if(c == '<') p[b] += 2;
        else p[a]++, p[b]++;
    }
    g = n*(n-1)/2*m-g;

    rep(i, 1, n) p[0] += 2*(m-mp[0][i]), g -= m-mp[0][i], mp[0][i] = m;
    rep(i, 1, n) if(p[0] <= p[i]) return no();

    Dinitz G(2+2*(n-1)+g, 0, 1+2*(n-1)+g);
    rep(i, 1, n) G.add(0, i, INF);
    
    int pp = n;
    rep(i, 1, n) rep(j, i+1, n) while(mp[i][j] < m)
        G.add(i, pp, 1), G.add(j, pp, 1), 
        G.add(pp, n+g+i-1, 2), G.add(pp++, n+g+j-1, 2),
        mp[i][j]++;

    rep(i, n+g, 2*n+g-1) G.add(i, 1+2*(n-1)+g, p[0]-1-p[i-n-g+1]);

    int f = 0;
    rep(i, 0, n) f += p[i];
    f += G.Flow();

    if(f == 2*(n*(n-1)/2*m)) return yes();
    return no();
}

int main(){ _
    while(cin >> n >> m >> g and n) solve();

    exit(0);
}
