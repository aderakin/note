#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define int long long
using pii = pair<int, int>;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());
#define REP(i, n)  for (int i = 1, _n = (n); i <= _n; i++)
#define REPD(i, n)  for (int i = (n); i >= 1; i--)
#define FOR(i, a, b)  for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a)  for (int i = (b), _a = (a); i >= _a; i--)

#define endl '\n'
#define db(val) "[" #val " = " << (val) << "] "
#ifdef LOCAL_DEBUG  
#   define clog cerr 
#else
#   define clog if (0) cerr
#endif

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }

// https://judge.yosupo.jp/problem/line_add_get_min
// - use [-SZ, SZ] for negative points

using point = complex<ll>;
ll f(point L, ll x) {return L.real() * x + L.imag();}

const ll inf = 2e18 + 10;

const int SZ = 1e9 + 10;
struct LichaoTree {
	struct Node {
		point line;
		Node *l, *r;

		Node() : line(point(0LL, inf)), l(NULL), r(NULL) {}
	};

	Node *root = new Node();

	void expand(Node *me) {
		if(!me->l) me->l = new Node();
		if(!me->r) me->r = new Node();
	}

	void add_line(Node *me, int lx, int rx, point nw) {
		int mid = (lx + rx) >> 1;
		bool c1 = f(nw, lx) < f(me->line, lx);
		bool c2 = f(nw, mid) < f(me->line, mid);
		if(c2) swap(me->line, nw);
		if(lx == rx) return;

		expand(me);
		if(c1 != c2) add_line(me->l, lx, mid, nw);
		else add_line(me->r, mid+1, rx, nw);
	}

	ll query(Node *me, int lx, int rx, int x) {
		int mid = (lx + rx) >> 1;
		if(lx == rx) return f(me->line, x);

		expand(me);
		if(x < mid) return min(f(me->line, x), query(me->l, lx, mid, x));
		else return min(f(me->line, x), query(me->r, mid+1, rx, x));
	}

	void add_line(point nw) { add_line(root, 0, SZ, nw); }
	ll query(int x) { return query(root, 0, SZ, x); } 

} lt;

void solve() {
	int n, Q;
	cin >> n >> Q;

	REP(i, n) {
		int a, b;
		cin >> a >> b;
		lt.add_line({a, b});
	}

	REP(_, Q) {
		int qt;
		cin >> qt;

		if (qt == 0) {
			int a, b;
			cin >> a >> b;
			lt.add_line({a, b});
		}
		else {
			int x;
			cin >> x;
			cout << lt.query(x) << endl;
		}
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t = 1;
	while (t--) solve();
}