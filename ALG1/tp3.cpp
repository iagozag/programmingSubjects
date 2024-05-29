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

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int l, c, n;
map<pii, int> mp; map<int, pii> mp_r;
vector<vi> g;
vi val;

int dp(int i, int got){
    if(i == n) return 0;

    int ans = 0;
    if(got){
        forr(ve, g[i]) ans = max(ans, val[i]+dp(ve, 0));
    }
    int ans2 = 0;
    forr(ve, g[i]) ans2 = max(ans2, dp(ve, 1));
    return max(ans, ans2);
}

void solve(){
    cin >> l >> c >> n;
    g = vector<vi>(l*c), val = vi(n);
    rep(i, 0, n){
        int x, y, v, di, ci, ei, bi; cin >> x >> y >> v >> di >> ci >> ei >> bi;
        mp[{x, y}] = i, mp_r[i] = {x ,y}, val[i] = v;
        if(di) g[i].eb(mp[{x, (y+1)%c}]);
        if(ci) g[i].eb(mp[{(x-1+l)%l, y}]);
        if(ei) g[i].eb(mp[{x, (y-1+c)%c}]);
        if(bi) g[i].eb(mp[{(x+1)%l, y}]);
    }

    cout << max(dp(0, 1), dp(0, 0)) << endl; 
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
