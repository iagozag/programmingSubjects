#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,x,n) for(auto i=x;i<n;i++)
#define repr(i,n,x) for(auto i=n;i>=x;i--)
#define forr(x, v) for(auto& x: v)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())
#define endl '\n'
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 2e5+10, MOD = 1e9+7;

int n, m, k;
vector<string> v;
map<pii, int> dist;
map<int, pii> mp;
vector<pii> moves = {{-2, 1}, {2, 1}, {-2, -1}, {2, -1}, {1, 2}, {-1, 2}, {1, -2}, {-1, -2}};

bool val(int i, int j){
    return i >= 0 and i < n and j >= 0 and j < m and v[i][j] != '#';
}

int bfs(int source, int destination){
    pii s = mp[source], d = mp[destination];
    queue<pii> q; q.push(s); 
    vector<vector<int>> dd(n, vi(m, INF)); dd[s.ff][s.ss] = 0;
    while(!q.empty()){
        pii ve = q.front(); q.pop();
        if(ve == d) return dd[ve.ff][ve.ss];
        for(auto [x, y]: moves){
            x += ve.ff, y += ve.ss;
            if(!val(x, y) or dd[ve.ff][ve.ss]+1 >= dd[x][y]) continue;
            dd[x][y] = dd[ve.ff][ve.ss]+1, q.push({x, y});
        }
    }
    
    return INF;
}

void solve(){
    k++;
    v = vector<string>(n); forr(x, v) cin >> x;

    int c = 1;
    rep(i, 0, n) rep(j, 0, m){
        if(v[i][j] == 'P') mp[c++] = {i, j};
        else if(v[i][j] == 'C') mp[0] = {i, j};
    }

    rep(i, 0, k) rep(j, 0, k){
        if(i == j) continue;

        dist[{i, j}] = bfs(i, j);
        dist[{j, i}] = dist[{i, j}];
    }

    int dp[1<<k][k]; memset(dp, INF, sizeof dp);
    dp[1][0] = 0;
    rep(i, 0, 1<<k){
        rep(j, 0, k) if(i&(1<<j)){
            rep(l, 0, k){
                if(j == l or !(i&(1<<l))) continue;
                dp[i][j] = min(dp[i][j], dp[i^(1<<j)][l]+dist[{j, l}]);
            }  
        } 
    }

    int mi = INF;
    rep(i, 0, k) mi = min(mi, dp[(1<<k)-1][i]+dist[{i, 0}]);
    cout << mi << endl;

    dist.clear(), mp.clear();
}

int main(){ _
    while(cin >> n >> m >> k and n != 0) solve();

    exit(0);
}
