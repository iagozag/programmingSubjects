#include <bits/stdc++.h>
#include <sys/types.h>
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

void solve(){
    int n; cin >> n; string s; cin >> s;
    int cnt = 0;
    rep(i, 1, n){
        if(s[i] == s[i-1] and i < n-1){
            cnt++;
            if(s[i-1] == s[i+1]){
                if(s[i] == 'B') s[i] = 'R';
                else s[i] = 'B';
            }
            else s[i] = 'R' ^ 'G' ^ 'B' ^ s[i-1] ^ s[i+1];
        }
        else if(s[i] == s[i-1]){
            cnt++;
            if(s[i] == 'B') s[i] = 'R';
            else s[i] = 'B';
        }
    }

    cout << cnt << endl << s << endl;
}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}