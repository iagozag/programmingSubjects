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

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 2e5+10, MOD = 1e9+7;

void solve(int n, int l, int m, int p){
    vi c(m), v(m); forr(x, c) cin >> x; forr(x, v) cin >> x;

    vector<vi> dp(n+1, vi(m+1, INF));
    dp[0][l-1] = 0;
    rep(i, 0, n) rep(j, 0, m){
        if(j < m-1) dp[i+1][j+1] = min(dp[i+1][j+1], c[j+1]+dp[i][j]); 
        dp[i+1][0] = min(dp[i+1][0], c[0]+p-v[j]+dp[i][j]);
    }

    rep(i, 0, n+1) rep(j, 0, m+1) cout << dp[i][j] << " \n"[j==m];

    int mi = dp[n][0], idx = 0;
    rep(j, 1, m) if(mi > dp[n][j]) mi = dp[n][j], idx = j;
    cout << mi << endl;

    vi ans;
    repr(i, n, 1){
        if(idx > 0){ idx--; continue; }
        rep(j, 0, m)
            if(dp[i-1][j]+c[0]+p-v[j] == dp[i][0]) idx = j;
        ans.eb(i);
    }

    reverse(all(ans));
    if(sz(ans) == 0) cout << 0 << endl;
    else rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i==sz(ans)-1];
}

int main(){ _
    int n, l, m, p;
    while(cin >> n >> l >> m >> p) solve(n, l, m, p);

    exit(0);
}
