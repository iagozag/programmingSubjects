#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 1010, MOD = 1e9+7;

vector<int> qnt(MAX);

int get_mex(vector<int> &v){
	int n = v.size();
	for(int i = 0; i < n; i++) qnt[v[i]]++;
	for(int i = 0; i < MAX; i++) if(!qnt[i]){
		for(int j = 0; j < n; j++) qnt[v[j]]--;
		return i;
	}

	return n;
}

bool wrong(vector<int> &v){
	int n = v.size();
	for(int i = 1; i < n; i++) if(v[i] < v[i-1]) return true;
	return false;
}

void solve(){
	int n; cin >> n;
	vector<int> v(n); for(int i = 0; i < n; i++) cin >> v[i];

	vector<int> ans, qntt(n);
	for(int i = 0; i < n; i++){
		if(v[i] >= n or qntt[v[i]]){
			int mex = get_mex(v);
			ans.emplace_back(i);
			v[i] = mex;
		}
		qntt[v[i]]++;
	}

	for(int i = 0; i < n; i++) if(v[i] == 0) ans.emplace_back(i), v[i] = n;

	int cur = 0, sub = 0;
	while(wrong(v)){
		ans.emplace_back(cur-sub);
		swap(v[cur-sub], cur);
		if(cur == n) sub++;
	}

	cout << ans.size() << endl;
	for(auto x: ans) cout << x+1 << ' ';
	cout << endl;

// 	cout << "v: ";
// 	for(auto x: v) cout << x << ' ';
// 	cout << endl;
}

int32_t main(){ _
    int ttt = 1; cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
