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

const ll MAX = 2e5+10, MOD = 1e6;

void no(){ cout << "NO" << endl; }
void yes(ll ans){
    ans %= MOD;
    string s = to_string(ans);
    while(sz(s) < 6) s = '0'+s;
    cout << s << endl;
}

ll n, k, l;

vector<vl> mult(vector<vl> a, vector<vl> b){
    int sza = sz(a[0]), szb = sz(b[0]);
    vector<vl> ans(sza, vl(szb));

    rep(i, 0, sza) rep(j, 0, szb) rep(m, 0, sza)
        ans[i][j] += a[i][m]*b[m][j]%MOD;

    return ans;
}

vector<vl> fexp(vector<vl> a, ll b){
    vector<vl> ans(3, vl(3));
    rep(i, 0, 3) ans[i][i] = 1;
    while(b){
        if(b&1) ans = mult(ans, a);
        a = mult(a, a), b >>= 1;
    }
    return ans;
}

void solve(){
    if(n == 1) return yes(k);
    if(n == 2) return yes(l+k*k);

    vector<vl> mat = {{k, l, 0}, {1, 0, 0}, {0, 1, 0}}, cb = {{(l+k*k)%MOD}, {k}, {0}};
    mat = fexp(mat, n-2);
    mat = mult(mat, cb);
    
    return yes(mat[0][0]); 
}

int main(){ _
    while(cin >> n >> k >> l) n /= 5, l %= MOD, k %= MOD, solve();

    exit(0);
}
