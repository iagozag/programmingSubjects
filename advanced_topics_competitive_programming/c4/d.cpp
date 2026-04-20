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

	vector<int> ans;
	bool verify = 0;
	while(wrong(v)){
		int mex = get_mex(v);

		if(mex == 0){ ans.emplace_back(0), v[0] = 0; continue; }

		if(mex == n){ ans.emplace_back(n-1), v[n-1] = mex, verify = true; continue; }

		if(verify){
			bool ok = true;
			for(int i = mex; i < n; i++) if(v[i] != i+1) ok = false;
			if(ok){ ans.emplace_back(mex-1), v[mex-1] = mex; continue; }
		}

		ans.emplace_back(mex), v[mex] = mex;
	}

	cout << ans.size() << endl;
	for(auto x: ans) cout << x+1 << ' ';
	cout << endl;

//  	cout << "v: ";
//  	for(auto x: v) cout << x << ' ';
//  	cout << endl;
}

int32_t main(){ _
    int ttt = 1; cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
