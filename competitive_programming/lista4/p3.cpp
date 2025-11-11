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

void no(){ cout << "0" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 1e6+10, MOD = 1e9+7;

vector<bool> nprime(MAX);

void sieve(){
    nprime[0] = nprime[1] = 1;

    rep(i, 2, sqrt(MAX)+1) if(!nprime[i])
        for(int j = i*i; j < MAX; j += i) nprime[j] = 1;
}

void solve(){
    int n; cin >> n;
    set<int> st; 
    rep(i, 0, n){ int a; cin >> a; st.insert(a); }

    if(!st.count(1)){ cout << 0 << endl; return; }

    int i = 1;
    while(st.count(i) or nprime[i]) i++;

    if(i > 1e6){ cout << 1299708 << endl; return; }

    cout << i-1 << endl;
}

int main(){ _
    int ttt = 1; cin >> ttt;

    sieve();

    while(ttt--) solve();

    exit(0);
}
