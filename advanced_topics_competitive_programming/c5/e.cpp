#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int nim[101];

void solve(){
	int a, b, c; cin >> a >> b >> c;
	int k; cin >> k;
	vector<int> v;
	for(int i = 0; i < k; i++){ int x; cin >> x; v.emplace_back(x); }

	for(int i = 0; i <= max({a, b, c}); i++){
		vector<int> mex(102);
		for(auto x: v) if(i-x >= 0) mex[nim[i-x]] = 1;
		for(int j = 0; j <= 101; j++) if(!mex[j]){ nim[i] = j; break; }
	}

	cout << ((nim[a]^nim[b]^nim[c]) ? "Peter" : "Vasya") << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
