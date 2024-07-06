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

void solve(int n){
    vector<vector<double>> v(n, vector<double>(n));
    rep(i, 0, n) rep(j, 0, n) cin >> v[i][j];

    vector<pii> mat(n-1);
    rep(i, 0, n-1){
        int a, b; cin >> a >> b; --a, --b;
        mat[i] = {a, b};
    }

    vector<vi> g(2*n-1), g_t(2*n-1);
    rep(i, 0, n-1){
        auto [a, b] = mat[i]; 
        g_t[a].eb(n+i), g[n+i].eb(a);
        g_t[b].eb(n+i), g[n+i].eb(b);
    }

    int end;
    rep(i, 0, 2*n-1) if(!sz(g_t[i])){ end = i; break; }

    vector<unordered_set<int>> cnt(2*n-1);
    function<unordered_set<int>(int)> dfs = [&](int vv){
        if(vv < n) return cnt[vv] = {vv};
        unordered_set<int> ret;
        forr(ve, g[vv]) forr(x, dfs(ve)) ret.insert(x);

        return cnt[vv] = ret;
    };

    dfs(end);

    vector<vector<double>> memo(n, vector<double>(2*n-1, -1));
    function<double(int, int)> dp = [&](int ve, int ga){
        double& p = memo[ve][ga];

        if(p != -1) return p;
        if(ga < n) return p = (ve == ga);

        p = 0; double ps[2];
        rep(i, 0, 2){
            ps[i] = 0;

            if(!cnt[g[ga][i]].count(ve)) continue;

            rep(j, 0, n) if(j != ve and cnt[g[ga][!i]].count(j)){
                ps[i] += v[ve][j]*dp(j, g[ga][!i]);
            }
            ps[i] *= dp(ve, g[ga][i]);
        }
        return p = max(ps[0], ps[1]);
    };

    cout << fixed << setprecision(6) << dp(0, end) << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(cin >> ttt and ttt) solve(ttt);

    exit(0);
}
