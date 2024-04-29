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
    int t;

    while(cin >> t){
        queue<int> q; priority_queue<int> pq; stack<int> s;
        map<int, string> mp;
        mp[0] = "queue", mp[1] = "priority queue", mp[2] = "stack";

        unordered_set<int> ans = {0, 1, 2};
        rep(i, 0, t){
            int a, b; cin >> a >> b;
            if(a == 1) q.push(b), pq.push(b), s.push(b);
            else{
                if(q.front() != b and ans.count(0)) ans.erase(0);
                if(pq.top() != b and ans.count(1)) ans.erase(1);
                if(s.top() != b and ans.count(2)) ans.erase(2);
                q.pop(), pq.pop(), s.pop();
            }
        }

        if(ans.size() == 0) cout << "impossible";
        else if(ans.size() > 1) cout << "not sure";
        else cout << mp[*ans.begin()];
        cout << endl;
    };

    exit(0);
}
