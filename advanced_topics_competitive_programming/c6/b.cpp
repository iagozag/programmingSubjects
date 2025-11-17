#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int mi = 1, ma = 0;
vector<vector<int>> g;
vector<int> parity;

void dfs(int v, int p){
	if(g[v].size() == 1 and v){ parity[v] = 0; return; }

	int se = 0, so = 0;
	for(auto ve: g[v]) if(ve != p){ 
		dfs(ve, v);
		se += (parity[ve] == 0), so += (parity[ve] == 1);
	}

	if(se and so) mi = 3;
	else if(se) parity[v] = 1;
	else parity[v] = 0;
}

int dist[MAX];
void dfs2(int v, int p){

}

void solve(){
	int n; cin >> n;
	g.resize(n), parity.resize(n);
	for(int i = 0; i < n-1; i++){
		int a, b; cin >> a >> b; --a, --b;
		g[a].emplace_back(b), g[b].emplace_back(a);
	}

	dfs(0, 0);

	

	cout << mi << ' ' << ma << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
