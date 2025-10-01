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

	int ma = 0; char c;
	vector<int> v(26); for(auto cc: s) v[cc-'a']++;

	for(int i = 0; i < 26; i++){
		if(ma < v[i]) ma = v[i], c = (char)(i+'a');
	}

	vector<int> p; 
	for(int i = 2; i <= n; i++){
		int can = 1;
		for(int j = 2; j*j <= i; j++) if(i%j == 0) can = 0;
		if(can) p.emplace_back(i);
	}

	int qnt = 0;
	for(auto pp: p) if(pp*2 > n) qnt++;

	if(qnt+1 < n-ma){ cout << "NO" << endl; return; }

	string ans = string(n, c);
	v[c-'a'] = 0;

	for(auto pp: p) if(pp*2 > n){
		for(int i = 0; i < 26; i++) if(v[i]){
			ans[pp-1] = (char)(i+'a'), v[i]--;
			break;
		}
	}

	for(int i = 0; i < 26; i++) if(v[i]) ans[0] = (char)(i+'a');

	cout << "YES" << endl;
	cout << ans << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
