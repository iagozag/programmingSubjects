#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int n, sum = 0;
vector<vector<int>> g;
vector<int> s;

void dfs(int v, int su){
	if(s[v] != -1 and su > s[v]) sum = -1;
	if(sum == -1) return;

	if(s[v] != -1){
		if(su > s[v]){ sum = -1; return; }
		sum += s[v]-su;
		su = s[v];
	} else{
		int mi = INF;
		for(auto ve: g[v]) mi = min(mi, s[ve]);
		if(mi != INF){
			if(mi < su){ sum = -1; return; }
			sum += mi-su;
			su = mi;
		}
	}

	for(auto ve: g[v]) dfs(ve, su);
}

void solve(){
	cin >> n;
	g = vector<vector<int>>(n); s = vector<int>(n);
	for(int i = 1; i < n; i++){ int p; cin >> p; --p; g[p].emplace_back(i); }
	for(auto& x: s){
		cin >> x;
	}

	dfs(0, 0);

	cout << sum << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
