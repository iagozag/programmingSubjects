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
typedef pair<double,double> pdd;
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

int n;

const double EPS = 1e-12;
mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count());

struct pt {
	double x, y;
	pt(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
	pt operator + (const pt& p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt& p) const { return pt(x-p.x, y-p.y); }
	pt operator * (double c) const { return pt(x*c, y*c); }
	pt operator / (double c) const { return pt(x/c, y/c); }
};

double dot(pt p, pt q) { return p.x*q.x+p.y*q.y; }
double cross(pt p, pt q) { return p.x*q.y-p.y*q.x; }
double dist(pt p, pt q) { return sqrt(dot(p-q, p-q)); }

pt center(pt p, pt q, pt r) {
	pt a = p-r, b = q-r;
	pt c = pt(dot(a, p+r)/2, dot(b, q+r)/2);
	return pt(cross(c, pt(a.y, b.y)), cross(pt(a.x, b.x), c)) / cross(a, b);
}

struct circle {
	pt cen;
	double r;
	circle(pt cen_, double r_) : cen(cen_), r(r_) {}
	circle(pt a, pt b, pt c) {
		cen = center(a, b, c);
		r = dist(cen, a);
	}
	bool inside(pt p) { return dist(p, cen) < r+EPS; }
};

void solve(){
    vector<pt> v(n);
    rep(i, 0, n){
        double x, y; cin >> x >> y;
        v[i] = pt(x, y);
    }

    shuffle(all(v), rng);
    circle c(pt(0, 0), 0);
    rep(i, 0, n) if(!c.inside(v[i])){
        c = circle(v[i], 0); 
        rep(j, 0, i) if(!c.inside(v[j])){
            c = circle((v[i]+v[j])/2.0, dist(v[i], v[j])/2.0);
            rep(k, 0, j) if(!c.inside(v[k])) c = circle(v[i], v[j], v[k]);
        }
    }

    cout << fixed << setprecision(2) << c.cen.x << " " << c.cen.y << " " << c.r << endl;
}

int main(){ _
    int cnt = 1; // cin >> ttt;

    cin >> n;
    cout << "Instancia " << cnt++ << endl;
    solve();

    while(cin >> n and n){
        cout << endl;
        cout << "Instancia " << cnt++ << endl;
        solve();
    }

    exit(0);
}
