#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int n, m;

int valid(int i, int j){
	return i >= 0 and i < n and j >= 0 and j < m;
}

void solve(){
	cin >> n >> m;
	int mat[n][m];
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cin >> mat[i][j];

	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
		int sum = 0;
		for(auto [x, y]: moves) sum += valid(x+i, y+j);

		if(mat[i][j] > sum){ cout << "NO" << endl; return; }
		else mat[i][j] = sum;
	}

	cout << "YES" << endl;
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) cout << mat[i][j] << " \n"[j==m-1];
}

int32_t main(){ _
    int ttt = 1; cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
