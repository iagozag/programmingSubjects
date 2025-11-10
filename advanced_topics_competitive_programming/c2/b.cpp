#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int n, k;
vector<int> v;

void solve(){
	cin >> n >> k;
	v = vector<int>(n); for(auto& x: v){ char c; cin >> c; x = c-'a'; }

	int ans = 0;
	for(int i = 0; i < 26; i++){
		int cnt = 0, cur = 0;
		for(int j = 0; j < n; j++){
			if(v[j] == i) cur++;
			else cur = 0;

			if(cur == k) cnt++, cur = 0;
		}
		ans = max(ans, cnt);
	}
	cout << ans << endl;

}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
