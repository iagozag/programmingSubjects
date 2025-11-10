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
	set<pair<int, int>> st;
	vector<int> pos(n);
	for(int i = 0; i < n; i++){
		int x; cin >> x; --x; st.insert({i, x}); pos[x] = i;
	}

	for(int i = n-1; i >= 0; i--){
		if((*st.rbegin()).second == i){ cout << "YES" << endl; return; }
		if((*st.begin()).second == i){ cout << "NO" << endl; return; }

		st.erase({pos[i], i});
	}
}

int32_t main(){ _
    int ttt = 1; cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
