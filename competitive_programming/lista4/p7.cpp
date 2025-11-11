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

const int MAX = 2e5+10, MOD = 13371337;

vector<vl> mult(vector<vl> a, vector<vl> b){
    int sza = sz(a[0]), szb = sz(b[0]);
    vector<vl> ans(sza, vl(szb));
    rep(i, 0, sza) rep(j, 0, szb) rep(k, 0, sza) ans[i][j] += a[i][k]*b[k][j]%MOD;
    return ans;
}

vector<vl> fexp(vector<vl> a, ll b){
    vector<vl> ans(5, vl(5));
    rep(i, 0, 5) ans[i][i] = 1;
    while(b){
        if(b&1) ans = mult(ans, a);
        a = mult(a, a), b >>= 1;
    }
    return ans;
}

void solve(int n){
    vl v(4); forr(x, v) cin >> x;

    vector<vl> mat(5, vl(5));
    mat[0] = {1, 1, 1, 1, 0};
    rep(i, 0, 4) mat[i+1][i] = 1;

    mat = fexp(mat, n-4);
    mat = mult(mat, {{v[3]},{v[2]}, {v[1]}, {v[0]}, {0}});
    ll ans = 0;
    rep(i, 0, 4) ans += mat[i][0], ans %= MOD;
    cout << ans << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(cin >> ttt and ttt) solve(ttt);

    exit(0);
}
