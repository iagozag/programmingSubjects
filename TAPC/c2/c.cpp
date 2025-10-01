#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int dp[MAX][3];

void solve(){
	int n, l, r; cin >> n >> l >> r;
	int qnt[3];
	memset(qnt, 0, sizeof qnt);

	if(r-l < 3){
		for(int i = l; i <= r; i++) qnt[i%3]++;
	}
	else{
		while(l%3 and l < r) qnt[l%3]++, l++;
		while(r%3 and l < r) qnt[r%3]++, r--;

		qnt[0]++;
		int tot = (r-l)/3;
		for(int i = 0; i < 3; i++) qnt[i] += tot;
	}

	memset(dp, 0, sizeof dp);
	dp[0][0] = 1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < 3; j++){
			dp[i+1][j] += dp[i][j]*qnt[0], dp[i+1][j] %= MOD;
			dp[i+1][(j+1)%3] += dp[i][j]*qnt[1], dp[i+1][(j+1)%3] %= MOD;
			dp[i+1][(j+2)%3] += dp[i][j]*qnt[2], dp[i+1][(j+2)%3] %= MOD;
		}
	}

	cout << dp[n][0] << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
