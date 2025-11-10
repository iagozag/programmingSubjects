#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

struct pt{
	int x, y;	
};

void solve(){
	int a, b;
	pt p1, p2; cin >> a >> b >> p1.x >> p1.y >> p2.x >> p2.y;

	int d1p1 = p1.x+p1.y, d1p2 = p2.x+p2.y;
	if(d1p1 > d1p2) swap(d1p1, d1p2);
	int MOVE1 = 2e9*a;
	d1p1 += MOVE1, d1p2 += MOVE1;
	d1p1 += 2*a-(d1p1%(2*a));
	d1p2 -= d1p2%(2*a);
	int ans1 = (d1p1 <= d1p2 ? (d1p2-d1p1)/(2*a)+1 : 0);

	int d2p1 = p1.x-p1.y, d2p2 = p2.x-p2.y;
	if(d2p1 > d2p2) swap(d2p1, d2p2);
	int MOVE2 = 2e9*b;
	d2p1 += MOVE2, d2p2 += MOVE2;
	d2p1 += 2*b-(d2p1%(2*b));
	d2p2 -= d2p2%(2*b);
	int ans2 = (d2p1 <= d2p2 ? (d2p2-d2p1)/(2*b)+1 : 0);

	cout << max(ans1, ans2) << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
