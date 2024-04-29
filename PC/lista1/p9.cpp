
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

int k;

bool check(vector<vi>& v){
    vi ptotals(6);
    rep(i, 0, 4){
        int sum_p = 0;
        rep(j, 0, 6) sum_p += v[i][j], ptotals[j] += v[i][j];
        if(sum_p != v[i][k]) return false;
        ptotals[k] += sum_p;
    }
    rep(i, 0, k+1) if(ptotals[i] != v[4][i]) return false;

    return true;
}

vector<vi> try_all(vector<string>& v){
    vector<vi> ans(5, vi(6));
    
    while(true){
        rep(i, 0, v.size()){
            rep(j, 1, 5){
                if(k == 1){
                    
                }
                rep(l, 1, 5){
                    
                }
            }
        }

        if(check(ans)) break;
    }

    return ans;
}

void solve(){
    vector<string> v(5);
    string s; cin >> s;

    vector<string> names(5);
    int l = 0; k = (s.size()-6)/2;
    while(cin >> s){
        string buffer = ""; int j = 0;
        while(s[j] < '0' or s[j] > '9') buffer += s[j], j++;
        names[l] = buffer, buffer = "";
        while(j < s.size()) buffer += s[j], j++;
        v[l] = buffer, l++;

        if(s[0] == 'T' and s[1] == 'P') break;
    }

    vector<vi> num = try_all(v); 

    rep(i, 1, k+1) cout << "P" << i << " ";
    cout << "Totals" << endl;
    rep(i, 0, 5){
        if(names[i] == "") continue;

        cout << names[i] << " ";
        rep(j, 0, k) cout << num[i][j] << " ";
        cout << num[i][5] << endl;
    }
}

int main(){
    int ttt; cin >> ttt;

    while(ttt--) solve();
    exit(0);
}
