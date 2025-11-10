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
	vector<int> v(n); for(auto& x: v) cin >> x;
	pair<int, int> ans = {0, INF};

	for(int i = 1; i < 101; i++){
		int cost = 0;
		for(int j = 0; j < n; j++){
			if(v[j] == i) continue;
			cost += abs(v[j]-i)-1;
		}
		if(cost < ans.second) ans = {i, cost};
	}

	cout << ans.first << ' ' << ans.second << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
