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

int main(){ _
    int t; cin >> t;

    map<string,int> stod;
    stod["*....."] = 1, stod["*.*..."]  = 2, stod["**...."] = 3, stod["**.*.."] = 4, stod["*..*.."] = 5,
    stod["***..."] = 6, stod["****.."]  = 7, stod["*.**.."] = 8, stod[".**..."] = 9, stod[".***.."] = 0;
    map<int,string> dtos;
    forr(x, stod) dtos[x.ss] = x.ff;

    while(t != 0){
        char c; cin >> c;
        if(c == 'S'){
            string s; cin >> s;
            for(int k = 0; k < 6; k += 2) 
                rep(i, 0, s.size())
                    cout << dtos[s[i]-'0'][k] << dtos[s[i]-'0'][k+1] << " \n"[i == s.size()-1]; 
        } else{
            vector<string> v(t, ""); cin.ignore();
            rep(i, 0, 3){
                string s; getline(cin, s); int j = 0, k = 0;
                while(k < t) v[k] += s[j], v[k] += s[j+1], j += 3, k++;
            }
            forr(x, v) cout << stod[x];
            cout << endl;
        }

        cin >> t;
    }

    exit(0);
}
