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
typedef bitset<50> bs;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 2e5+10, MOD = 1e9+7;

vl v;
vl seg;

ll build(int node, int l, int r){
    if(l == r) return seg[node] = (1LL<<v[l]);
    int m = (l+r)>>1;
    return seg[node] = (build(node*2, l, m) | build(node*2+1, m+1, r));
}

ll update(int node, int l, int r, int idx, int val){
    if(idx < l or idx > r) return seg[node];
    if(l == r) return seg[node] = (1LL<<val);
    int m = (l+r)>>1;
    return seg[node] = (update(node*2, l, m, idx, val) | update(node*2+1, m+1, r, idx, val));
}

ll query(int node, int l, int r, int ql, int qr){
    if(ql > r or qr < l) return 0;
    if(ql <= l and r <= qr) return seg[node]; 
    int m = (l+r)>>1;
    return (query(node*2, l, m, ql, qr) | query(node*2+1, m+1, r, ql, qr));
}

void solve(){
    int n, q, m; cin >> n >> q >> m;
    v = vl(n), seg = vl(4*n);
    rep(i, 0, n) cin >> v[i], v[i]--;

    build(1, 0, n-1);

    rep(i, 0, q){
        ll op, c, t; cin >> op >> c >> t; --c, --t;
        if(op == 1) cout << __builtin_popcountll(query(1, 0, n-1, c, t)) << endl;
        else update(1, 0, n-1, c, t);
    }
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
