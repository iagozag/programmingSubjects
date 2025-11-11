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

const int MAX = 2e5+10;

pair<int,string> check(string s, string op, int n){
    string a1 = "", a2 = "", a3 = "";
    int k = 0;
    rep(i, 0, n) a1 += op[k], k = (k+1)%3;
    k = 1;
    rep(i, 0, n) a2 += op[k], k = (k+1)%3;
    k = 2;
    rep(i, 0, n) a3 += op[k], k = (k+1)%3;
    int ca1 = 0, ca2 = 0, ca3 = 0;
    rep(i, 0, n) ca1 += (a1[i] != s[i]), ca2 += (a2[i] != s[i]), ca3 += (a3[i] != s[i]);
    int mi = min({ca1, ca2, ca3});
    if(ca1 == mi) return {ca1, a1};
    else if(ca2 == mi) return {ca2, a2};
    else return {ca3, a3};
}

void solve(){
    int n; cin >> n;
    string s; cin >> s;

    pair<int,string> mi = {INF, ""};
    pair<int,string> pos = check(s, "RGB", n);
    if(mi.ff > pos.ff) mi = pos;
    pos = check(s, "RBG", n);
    if(mi.ff > pos.ff) mi = pos;
    pos = check(s, "BRG", n);
    if(mi.ff > pos.ff) mi = pos;
    pos = check(s, "BGR", n);
    if(mi.ff > pos.ff) mi = pos;
    pos = check(s, "GRB", n);
    if(mi.ff > pos.ff) mi = pos;
    pos = check(s, "GBR", n);
    if(mi.ff > pos.ff) mi = pos;

    cout << mi.ff << endl << mi.ss << endl;
}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}
