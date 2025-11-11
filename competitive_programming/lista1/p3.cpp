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

void solve(){
    int n, m; cin >> n >> m;
    vector<vi> g(n); vi vis(n);
    rep(i, 0, m){
        char a, b; cin >> a >> b; int va = a-'a', vb = b-'a';
        g[va].eb(vb), g[vb].eb(va);
    }

    function<void(int v, set<char>& ans)> dfs = [&](int v, set<char>& ans){
        vis[v] = 1; ans.insert(char(v+'a'));
        forr(ve, g[v]){
            if(!vis[ve]) dfs(ve, ans);
        }
    };

    int cnt = 0;
    rep(i, 0, n){
        if(!vis[i]){
            set<char> ans;
            dfs(i, ans), cnt++;
            forr(x, ans) cout << x << ",";
            cout << endl;
        }
    }

    cout << cnt << " connected components\n";
}

int main(){ _
    int t; cin >> t;

    rep(i, 1, t+1){ cout << "Case #" << i << ":\n"; solve(); if(i < t) cout << endl;}

    exit(0);
}
