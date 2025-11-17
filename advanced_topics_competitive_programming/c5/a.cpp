#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int n, b;
vector<vector<pair<int, int>>> v(20);

int f(int i, int j){
	if(i == n) return 0;
	if(j == (int)v[i].size()) return f(i+1, 0);

	int ma = 0;
	for(int l = 0; l < (int)v[i].size(); l++) if(v[i][j].second <= b){
		b -= v[i][j].second;
		ma = max(ma, v[i][j].first+f(i+1, 0));
		b += v[i][j].second;
	}

	return max(ma, f(i, j+1));
}

void solve(){
	cin >> n >> b;
	for(int i = 0; i < n; i++){
		int k; cin >> k;
		for(int j = 0; j < k; j++){ int r, w; cin >> r >> w; v[i].emplace_back(r, w); }
	}

	cout << f(0, 0) << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
