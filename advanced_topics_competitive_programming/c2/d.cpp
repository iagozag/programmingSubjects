#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

int n, m, P;
int s[11];
int mat[1001][1001], vis[1001][1001], dist[1001][1001];
queue<pair<int, int>> queues[11][2];

vector<pair<int, int>> moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool val(int i, int j){
	return i >= 0 and i < n and j >= 0 and j < m and mat[i][j] == 0;
}

void bfs(int p){
	while(!queues[p][0].empty()) queues[p][0].pop();
	while(!queues[p][1].empty()){
		auto [a, b] = queues[p][1].front(); queues[p][1].pop();
		dist[a][b] = s[p], queues[p][0].push({a, b});
	}

	queue<pair<int, int>>& q = queues[p][0];
	while(!q.empty()){
		auto [a, b] = q.front(); q.pop();

		if(dist[a][b] == 0){ queues[p][1].push({a, b}); continue; }

		if(vis[a][b] == 1) continue;
		vis[a][b] = 1;

		for(auto [x, y]: moves){
			x += a, y += b;
			if(!val(x, y)) continue;
			mat[x][y] = mat[a][b], dist[x][y] = dist[a][b]-1, queues[p][0].push({x, y});
		}
	}
}

void solve(){
	cin >> n >> m >> P;

	memset(s, 0, sizeof s);
	for(int i = 1; i <= P; i++) cin >> s[i];

	memset(mat, 0, sizeof mat);
	for(int i = 0; i < n; i++){
		string st; cin >> st;
		for(int j = 0; j < m; j++){
			char c = st[j];
			if(c == '.') mat[i][j] = 0;
			else if(c == '#') mat[i][j] = -1;
			else mat[i][j] = c-'0', queues[mat[i][j]][1].push({i, j});
		}
	}

	memset(vis, 0, sizeof vis);
	fill(*dist, *dist+n*m, INF);
	for(int rnd = 0; rnd < 1e6; rnd++)
		for(int i = 1; i <= P; i++)
			bfs(i);

	int qnt[11]; memset(qnt, 0, sizeof qnt);
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) if(mat[i][j] >= 1 and mat[i][j] <= P) qnt[mat[i][j]]++;
	for(int i = 1; i <= P; i++) cout << qnt[i] << ' ';
	cout << endl;
}

int32_t main(){ _
    int ttt = 1; // cin >> ttt;

    while(ttt--) solve();

    exit(0);
}
