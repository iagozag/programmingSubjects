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

#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#define dbgc(...) cerr << "["<< #__VA_ARGS__ << "]: [ "; DBGC(__VA_ARGS__) 

void no(){ cout << "N" << endl; }
void yes(){ cout << "S" << endl; }

const int MAX = 1e4+10;

int n, m, k;

struct sensor{
    int px, py, s, ml, md, mr, mu;
    sensor(ll a, ll b, ll c){
        px = a, py = b, s = c;
        mr = px+s, md = py+s, ml = px-s, mu = py-s;
    }
};

double dist(sensor a, sensor b){
    return sqrt(pow(a.px-b.px, 2)+pow(a.py-b.py, 2));
}

vi id, sz;
vector<sensor> v;

int find(int x){
    return id[x] = (id[x] == x ? x : find(id[x]));
}

void unio(int a, int b){
    a = find(a), b = find(b);
    if(a == b) return;
    if(sz[a] < sz[b]) swap(a, b);

    id[b] = a, sz[a] += sz[b];
    v[a].ml = min(v[a].ml, v[b].ml), v[a].md = max(v[a].md, v[b].md),
    v[a].mu = min(v[a].mu, v[b].mu), v[a].mr = max(v[a].mr, v[b].mr);
}

bool check(sensor a){
    return (a.ml <= 0 and (a.mu <= 0 or a.mr >= n)) or 
           (a.md >= n and (a.mu <= 0 or a.mr >= m));
}

void solve(){
    cin >> m >> n >> k;
    id = vi(k), sz = vi(k, 1); iota(all(id), 0);

    rep(i, 0, k){
        int x, y, s; cin >> x >> y >> s;
        v.eb(sensor(x, y, s));
    }

    rep(i, 0, k) rep(j, i+1, k)
        if(find(i) != find(j) and dist(v[i], v[j]) <= v[i].s+v[j].s)
            unio(i, j);

    unordered_set<int> ok;
    rep(i, 0, k){
        int par = find(i);
        if(!ok.count(par) and check(v[par])) return no(); 
        ok.insert(par); 
    }

    return yes();
}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}
