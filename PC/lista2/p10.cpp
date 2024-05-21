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
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ll> vl;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const ll MAX = 1e6+10, MOD = 1e9+7;

vl pref(11);

ll dp(ll n){
    if(n < 10) return n*(n+1)/2;

    ll d = log10(n)+1, p = pow(10, d-1), c = n/p, rest = n-c*p;

    return (pref[d-1]%MOD*c%MOD+(c*(c-1)/2)*p%MOD+c*(rest+1)%MOD+dp(rest)%MOD)%MOD;
}

void solve(ll l, ll r){
    cout << (dp(r)%MOD-dp(l-1)%MOD+MOD)%MOD << endl;
}

int main(){ _
    ll l, r;

    ll p = 1;
    rep(i, 1, 11) pref[i] = (1LL*45*i%MOD*p%MOD)%MOD, p *= 10;

    while(cin >> l >> r) solve(l, r);

    exit(0);
}
