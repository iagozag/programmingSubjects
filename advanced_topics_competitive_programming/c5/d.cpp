#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int n, m;
int v[500][500], memo[500][500][3];

int dp(int i, int j, int d){
	if(i == n-1 and j == m-1) return 0;
	if(i < 0 or j < 0 or i >= n or j >= m) return LINF;

	int& p = memo[i][j][d];
	if(p != -1) return p;

	p = v[i][j];

	int left = dp(i, j-1, 1), right = dp(i, j+1, 2), down = dp(i+1, j, 0);

	if(d == 0) return p = max(p, min({left, right, down}));
	else if(d == 1) p = max(p, min(left, down));
	else p = max(p, min(right, down));

	return p;
}

void solve(){
	cin >> n >> m;
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> v[i][j], memo[i][j][0] = memo[i][j][1] = memo[i][j][2] = -1;

	cout << dp(0, 0, 0) << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
