#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,x,n) for(auto i=x;i<n;i++)
#define repr(i,n,x) for(auto i=n;i>=x;i--)
#define forr(x, v) for(auto& x: v)
#define all(a) (a).begin(), (a).end()
#define endl '\n'
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ll> vl;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void DBG() {
    cerr << "]" << endl;
}

void DBGC() {
    cerr << "]" << endl;
}

template<class H, class... T> void DBG(H h, T... t) {
    cerr << to_string(h);
    if(sizeof...(t)) cerr << ", ";
    DBG(t...);
}

template<class H, class... T> void DBGC(H h, T... t) {
    for(auto& x: h) cerr << x << " ";
    if(sizeof...(t)) cerr << "], [ ";
    DBGC(t...);
}

#ifndef _DEBUG
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define dbgc(...) cerr << "["<< #__VA_ARGS__ << "]: [ "; DBGC(__VA_ARGS__) 
#else
#define dbg(...) 0
#define dbgc(...) 0
#endif

const int MAX = 2e5+10;

int a, b;

bool ok(vi v, vi g){
    int i = 0, j = a-1;
    while(i < b and v[i] == g[i]) i++;
    while(i < b and v[i]+v[j] == g[i]) i++, j--;
    if(i <= j) return 0;

    return 1;
}

void solve(){
    while(cin >> a){
        vi v(a); forr(x, v) cin >> x;
        cin >> b;
        vi g(b); forr(x, g) cin >> x;

        if(b == 1){
            int sum = 0; forr(x, v) sum += x;
            cout << (sum == g[0] ? "S" : "N") << endl;
            continue;
        }
        else if(a == b){
            bool equal = true;
            rep(i, 0, a) if(v[i] != g[i]) equal = false;
            if(!equal){ equal = true; rep(i, 0, a) if(v[i] != g[a-i-1]) equal = false; }
            cout << (equal ? 'S' : 'N') << endl;
            continue;
        }

        bool b1 = ok(v, g);
        reverse(all(v));
        bool b2 = ok(v, g);

        cout << (b1 or b2 ? "S" : "N") << endl;
    }
}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}
