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

struct dinitz{
    int n, m = 0, s, t;
    vector<vi> g;
    vi level, ptr;
    queue<int> q;
    vector<Edge> edges;
    
    dinitz(int _n, int _s, int _t): n(_n), s(_s), t(_t) {
        g.resize(n), level.resize(n), ptr.resize(n);
    }

    void add(int u, int v, int c){
        edges.eb(u, v, c);
        edges.eb(v, u, 0);
        g[u].eb(m++), g[v].eb(m++);
    }

    bool bfs(){
        fill(all(level), -1);
        q.push(s), level[s] = 0;
        while(!q.empty()){
            int v = q.front(); q.pop();
            forr(ve, g[v]){
                if(level[edges[ve].v] != -1 or edges[ve].cap-edges[ve].f < 1) continue;
                level[edges[ve].v] = level[v]+1;
                q.push(edges[ve].v);
            }
        }

        return level[t] != -1;
    }

    int dfs(int v, int pushed){
        if(v == t or !pushed) return pushed;
        for(int& cid = ptr[v]; cid < g[v].size(); cid++){
            int id = g[v][cid], ve = edges[id].v;
            if(level[ve] != level[v]+1 or edges[id].cap-edges[id].f < 1)
                continue;
            int tr = dfs(ve, min(pushed, edges[id].cap-edges[id].f));
            if(!tr) continue;
            edges[id].f += tr;
            edges[id^1].f -= tr;
            return tr;
        }
        return 0;
    }

    int Flow(){
        int f = 0;
        while(bfs()){
            fill(all(ptr), 0);
            while(int push = dfs(s, INF))
                f += push;
        }

        return f;
    }
};

void solve(int n, int m){
    vi c(n); forr(x, c) cin >> x;
    vi sizes(m); forr(x, sizes) cin >> x;
    vector<vi> cat(m);
    rep(i, 0, m){
        cat[i].resize(sizes[i]+1);
        rep(j, 0, sz(cat[i])) cin >> cat[i][j]; 
    }

    dinitz G(n+m+2, 0, n+m+1);
    rep(i, 1, m+1){
        G.add(0, i, cat[i-1][0]);
        rep(j, 1, sz(cat[i-1])) G.add(i, m+cat[i-1][j], INF);
    }

    rep(i, m+1, n+m+1) G.add(i, n+m+1, c[i-m-1]);

    int sum = 0;
    rep(i, 0, m) sum += cat[i][0];
    cout << sum-G.Flow() << endl;
}

int main(){ _
    int n, m;
    while(cin >> n >> m) solve(n, m);

    exit(0);
}
