#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,x,n) for(auto i=x;i<n;i++)
#define repr(i,n,x) for(auto i=n;i>=x;i--)
#define forr(x, v) for(auto& x: v)
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())
#define endl '\n'
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ll> vl;

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 5010, MOD = 1e9+7;

string a, b;
int n, m;
int memo[MAX][MAX];

int dp(int i, int j){
    if(i == 0 or j == 0) return 0;

    int& p = memo[i][j];
    if(p != -1) return p;

    if(a[i] == b[j]) return p = dp(i-1, j-1)+1;
    return p = max(dp(i-1, j), dp(i, j-1));
}

void solve(){
    cin >> a >> b; n = a.size(), m = b.size(); a = " "+a, b = " "+b;

    memset(memo, -1, sizeof memo);
    cout << dp(n, m) << endl;
}

int main(){ _
    int ttt = 1;

    while(ttt--) solve();

    exit(0);
}
