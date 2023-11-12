#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define all(a) (a).begin(), (a).end()
#define endl '\n'
#define f first
#define s second
#define pb push_back

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

#ifdef _DEBUG
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define dbgc(...) cerr << "["<< #__VA_ARGS__ << "]: [ "; DBGC(__VA_ARGS__) 
#else
#define dbg(...) 0
#define dbgc(...) 0
#endif

int MAX = 1E5+10;
vector<vector<vi>> seg(4*MAX);

vector<vi> multiply(const vector<vi>& mat1, const vector<vi>& mat2) 
{
    int x, i, j; 
    vector<vi> res(2, vi(2, 0)); 

    for (i = 0; i < 2; i++) { 
        for (j = 0; j < 2; j++) { 
            for (x = 0; x < 2; x++) { 
                res[i][j] += mat1[i][x] * mat2[x][j]; 
            } 
        } 
    }

    return res;
} 

vector<vi> build(int node, int tl, int tr){
    vector<vi> v = {{1, 0}, {0, 1}};
    if(tl == tr){
        seg[node][0][0] = 1, seg[node][1][1] = 1;
        return seg[node];
    }

    int tm = (tl+tr)>>1;
    return seg[node] = multiply(build(node*2, tl, tm), build(node*2+1, tm+1, tr));
}

vector<vi> update(int node, int tl, int tr, int idx, int val[2][2]){
    if(idx < tl || idx > tr) return seg[node];
    if(tl == tr){
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < 2; j++)
                seg[node][i][j] = val[i][j];
        return seg[node];
    }

    int tm = (tl+tr)>>1;
    return seg[node] = multiply(update(node*2, tl, tm, idx, val), update(node*2+1, tm+1, tr, idx, val));
}

vector<vi> query(int node, int tl, int tr, int l, int r){
    if(r < tl || l > tr) return {{1, 0}, {0, 1}};
    if(l <= tl && r >= tr) return seg[node];

    int tm = (tl+tr)>>1;
    return multiply(query(node*2, tl, tm, l, r), query(node*2+1, tm+1, tr, l, r));
}

void solve(){
    int n, m; cin >> n >> m;
    build(1, 0, n-1);

    for(int i = 0; i < m; i++){
        char op; int idx, a, b, c, d; cin >> op;
        if(op == 'u'){
            cin >> idx >> a >> b >> c >> d;
            int m[2][2] = {{a, b}, {c, d}};
            update(1, 0, n-1, idx, m);
        } else{
            cin >> a >> b >> c >> d;
            vector<vi> m = query(1, 0, n-1, a, b);
            m = multiply(m, {{c, d}, {0, 0}});
            cout << m[0][0] << " " << m[1][0] << endl;
        }
    }
}

int main(){ _
    int t = 1;
    while(t--){
        solve();
    }

    exit(0);
}

