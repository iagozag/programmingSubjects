#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
	using ord_set = tree<T, null_type, greater<T>, rb_tree_tag,
	tree_order_statistics_node_update>;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 3e5+10, MOD = 1e9+7;

int n, k, ans = 0, sum = 0, in = 0;
vector<vector<int>> g(MAX);
vector<int> a(MAX);
ord_set<pair<int, int>> st;

void dfs(int v){
	if(st.order_of_key({a[v], v}) < k)
		sum += a[v]-((int)st.size() >= k ? (*st.find_by_order(k-1)).first : 0);

	st.insert({a[v], v});

	for(auto ve: g[v]) dfs(ve);

	if(g[v].size() == 0) ans = max(ans, sum);

	if(st.order_of_key({a[v], v}) < k)
		sum -= a[v]-((int)st.size() > k ? (*st.find_by_order(k)).first : 0);

	st.erase({a[v], v});
}

void solve(){
	cin >> n >> k;
	int root = 0;
	for(int i = 0; i < n; i++){
		int u; cin >> u >> a[i]; --u;
		if(u != -1) g[u].emplace_back(i);
		else root = i;
	}

	dfs(root);

	cout << ans << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
