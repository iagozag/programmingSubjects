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

typedef tuple<int,int,int> ttt;

vi id, rk;

int find(int x){
    return id[x] = (id[x] == x ? x : find(id[x]));
}

void unio(int a, int b){
    a = find(a), b = find(b);
    if(a == b) return;
    if(rk[a] > rk[b]) swap(a, b);
    id[a] = b;
    if(rk[a] == b) rk[b]++;
}

void solve(){
    int n; cin >> n; id = vi(n), rk = vi(n); iota(all(id), 0);
    vector<ttt> edges(n);
    rep(i, 0, n){
        int a, b, w; cin >> a >> b >> w; --a, --b;
        edges[i] = {w, a, b};
    }
    sort(all(edges));

    ll ans2 = 0;
    for(auto [w, a, b]: edges){
        if(find(a) != find(b)) ans2+=w,unio(a,b);
    }

    id = vi(n), rk = vi(n); iota(all(id), 0);
    sort(all(edges), greater<ttt>());
    ll ans1 = 0;
    for(auto [w, a, b]: edges){
        if(find(a) != find(b)) ans1+=w,unio(a,b);
    }
    cout << ans1 << endl << ans2 << endl;

}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}
