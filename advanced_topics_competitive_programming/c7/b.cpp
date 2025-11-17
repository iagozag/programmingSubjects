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
map<char, int> mp;
mp['A'] = 0;
mp['C'] = 1;
mp['G'] = 2;
mp['T'] = 3;

vector<vector<int>> pos;

int calc_diff(vector<vector<int>>& m1, vector<vector<int>>& m2){
	int sum = 0;
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) sum += (m1[i][j] != m2[i][j]);
	return sum;
}

void solve(){
	cin >> n >> m;
	vector<vector<int>> mat(n, vector<int> m);
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
		char c; cin >> c;
		mat[i][j] = mp[c];
	}
	
	int dp[n][m][4];
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) for(int k = 0; k < 4; k++){
		vector<int> pos;
		for(int l = 0; l < 4; l++) if(l != k) pos.emplace_back(l);

		do{
			dp[i][j][k] = 
		} while(next_permutation(pos.begin(), pos.end()));
	}


	
	cout << ans << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
