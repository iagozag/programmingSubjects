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
typedef pair<double, double> pdd;
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

void solve(int n){
    vector<pll> v(n);
    forr(x, v) cin >> x.ff >> x.ss;
    vector<vl> dist(n, vl(n));
    rep(i, 0, n) rep(j, i+1, n)
        dist[i][j] = (v[i].ff-v[j].ff)*(v[i].ff-v[j].ff)+(v[i].ss-v[j].ss)*(v[i].ss-v[j].ss),
        dist[j][i] = dist[i][j];

    // rep(i, 0, n) rep(j, 0, n) cout << dist[i][j] << " \n"[j==n-1];

    ll ans = 0;
    rep(i, 0, n){
        map<ll, ll> mp;
        rep(j, 0, n) mp[dist[i][j]]++;
        forr(x, mp) ans += x.ss*(x.ss-1)/2;
    }

    cout << ans << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(cin >> ttt and ttt) solve(ttt);

    exit(0);
}
