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

const int MAX = 2e5+10;

vector<vector<ii>> g;
vector<int> dist;

void dijkstra(int o){
    priority_queue<ii> pq; pq.push({0, o});
    while(!pq.empty()){
        auto [w, v] = pq.top(); w -= 2*w; pq.pop();
        if(w >= dist[v]) continue;
        dist[v] = w;

        for(auto [ve, wg]: g[v]){
            if(w+wg < dist[ve]) pq.push({-w-wg, ve});
        }
    }
}

void solve(int n, int m, int k, double p){
    g = vector<vector<ii>>(n), dist = vi(n, INF);
    vector<ii> edges(m); forr(x, edges) cin >> x.ff >> x.ss, --x.ff, --x.ss;

    int qc; cin >> qc; vi costs(n); rep(i, 0, qc){ int a; cin >> a; --a; costs[a]++; }

    for(auto [a, b]: edges){
        g[a].eb(b, costs[b]), g[b].eb(a, costs[a]);
    }

    int o, d; cin >> o >> d; --o, --d;
    dijkstra(o);

    double ans = pow(p, costs[o]+dist[d]);
    printf("%.3f\n", ans);
}

int main(){ _
    int n, m, k; double p;

    while(cin >> n >> m >> k >> p) solve(n, m, k, p);

    exit(0);
}
