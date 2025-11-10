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
	int n, k, A, B; cin >> n >> k >> A >> B;
	map<int, int> mp; for(int i = 0; i < k; i++){ int x; cin >> x; mp[x]++; }

	vector<pair<int, int>> v;
	for(auto [x, y]: mp) v.emplace_back(x, y);
	int m = v.size();

	vector<int> pref(m); for(int i = 0; i < m; i++) pref[i] = (i ? pref[i-1] : 0) + v[i].second;

	auto get = [&](int l, int r) -> int{
		return pref[r] - (l ? pref[l-1] : 0);
	};

	auto f = [&](auto&& self, int l, int r) -> int{
		int lb = lower_bound(v.begin(), v.end(), make_pair(l, 0LL))-v.begin();
		int ub = upper_bound(v.begin(), v.end(), make_pair(r, INF))-v.begin(); ub--;
		if(lb > ub) return A;
		if(l == r) return B*get(lb, ub);

		int burn = get(lb, ub)*B*(r-l+1);
		int divide = self(self, l, (l+r)/2)+self(self, (l+r)/2+1, r);

		return min(burn, divide);
	};

	cout << f(f, 1, 1LL<<n) << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
