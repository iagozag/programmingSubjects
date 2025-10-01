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
	int n, k, m; cin >> n >> k >> m;
	vector<int> v(n); for(auto& x: v) cin >> x;
	sort(v.begin(), v.end());

	vector<int> pref(n);
	for(int i = n-1; i >= 0; i--) pref[i] = (i < n-1 ? pref[i+1] : 0) + v[i];

	long double ans = 0;
	for(int i = 0; i < min(n, m+1); i++){
		ans = max(ans, (long double)(pref[i]+min(k*(n-i), m-i))/(long double)(n-i));
	}

	cout << fixed << setprecision(12) << ans << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
