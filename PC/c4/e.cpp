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

vector<vi> g;
vi distr, dist;

void bfsr(int s = 0){
    queue<int> q; q.push(s), distr[s] = 0;
    while(!q.empty()){
        int v = q.front(); q.pop();
        forr(ve, g[v]) if(distr[ve] == -1) distr[ve] = distr[v]+1, q.push(ve);
    }
}

void bfs(int s){
    queue<int> q; q.push(s), dist[s] = 0;
    while(!q.empty()){
        int v = q.front(); q.pop();
        forr(ve, g[v]) if(dist[ve] == -1) dist[ve] = dist[v]+1, q.push(ve);
    }
}

void solve(){
    int n, k, c; cin >> n >> k >> c;
    g = vector<vi>(n), distr = vi(n, -1), dist = vi(n, -1);
    rep(i, 0, n-1){
        int a, b; cin >> a >> b; --a, --b;
        g[a].eb(b), g[b].eb(a);
    }

    bfsr();

    int idx = 0;
    rep(i, 0, n) if(distr[idx] < distr[i]) idx = i;

    bfs(idx);

    if(c > k){ cout << 1LL*distr[idx]*k << endl; return; }
    
    ll ma = 0;
    rep(i, 0, n)
        ma = max(ma, 1LL*dist[i]*k - 1LL*min(distr[idx], distr[i])*c);
    cout << ma << endl;
}

int main(){ _
    int ttt; cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
