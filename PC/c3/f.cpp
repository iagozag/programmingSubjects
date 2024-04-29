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

const int MAX = 2e5+10, MOD = 1e9+7;

void solve(){
    int n; cin >> n;
    vi v(n); vector<double> medians(n/2+1, INF); forr(x, v) cin >> x;
    sort(all(v));
    int l = 0, r = n-1;
    while(l <= r) medians[l] = (v[l]+v[r])/2, l++, r--;
    
    vector<double> pref(medians.size()); pref[0] = medians[0];
    rep(i, 1, medians.size()) pref[i] = pref[i-1]+medians[i];

    int idx, m_ans; double ma = -1;
    rep(i, 0, n){
        double med = v[i];
        auto it = upper_bound(all(medians), med)-medians.begin();
        if(it != 0 and ma < pref[it-1]) ma = pref[it-1], idx = it, m_ans = i; 
    }
    
    vi ans; bool ok = false;
    rep(i, 0, idx){ if(i == m_ans) ok = true; ans.eb(v[i]); ans.eb(v[n-i-1]); }
    if(!ok) ans.eb(v[m_ans]);
    sort(all(ans));

    cout << ans.size() << endl;
    rep(i, 0, ans.size()) cout << ans[i] << " \n"[i == ans.size()-1];
}

int main(){ _
    int ttt = 1;

    while(ttt--) solve();

    exit(0);
}
