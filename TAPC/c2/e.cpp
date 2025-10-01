#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int N, M;
int g[41][41];

int f(){
	int n = M;
	vector<int> dp(1<<(n/2));
	for(int i = 0; i < (1<<(n/2)); i++){
		int mask = (1<<(n/2))-1;
		for(int j = 0; j < n/2; j++) if((i>>j)&1)
			for(int k = 0; k < n/2; k++) if(g[j][k] and ((mask>>k)&1)) mask -= 1<<k;

		for(int j = 0; j < n/2; j++) if(!((i>>j)&1)){
			dp[i|(1<<j)] = max(dp[i|(1<<j)], dp[i]+((mask>>j)&1));
		}
	}

	int ans = 0;
	for(int i = 0; i < (1<<((n+1)/2)); i++){
		int ok = 1;
		for(int j = n/2; j < n; j++) if((i>>(j-n/2))&1){
			for(int k = j+1; k < n; k++) if(((i>>(k-n/2))&1) and g[j][k]) ok = 0;
		}

		if(!ok) continue;

		int mask = (1<<(n/2))-1;
		for(int j = n/2; j < n; j++) if((i>>(j-n/2))&1){
			for(int k = 0; k < n/2; k++) if(g[j][k] and ((mask>>k)&1)) mask -= 1<<k;
		}

		if(ans < (__builtin_popcount(i)+dp[mask])){
			ans = __builtin_popcount(i)+dp[mask];
		}
	}

	return ans;
}

void solve(){
	cin >> N >> M;
	vector<pair<int, string>> q2(N);
	vector<pair<int, int>> q(N);

	set<string> st;
	for(auto& [a, b]: q2){
		cin >> a;
		if(a == 2) cin >> b, st.insert(b);
	}
	map<string, int> mp;
	int id = 0;
	for(auto s: st) mp[s] = id++;

	for(int i = 0; i < N; i++){
		q[i].first = q2[i].first;
		if(q2[i].first == 2) q[i].second = mp[q2[i].second];
	}

	vector<int> v(41);
	for(int i = N-1; i >= 0; i--){
		if(q[i].first == 1){
			for(int j = 0; j < M; j++) for(int k = j+1; k < M; k++) if(v[j] and v[k]) g[j][k] = g[k][j] = 1;
			v = vector<int>(41);
		}
		else v[q[i].second] = 1;
	}

	cout << f() << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
