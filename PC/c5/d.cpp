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
	string s; cin >> s; int n = s.size();
	vector<pair<int, int>> pal;
	for(int i = 0; i < n; i++){
		// odd
		for(int j = 0; i-j >= 0 and i+j < n; j++){
			if(s[i-j] != s[i+j]) break;
			pal.emplace_back(i-j, i+j);
		}

		// even
		for(int j = 0; i-j >= 0 and i+j+1 < n; j++){
			if(s[i-j] != s[i+j+1]) break;
			pal.emplace_back(i-j, i+j+1);
		}
	}

	sort(pal.begin(), pal.end());

	int ans = 0;
	for(int i = 0; i < (int)pal.size(); i++){
		int ub = upper_bound(pal.begin(), pal.end(), make_pair(pal[i].second, INF))-pal.begin();
		ans += (int)pal.size()-ub;
	}

	cout << ans << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
