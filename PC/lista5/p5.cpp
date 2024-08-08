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

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 2e5+10, MOD = 1e9+7;

int n, k, t;
vi v, seg, lz;

void push(int node, int l, int r){
     
}

int build(int node, int l, int r){
    if(l == r) return seg[node] = t;
    int m = (l+r)>>1;
    return build(node*2, l, m)+build(node*2+1, m+1, r);
}

int update(int node, int l, int r, int ul, int ur, int val){
    if(ul > r or ur < l) return seg[node];
    if(ul <= l and r <= ur){

    }
    if(lazy[node]) push(node, l, r);
    int m = (l+r)>>1;
    return seg[node] = update(node*2, l, m, ul, ur, val)+update(node*2+1, m+1, r, ul, ur, val);
}

vi ans;
void querym(int node, int l, int r){
    if(l == r){
        ans[l] = seg[node];
        return;
    }
    if(lazy[node]) push(node, l, r);
    int m = (l+r)>>1;
    querym(node*2, l, m), querym(node*2+1, m+1, r);
}

void solve(){
    seg = lz = vi(4*n);
    rep(i, 0, k){
        int a, b; cin >> a >> b; --a, --b;
        update(1, 0, n-1, a, b, t);
        lz[1] -= 1;
    }

    ans = vi(n);
    querym(1, 0, n-1);
    sort(all(ans));
    cout << sz(ans) << " ";
    forr(x, ans) cout << x << " ";
    cout << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(cin >> n >> k >> t) solve();

    exit(0);
}
