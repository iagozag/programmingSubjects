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

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 2e5+10, MOD = 1e9+7;

void solve(int n, int b){
    vi slots(n), balls(b); forr(x, slots) cin >> x; forr(x, balls) cin >> x;

    int dp[n][b]; 

    int ans = INF;
    rep(c, 0, n){
        memset(dp, INF, sizeof dp);
        rep(i, 0, n) dp[i][0] = (slots[i]+slots[(i+1)%n])*balls[0];
        
        rep(j, 1, b){
            int pref[n+1]; memset(pref, INF, sizeof pref);
            rep(i, 1, n+1) pref[i] = min(pref[i-1], dp[i-1][j-1]);
            rep(i, 2, n-1)
                dp[i][j] = min(dp[i][j], pref[i-1]+(slots[i]+slots[(i+1)%n])*balls[j]);
        } 

        int mi = INF;
        rep(i, 0, n) mi = min(mi, dp[i][b-1]);
        ans = min(ans, mi);

        rotate(slots.rbegin(),slots.rbegin()+1, slots.rend());
    }

    cout << -ans << endl;
}

int main(){ _
    int n, k;
    while(cin >> n >> k){ if(n == 0 and k == 0) break; solve(n, k); }

    exit(0);
}

