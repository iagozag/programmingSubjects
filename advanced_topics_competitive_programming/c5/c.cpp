#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

void solve(){
	int n; cin >> n;
	vector<int> v(n); for(int i = 0; i < n; i++) cin >> v[i];

	int dp[n][n]; memset(dp, 0, sizeof dp);

	for(int i = 0; i < n; i++) dp[i][i] = v[i]*n;

	for(int i = 1; i < n; i++){
		for(int j = 0; j+i < n; j++){
			int cnt = n-i;

			dp[j][j+i] = max(v[j]*cnt+dp[j+1][j+i], v[j+i]*cnt+dp[j][j+i-1]);
		}
	}

	cout << dp[0][n-1] << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
