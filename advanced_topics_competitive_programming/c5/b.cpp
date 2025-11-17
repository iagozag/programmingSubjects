#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int long long

const long long LINF = 0x3f3f3f3f3f3f3f3f;

int N, C;
vector<int> w, c;
vector<vector<int>> g;
long long dp[1000][1<<10][2];

void dfs(int v, int p){
    dp[v][1<<c[v]][1] = w[v];

    for (auto ve : g[v]) if(ve != p){
        dfs(ve, v);

        int newdp[1<<10][2]; memset(newdp, 0, sizeof newdp);
        for (int i = 0; i < (1<<C); i++) {
            int comp = ((1<<C)-1)^i;
            for (int j = comp; ; j = (j-1)&comp) {
                newdp[i|j][1] = max(newdp[i|j][1], dp[v][i][1] + dp[ve][j][0]);
				newdp[i|j][0] = max(newdp[i|j][0], dp[v][i][0] + max(dp[ve][j][0], dp[ve][j][1]));

                if (j == 0) break;
            }
        }

        for (int m = 0; m < (1<<C); m++) {
            dp[v][m][0] = max(dp[v][m][0], newdp[m][0]);
            dp[v][m][1] = max(dp[v][m][1], newdp[m][1]);
        }
    }
}

void solve(){
    cin >> N >> C;
    w = c = vector<int>(N);
    g = vector<vector<int>>(N);

    for(int i = 0; i < N; i++) cin >> w[i];
    for(int i = 0; i < N; i++) cin >> c[i], --c[i];

    for(int i = 0; i < N-1; i++){ int a, b; cin >> a >> b; --a; --b; g[a].emplace_back(b); g[b].emplace_back(a); }

	memset(dp, 0, sizeof dp);

    dfs(0, 0);

    int ans = 0;
    for(int i = 0; i < (1<<C); i++) ans = max({ans, dp[0][i][0], dp[0][i][1]});

    cout << ans << endl;
}

int32_t main(){ _
    solve();
}

