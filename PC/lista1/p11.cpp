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

const int INF = 10000;
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

const int MAX = 110, MOD = 1e9+7;

int t, p;
vi timep, fails;
vector<vi> same_cnt;

bool check(int m){
    forr(v, same_cnt){
        if(v.size() <= 1) continue;
        rep(i, 0, v.size()-1){
            int a = v[i], b = v[i+1];
            if(fails[a] == fails[b]) continue;
            if(fails[a] != fails[b] and timep[a] == timep[b] and m != 20) return false;

            if(timep[a]-fails[a]*20+fails[a]*m >= timep[b]-fails[b]*20+fails[b]*m) return false;
        }
    }

    return true;
}

void solve(){
    same_cnt = vector<vi>(p+1), timep = fails = vi(t);
    rep(i, 0, t){
        int cnt = 0;
        rep(j, 0, p){
            string st; cin >> st; replace(all(st), '/', ' '); if(st[st.size()-1] == '-') st = st+'1';

            int fa; int tr; 
            istringstream ss(st);
            ss >> fa >> tr;
            if(tr != -1) cnt++, fails[i] += fa-1, timep[i] += tr;
        }
        same_cnt[cnt].eb(i), timep[i] += fails[i]*20;
    } 

    forr(x, same_cnt) 
        sort(all(x), [&](const int& a, const int& b){
            return timep[a] < timep[b];
        });

    int ansl = 20;
    while(ansl > 1 and check(ansl-1)) ansl--;

    int l = 20, r = INF, ansr = 20;
    while(l <= r){
        int m = l+(r-l)/2;
        if(check(m)) ansr = m, l = m+1;
        else r = m-1;
    }
    
    cout << ansl << " "; if(ansr == INF) cout << '*'; else cout << ansr;
    cout << endl;
}

int main(){ _
    while(cin >> t >> p){ if(t == 0 or p == 0) break; solve(); }

    exit(0);
}
