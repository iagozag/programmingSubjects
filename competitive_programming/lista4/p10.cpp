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

void no(){ cout << "Nada" << endl; }
void yes(){ cout << "Primo" << endl; }

const int MAX = 1e5+10, MOD = 1e9+7;

vi fact(MAX);

void sieve(){
    iota(all(fact), 0);
    fact[0] = fact[1] = -1;
    rep(i, 2, sqrt(MAX)+1){
        if(fact[i] == i)
            for(int j = i; j < MAX; j += i)
                fact[j] = i;
    }
}

void solve(int n){
    if(fact[n] != n) return no();
    string s = to_string(n);
    forr(x, s) if(fact[(x-'0')] != (x-'0')) return yes();
    cout << "Super" << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    sieve();

    while(cin >> ttt) solve(ttt);

    exit(0);
}
