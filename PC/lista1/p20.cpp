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

const int MAX = 1e3+10;

vector<vector<ii>> g(MAX);
vi dist(MAX, INF);

void dijkstra(int x){
    priority_queue<ii> pq; pq.push({0, x});
    while(!pq.empty()){
        auto [d, i] = pq.top(); d-=2*d; pq.pop();
        if(d >= dist[i]) continue;
        dist[i] = d;
        for(auto [b, a]: g[i]){
            if(dist[b] > d+a) pq.push({-d-a, b});
        }
    }
}

void solve(){
    int n, m; cin >> n >> m;
    rep(i, 0, m){
        int a, b, c; cin >> a >> b >> c; a--, b--;
        g[a].eb(b, c), g[b].eb(a, c);
    }

    int a, mi = INF, ma = -1; cin >> a; a--; dijkstra(a);
    rep(i, 0, n){
        if(i == a) continue;
        mi = min(mi, dist[i]), ma = max(ma, dist[i]);
    }

    cout << ma-mi << endl;
}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}
