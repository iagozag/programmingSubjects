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
	vector<int> v(n); for(auto& x: v) cin >> x, x = abs(x);

	for(int i = 0; i < n/2; i++) if(i%2 == 0) v[i] *= -1;
	for(int i = n/2; i < n; i++) if(i%2 == 0) v[i] *= -1;

	for(auto x: v) cout << x << ' ';
	cout << endl;
}

int32_t main(){ _
    int ttt = 1; cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
