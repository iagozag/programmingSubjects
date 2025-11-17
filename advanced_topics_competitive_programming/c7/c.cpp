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

	if(k > (n+1)*n/2){ cout << "No" << endl; return; }
	
	cout << "Yes" << endl;

	map<int, int> mp; mp[2] = 0;
	k--;

	vector<int> p(n);
	for(int i = 1; i < n; i++){
		int rest = n-i-1;

		auto [a, b] = *mp.rbegin();

		int l = 2, r = a, ans;
		while(l <= r){
			int m = l+(r-l)/2;

			if(rest*2+m > k) r = m-1;
			else ans = m, l = m+1;
		}

		mp[ans+1] = i;
		p[i] = mp[ans];
		k -= ans;
	}

	for(int i = 1; i < n; i++) cout << p[i]+1 << ' ';
	cout << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
