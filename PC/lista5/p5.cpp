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
vi seg, lz;
vi live;

void push(int node, int l, int r){
    if(l == r or lz[node] == -1) return;

    seg[node<<1] = lz[node];
    lz[node<<1] = lz[node];
    seg[(node<<1)+1] = lz[node];
    lz[(node<<1)+1] = lz[node];
    lz[node] = -1;
}

void kill(int node, int l, int r, int x){
    push(node, l, r);
    if(l == r){
        live[node] = 0;
        return;
    }

    int m = l+(r-l)/2;
    if(x-seg[node<<1] > t) kill(node<<1, l, m, x);
    if(x-seg[(node<<1)+1] > t) kill((node<<1)+1, m+1, r, x);

    live[node] = live[node<<1] | live[(node<<1)+1];
}

int update(int node, int l, int r, int ul, int ur, int x){
    if(!live[node]) return INF;
    push(node, l, r);
    if(ul > r or ur < l) return seg[node];
    if(ul <= l and r <= ur){
        if(x-seg[node] > t) kill(node, l, r, x);
        seg[node] = x, lz[node] = x;
        return seg[node];
    }
    int m = l+(r-l)/2;
    return seg[node] = min(update(node<<1, l, m, ul, ur, x), update((node<<1)+1, m+1, r, ul, ur, x));
}

vi ans;

void get_ans(int node, int l, int r){
    if(!live[node]) return;
    push(node, l, r);
    if(l == r){
        if(live[node]) ans.eb(l+1);
        return;
    }
    int m = l+(r-l)/2;
    get_ans(node<<1, l, m), get_ans((node<<1)+1, m+1, r);
}

void solve(){
    seg = vi(4*n), lz = vi(4*n, -1), live = vi(4*n, 1);

    rep(i, 0, k){
        int a, b; cin >> a >> b; --a, --b;
        update(1, 0, n-1, a, b, i+1);
    }

    update(1, 0, n-1, 0, n-1, k+1);

    ans.clear();
    get_ans(1, 0, n-1);
    if(sz(ans) == 0){
        cout << 0 << endl;
        return;
    }
    cout << sz(ans) << " ";
    rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i==sz(ans)-1]; 
}

int main(){ _
    while(cin >> n >> k >> t) solve();

    exit(0);
}
