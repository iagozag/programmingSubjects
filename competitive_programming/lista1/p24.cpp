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
void yes(int ans){ cout << ans << endl; }

const int MAX = 2e5+10;

typedef unordered_map<char,int> um;

void solve(){
    int n, k; cin >> n >> k; --k;
    string cards = "A23456789DQJKZ";
    um score; rep(i, 0, cards.size()) score[cards[i]] = i;

    vector<um> p(n); p[k]['W'] = 1; int ans = -1; char c = 'Z';
    rep(i, 0, n){
        string a; cin >> a;
        forr(x, a) p[i][x]++;
        if(p[i].size() == 1 and score[c] > score[a[0]]) ans = i+1, c = a[0];
    }
    if(ans != -1) return yes(ans);

    vector<bool> can_pass(n);
    while(true){
        um& mp = p[k]; int prox = (k+1)%n;

        char low = 'Z'; int qnt = 5, ma = 0;
        forr(x, mp){
            if(x.ff == 'W') continue;
            if(x.ss < qnt or (x.ss == qnt and score[low] > score[x.ff])) low = x.ff, qnt = x.ss;
            ma = max(ma, x.ss);
        }

        if(ma == 4){
            if(mp.count('W') and !can_pass[k]){
                low = mp.begin()->ff;
                mp[low]--, p[prox][low]++, can_pass[k] = 1;
                k = prox; continue;
            };
            return yes(k+1);
        }

        bool passed = false;
        if(mp.count('W')){ 
            if(can_pass[k]) mp.erase('W'), p[prox]['W'] = 1, can_pass[k] = 0, passed = 1;
            else can_pass[k] = 1;
        }
        
        if(!passed){
            mp[low]--, p[prox][low]++; if(mp[low] == 0) mp.erase(low);
        }

        k = prox;
    }
}

int main(){ _
    int t = 1;

    while(t--) solve();

    exit(0);
}
