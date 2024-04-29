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

const int MAX = 2e5+10;

vl id, sz;

int find(int x){
    return id[x] = (id[x] == x ? x : find(id[x]));
}

void unio(int p, int q){
    p = find(p), q = find(q);
    if(p == q) return;
    if(sz[p] > sz[q]) swap(p, q);
    id[p] = q, sz[q] += sz[p];
}

void solve(){
    ll n, m; cin >> n >> m;
    id = vl(n), sz = vl(n, 1); iota(all(id),0);

    vector<tuple<ll, ll, ll>> g(m); map<int, pair<ll,ll>> mp; map<int,int> edge; 
    for(int i = 0; i < m; i++){
        ll a, b, w; cin >> a >> b >> w; a--, b--;
        if(!mp.count(a) or mp[a].ff > w) mp[a] = {w, 1}, edge[a] = b; 
        else if(mp[a].ff == w) mp[a].ss++, edge[a] = b;
        if(!mp.count(b) or mp[b].ff > w) mp[b] = {w, 1}, edge[b] = a; 
        else if(mp[b].ff == w) mp[b].ss++, edge[b] = a;
        g[i] = {w, a, b};
    }

    ll ans = 0;
    forr(x, mp) if(x.ss.ss > 1){ ans++; mp.erase(edge[x.ff]); }
    cout << ans << endl;

}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}

