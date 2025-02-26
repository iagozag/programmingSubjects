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

const int MAX = 2e6+10, MOD = 1e9+7;

vi fact(MAX), mult(MAX, 1);
vi pref(MAX);

void sieve(){
    iota(all(fact), 0);
    fact[0] = fact[1] = -1;

    for(int i = 2; i < sqrt(MAX)+1; i++) if(fact[i] == i)
        for(int j = i; j < MAX; j += i){
            fact[j] = i, mult[j] = 1;
            if((j/i)%i == 0) mult[j] = mult[j/i]+1;  
        }
}

int fexp(int a, int b){
    int ans = 1;
    while(b){
        if(b&1) ans *= a;
        a *= a, b >>= 1;
    }
    return ans;
}

bool is_hyper(int n){
    int cnt = 1;
    while(n != 1)
        cnt *= mult[n]+1, n /= fexp(fact[n], mult[n]);
    return fact[cnt] == cnt;
}

void solve(int n){
    cout << pref[n]-pref[1] << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    sieve();

    rep(i, 2, MAX) pref[i] = pref[i-1]+is_hyper(i);

    while(cin >> ttt) solve(ttt);

    exit(0);
}
