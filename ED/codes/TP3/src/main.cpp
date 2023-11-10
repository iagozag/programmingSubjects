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

vector<vi> seg;

vector<vi> build(int node, int tl, int tr){
}

vector<vi> update(int node, int tl, int tr, int idx, int val[2][2]){

}

vector<vi> query(int node, int tl, int tr, int l, int r){
}

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<vi>> seg(n, vector<vi>(2, vi(2, 0))); 
    build(1, 0, n-1);

    for(int i = 0; i < m; i++){
        char op; int idx, a, b, c, d;
        if(op == 'u'){
            cin >> idx >> a >> b >> c >> d;
            int m[2][2] = {{a, b}, {c, d}};
            update(1, 0, n-1, idx, m);
        } else{
            cin >> a >> b >> c >> d;
            
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

