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

const int MAX = 4e5+10, MOD = 9;

int lazy[MAX];
int seg[MAX][MOD];

void push(int node, int l, int r){
    rotate(seg[node<<1], seg[node<<1]+MOD-lazy[node], seg[node<<1]+MOD);
    rotate(seg[(node<<1)+1], seg[(node<<1)+1]+MOD-lazy[node], seg[(node<<1)+1]+MOD);
    if(l != r) lazy[node<<1] = (lazy[node<<1]+lazy[node])%MOD,
               lazy[(node<<1)+1] = (lazy[(node<<1)+1]+lazy[node])%MOD;
    lazy[node] = 0;
}

int* build(int node, int l, int r){
    if(l == r){
        seg[node][1] = 1;
        return seg[node];
    }
    int m = (l+r)>>1;
    build(node<<1, l, m), build((node<<1)+1, m+1, r);
    rep(i, 0, 9) seg[node][i] = seg[node<<1][i]+seg[(node<<1)+1][i];
    return seg[node];
}

int* update(int node, int l, int r, int ul, int ur, int val){
    if(ul > r or ur < l) return seg[node];
    if(ul <= l and r <= ur){
        rotate(seg[node], seg[node]+MOD-val, seg[node]+MOD);
        if(l != r) lazy[node] += val, lazy[node] %= MOD;
        return seg[node];
    }
    if(lazy[node]) push(node, l, r);

    int m = (l+r)>>1;
    update(node<<1, l, m, ul, ur, val),
    update((node<<1)+1, m+1, r, ul, ur, val);

    rep(i, 0, 9) seg[node][i] = seg[node<<1][i]+seg[(node<<1)+1][i];
    return seg[node];
}

int cnt[MOD];

void query(int node, int l, int r, int ql, int qr){
    if(ql > r or qr < l) return;
    if(ql <= l and r <= qr){
        rep(i, 0, 9) cnt[i] += seg[node][i];
        return;
    }
    if(lazy[node]) push(node, l, r);

    int m = (l+r)>>1;
    query(node<<1, l, m, ql, qr),
    query((node<<1)+1, m+1, r, ql, qr);
}

int ans[MAX];

void querym(int node, int l, int r){
    if(l == r){
        int idx = 0;
        rep(i, 1, 9) if(seg[node][i] >= seg[node][idx]) idx = i;
        ans[l] = idx;
        return;
    }
    if(lazy[node]) push(node, l, r);
    int m = (l+r)>>1;
    querym(node<<1, l, m), querym((node<<1)+1, m+1, r);
}

void solve(){
    int n, q; cin >> n >> q;
    fill(&seg[0][0], &seg[0][0] + MAX * MOD, 0), fill(lazy, lazy+MAX, 0);

    build(1, 0, n-1);

    rep(qq, 0, q){
        int a, b; cin >> a >> b;
        fill(cnt, cnt+MOD, 0);
        query(1, 0, n-1, a, b);
        int idx = 0;
        rep(i, 1, 9) if(cnt[i] >= cnt[idx]) idx = i;
        update(1, 0, n-1, a, b, idx);
    }

    querym(1, 0, n-1);
    rep(i, 0, n) cout << ans[i] << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
