#include <bits/stdc++.h>
using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define rep(i,x,n) for(auto i=x;i<n;i++)
#define repr(i,n,x) for(auto i=n;i>=x;i--)
#define forr(x, v) for(auto& x: v)
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a.size())
#define endl '\n'
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back

typedef long long ll;
typedef pair<double, double> pdd;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

template<typename X, typename Y> bool ckmin(X& x, const Y& y) { return (y < x) ? (x=y,1):0; }
template<typename X, typename Y> bool ckmax(X& x, const Y& y) { return (x < y) ? (x=y,1):0; }

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;

void no(){ cout << "NO" << endl; }
void yes(){ cout << "YES" << endl; }

const int MAX = 2e5+10, MOD = 1e9+7;

double cross(pdd v, pdd w){
    return v.ff*w.ss - v.ss*w.ff;
}

double area(vector<pdd> p){
    double area = 0;
    rep(i, 0, sz(p)) area += cross(p[i], p[(i+1)%sz(p)]);
    return abs(area)/2.0;
}

bool solve(){
    vector<pdd> t(5); forr(x, t) cin >> x.ff >> x.ss;

    bool ok = false;
    forr(x, t) if(x.ff or x.ss) ok = true;
    if(!ok) return false;

    double ma = 0;
    rep(j, 0, 5){
        vector<pdd> v;
        rep(k, 0, 5){
            if(j == k) continue;
            v.eb(t[k]);
        }
        sort(all(v));
        do{
            bool can = true;
            rep(i, 0, 4){
                double ax = (v[(i+1)%4].ff-v[i].ff), ay = (v[(i+1)%4].ss-v[i].ss),
                    bx = (v[(i+2)%4].ff-v[(i+1)%4].ff), by = (v[(i+2)%4].ss-v[(i+1)%4].ss); 
                if(ax*by-ay*bx <= 0) can = 0;
            }
            if(can) ckmax(ma, area(v));
        } while(next_permutation(all(v)));
    }

    cout << ma << endl;
    return true;
}

int main(){ _
    while(solve()) continue;

    exit(0);
}
