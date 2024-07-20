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

void no(){ cout << "?" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 2e7+1, MOD = 2;

bitset<MAX> is_c;
vi mult(MAX);

void sieve(){
    is_c.set(0), is_c.set(1), mult[2] = 1;
    for(int j = 4; j < MAX; j += 2){ 
        is_c.set(j);
        if((j/2) % 2 == 0) mult[j] = mult[j/2]+1;
        else mult[j] = 1;
    }
    for(int i = 3; i < sqrt(MAX)+1; i += 2) if(!is_c.test(i))
        for(int j = i*i; j < MAX; j += i) is_c.set(j);
}

void solve(){
    int n, m; cin >> n >> m;
    if(n == m) return no();
    if(n > m) swap(n, m);
    
    sieve();

    int N = 0, K = m-n;
    rep(i, n, m+1) N += !is_c.test(i);

    if(!N){ cout << "Bob" << endl; return; } 

    ll cnt = 0;
    rep(i, 0, K+N) cnt += mult[i];

    rep(i, 0, N) cnt -= mult[i];
    rep(i, 0, K+1) cnt -= mult[i];

    cout << (cnt > 0 ? "Bob" : "Alice") << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
