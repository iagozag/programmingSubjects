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
	string a, b; cin >> a >> b;
	int n = a.size(), m = b.size();
	if(n != m){ cout << "No" << endl; return; }

	vector<int> va(n), vb(n);
	for(int i = 0; i < n; i++){
		int ta = 0, tb = 0;
		if(a[i] == 'a' or a[i] == 'e' or a[i] == 'i' or a[i] == 'o' or a[i] == 'u') ta = 1;
		else ta = 2;

		if(b[i] == 'a' or b[i] == 'e' or b[i] == 'i' or b[i] == 'o' or b[i] == 'u') tb = 1;
		else tb = 2;

		if(ta != tb) { cout << "No" << endl; return; }
	}

	cout << "Yes" << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
