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
	int n, k; cin >> n >> k;
	vector<string> v(n); for(auto& x: v) cin >> x;
	vector<int> perm; for(int i = 0; i < k; i++) perm.emplace_back(i);
	
	int ans = LINF;
	do{
		vector<int> num;
		for(int i = 0; i < n; i++){
			string s = "";
			for(int j = 0; j < k; j++) s += v[i][perm[j]];
			num.emplace_back(stoi(s));
		}
		sort(num.begin(), num.end());
		ans = min(ans, num.back()-num[0]);
	} while(next_permutation(perm.begin(),perm.end()));

	cout << ans << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
