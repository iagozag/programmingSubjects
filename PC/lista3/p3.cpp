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

void no(){ cout << "N" << endl; }
void yes(){ cout << "Y" << endl; }

const int MAX = 2e5+10, MOD = 1e9+7;

int n, m, g;

void solve(){
    vi p(n); map<pii, int> mp;
    rep(i, 0, g){
        int a, b; char c; cin >> a >> c >> b;
        mp[{min(a, b), max(a, b)}]++;
        if(c == '<') p[b] += 2;
        else p[a]++, p[b]++;
    }

    rep(i, 0, n) rep(j, 0, n){
        if(i == j) continue;
        if(!mp.count({min(i, j), max(i, j)})) mp[{min(i, j), max(i, j)}] = 0;
    }

    forr(x, mp){
        auto [a, b] = x.ff;
        // cout << a << " " << b << ": " << x.ss << endl;
        if(x.ss == m) continue;
        if(a == 0) p[0] += 2*(m-x.ss);
        else{
            while(x.ss < m){
                if(p[a] == p[b]) p[a]++, p[b]++;
                else if(p[a] > p[b] and p[a]+2 >= p[0]) p[b] += 2;
                else p[a] += 2;
                x.ss++;
            }
        }
    }

    // rep(i, 0, n) cout << p[i] << " ";

    rep(i, 1, n) if(p[i] >= p[0]) return no();
    return yes();
}

int main(){ _
    while(cin >> n >> m >> g and n != 0) solve();

    exit(0);
}
