#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define rep(i, x, n) for (auto i = x; i < n; i++)
#define repr(i, n, x) for (auto i = n; i >= x; i--)
#define forr(x, v) for (auto& x : v)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())
#define endl '\n'
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void no() { cout << "NO" << endl; }
void yes() { cout << "YES" << endl; }

const int MAX = 2e5 + 10, MOD = 1e9 + 7;

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int _v, int _u, long long _cap) : v(_v), u(_u), cap(_cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
        adj.resize(_n);
        level.resize(_n);
        ptr.resize(_n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

vector<vector<int>> memo(100, vector<int>(100));
vector<vector<int>> vis(100, vector<int>(100, -1));
int cnt = 0;

int lcs(vector<int>& person, vector<int>& toy, int i, int j) {
    if (i == sz(person) or j == sz(toy))
        return 0;
    int& v = vis[i][j];
    int& p = memo[i][j];
    if (v >= cnt)
        return p;
    v = cnt;

    if (person[i] == toy[j])
        return p = 1 + lcs(person, toy, i + 1, j + 1);
    return p = max(lcs(person, toy, i + 1, j), lcs(person, toy, i, j + 1));
}

void solve(int n, int m) {
    vector<string> f(n), t(m);
    forr(x, f) cin >> x;
    forr(x, t) cin >> x;

    vector<vi> fr(n), to(m);
    rep(i, 0, n) {
        map<char, int> mp;
        forr(x, f[i]) {
            if (!mp.count(x)) mp[x] = (x - 'A') + 1;
            fr[i].eb(mp[x]), mp[x] += 26;
        }
    }
    rep(i, 0, m) {
        map<char, int> mp;
        forr(x, t[i]) {
            if (!mp.count(x)) mp[x] = (x - 'A') + 1;
            to[i].eb(mp[x]), mp[x] += 26;
        }
    }

    vector<vector<bool>> can(m, vector<bool>(n));
    rep(i, 0, n) rep(j, 0, m) {
        can[j][i] = !((fr[i].size() + to[j].size() - 2 * lcs(fr[i], to[j], 0, 0)) % 5);
        cnt++;
    }

    Dinic F(2 + n + m, 0, n + m + 1);
    rep(i, 1, m + 1) F.add_edge(0, i, 1);
    rep(i, 1, m + 1)
        rep(j, 0, n) if (can[i - 1][j])
            F.add_edge(i, m + 1 + j, 1);

    rep(i, m + 1, m + 1 + n) F.add_edge(i, m + 1 + n, 1);

    double ans = ((1.0 * F.flow()) / (1.0 * n)) * 100.0;
    cout << "P = " << fixed << setprecision(2) << ans << endl;
}

int main() { _
    int n, m;
    while (cin >> n >> m and n) solve(n, m);

    return 0;
}

