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
	vector<int> v(n); 
	for(auto& x: v) cin >> x;

	int ans = 0, ma = v[0];
	for(int i = 1; i < n; i++){
		if(v[i] < ma){
			int tmp = v[i], sum = 1, j = 0;
			while(tmp < ma) tmp += sum, j++, sum *= 2;
			ans = max(ans, j);
		}

		ma = max(ma, v[i]);
	}

	cout << ans << endl;
}

int32_t main(){ _
    int ttt = 1; cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
