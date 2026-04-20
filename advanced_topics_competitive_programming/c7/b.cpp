#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define int ll

typedef long long ll;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

const int MAX = 2e5+10, MOD = 1e9+7;

vector<char> letters = {'A', 'C', 'G', 'T'};
set<pair<int, int>> st;

pair<vector<vector<char>>, int> solve(vector<vector<char>>& mat){
	int n = mat.size(), m = mat[0].size(), mi = LINF;
	vector<vector<char>> ans = mat;
	do{
		if(st.count({letters[1], letters[0]})) continue;
		st.insert({letters[0], letters[1]});

		int diff = 0;
		vector<vector<char>> tmp(n);
		for(int l = 0; l < n; l++){
			int sum1 = 0, sum2 = 0;
			vector<char> t1, t2;

			int i = (l&1 ? letters[0] : letters[2]), j = (l&1 ? letters[1] : letters[3]);
			for(int k = 0; k < m; k++){
				t1.emplace_back(k&1 ? i : j), sum1 += (t1[k] != mat[l][k]);
				t2.emplace_back(k&1 ? j : i), sum2 += (t2[k] != mat[l][k]);
			}

			if(sum1 < sum2) tmp[l] = t1, diff += sum1;
			else tmp[l] = t2, diff += sum2;
		}
		
		if(diff < mi) mi = diff, ans = tmp;
	} while(next_permutation(letters.begin(), letters.end()));

	return {ans, mi};
}

int32_t main(){ _
	int n, m; cin >> n >> m;
	vector<vector<char>> mat(n, vector<char>(m)), mat2(m, vector<char>(n));
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++){
		char c; cin >> c;
		mat[i][j] = mat2[j][i] = c;
	}

	auto [ans, d1] = solve(mat);
	auto [ans2, d2] = solve(mat2);

	vector<vector<char>> tmp(n, vector<char>(m));
	for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) tmp[i][j] = ans2[j][i];
	swap(ans2, tmp);

	if(d1 > d2) swap(ans, ans2), swap(d1, d2);

	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++) cout << ans[i][j];
		cout << endl;
	}

	// cout << d1 << endl;

    exit(0);
}
