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
typedef pair<int,int> pii;
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

struct pt {
	double x, y;
	pt(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	pt operator + (const pt& p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt& p) const { return pt(x-p.x, y-p.y); }
	pt operator * (double c) const { return pt(x*c, y*c); }
	pt operator / (double c) const { return pt(x/c, y/c); }
    bool operator == (const pt p) const { return x == p.x and y == p.y; }
    bool operator < (const pt& p) const { return x < p.x || (x == p.x && y < p.y); }
};

double dot(pt p, pt q) { return p.x*q.x+p.y*q.y; }
double cross(pt p, pt q) { return p.x*q.y-p.y*q.x; }
double dist(pt p, pt q) { return sqrt(dot(p-q, p-q)); }

vector<pt> ch(vector<pt> v){
    int n = sz(v);
    if(n <= 3) return v;
    set<pt> anss;

    vector<pt> st;
    st.eb(v[0]), st.eb(v[1]);
    rep(i, 2, n){
        while(sz(st) > 1 and cross(st.back()-st[sz(st)-2], v[i]-st[sz(st)-2]) < 0)
            st.pop_back();
        st.eb(v[i]);
    }
    forr(x, st) anss.insert(x); 

    reverse(all(v));
    st.eb(v[0]), st.eb(v[1]);
    rep(i, 2, n){
        while(sz(st) > 1 and cross(st.back()-st[sz(st)-2], v[i]-st[sz(st)-2]) < 0)
            st.pop_back();
        st.eb(v[i]);
    }
    forr(x, st) anss.insert(x); 

    return vector(all(anss));
}

void solve(int n){
    vector<pt> v(n);
    rep(i, 0, n){
        int a, b; cin >> a >> b;
        v[i] = pt(a, b);
    }

    sort(all(v));
    
    int qnt = 0;
    while(sz(v)){
        qnt++;
        vector<pt> pts = ch(v);
        forr(p, pts) v.erase(find(all(v), p));
    }

    if(qnt&1) cout << "Take this onion to the lab!" << endl;
    else cout << "Do not take this onion to the lab!" << endl;
}

int main(){ _
    int ttt = 1; // cin >> ttt;

    while(cin >> ttt and ttt) solve(ttt);

    exit(0);
}
