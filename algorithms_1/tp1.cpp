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

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

int t = 0;
vector<vi> g;
vi tin, low;
vector<bool> vis;
stack<ii> st;
set<int> cutp; 
set<set<int>> bc;

void dfs(int v, int p){
    vis[v] = 1, tin[v] = low[v] = t++;

    int c = 0;
    forr(ve, g[v]){
        if(ve == p) continue;
        if(vis[ve]){
            low[v] = min(low[v], tin[ve]);
            if(tin[ve] < tin[v]) st.push({v, ve});
        }
        else{
            c++, st.push({v, ve});
            dfs(ve, v);
            low[v] = min(low[v], low[ve]);
            if((c > 1 and !p) or (low[ve] >= tin[v] and p)){
                cutp.insert(v);
                set<int> curbc;
                while(st.top().ff != v or st.top().ss != ve){
                    curbc.insert(st.top().ff), curbc.insert(st.top().ss);
                    st.pop();
                }
                curbc.insert(st.top().ff), curbc.insert(st.top().ss); 
                st.pop();

                bc.insert(curbc);
            }
        }
    }
}

void solve(){
    int n, m; cin >> n >> m; ++n; 
    g = vector<vi>(n); tin = low = vi(n, -1), vis = vector<bool>(n);
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        g[a].eb(b), g[b].eb(a);
    }

    rep(i, 1, n){
        if(tin[i] == -1) dfs(i, 0);

        set<int> curbc;
        while(!st.empty()){
            curbc.insert(st.top().ff), curbc.insert(st.top().ss);
            st.pop();
        }
        if(curbc.size()) bc.insert(curbc);
    }
    cout << cutp.size() << endl;
    forr(x, cutp) cout << x << endl;

    cout << bc.size() << endl;
    int bccnt = n, vt = 0;
    vector<pair<int,int>> ans; set<int> vtx;
    forr(x, bc){
        cout << bccnt++ << " " << x.size() << " ";
        if(!vtx.count(bccnt-1)) vt++, vtx.insert(bccnt-1);

        int end = 0; 
        forr(y, x){
            cout << y << " \n"[end == x.size()-1], end++;
            if(cutp.count(y)){
                ans.eb(y, bccnt-1);
                if(!vtx.count(y)) vt++, vtx.insert(y);
            }
        }
    }
    sort(all(ans));

    cout << vt << " " << ans.size() << endl;
    forr(x, ans) cout << x.ff << " " << x.ss << endl;
}

int main(){ _
    int ttt = 1;

    while(ttt--) solve();

    exit(0);
}
