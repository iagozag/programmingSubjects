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
    vi ila, ptr, level;
    int n, m = 0, s, t;

    Dinitz(int _n, int source, int sink): n(_n), s(source), t(sink) {
        g = vector<vi>(n);
        ila = ptr = vi(n);
    }

    void add(int u, int v, int c){
        edges.eb(u, v, c);
        edges.eb(v, u, 0);
        g[u].eb(m++), g[v].eb(m++);
    }

    bool bfs(){
        level = vi(n, -1);
        queue<int> q; q.push(s); level[s] = 0;
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
            ptr = vi(n);
            while(ll push = dfs(s, LINF))
                f += push;
        }
        return f;
    }
};

void solve(int n, int m, int k){
    vi c(n); forr(x, c) cin >> x;
    Dinitz F(n+m+2, 0, n+m+1);

    rep(i, 1, m+1) F.add(0, i,  1);
    rep(i, 0, k){
        int a, b; cin >> a >> b;
        F.add(b, a+m, 1);
    }

    rep(i, m+1, n+m+1) F.add(i, n+m+1, c[i-m-1]);

    cout << F.Flow() << endl;
}

int main(){ _
    int ttt = 1, n, m, k; // cin >> ttt;

    while(cin >> n >> m >> k){
        cout << "Instancia " << ttt++ << endl;
        solve(n, m, k);
        cout << endl;
    }

    exit(0);
}
