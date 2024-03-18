#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define int long long

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

const int SZ = 1e9 + 1e5 + 10;
template<
	class S,
	S (*op) (S, S),
	S (*e) ()
> struct DynamicSegTree {
	S val = e(); DynamicSegTree<S, op, e> *c[2];
	DynamicSegTree() { c[0] = c[1] = NULL; }

	void update(int p, S x, int lx = 0LL, int rx = SZ) { // add x
		if (p > rx || p < lx) return;
		if (lx == p && rx == p) { 
			val = op(val, x);
			// val = x; 
			return; 
		}

		int mid = (lx + rx) >> 1;
		if (p <= mid) {
			if (!c[0]) c[0] = new DynamicSegTree<S, op, e>();
			c[0]->update(p, x, lx, mid);
		} 
		else {
			if (!c[1]) c[1] = new DynamicSegTree<S, op, e>();
			c[1]->update(p, x, mid+1, rx);
		}

		val = e(); FOR(i,0,1) if (c[i]) val = op(val, c[i]->val);
	}
	S query(int u, int v, int lx = 0LL, int rx = SZ) { // query sum of segment
		if (v < lx || rx < u) return e();
		if (u <= lx && rx <= v) return val;

		int mid = (lx + rx) >> 1; S res = e();
		if (c[0]) res = op(res, c[0]->query(u, v, lx, mid));
		if (c[1]) res = op(res, c[1]->query(u, v, mid+1, rx));

		return res;
	}	
};

using S = int;
S op(S l, S r) { return l+r; }
S e() { return 0; }

const int MAXN = 5e5 + 10;
int a[MAXN];

void solve() {
    int n, q;
    cin >> n >> q;
    REP(i, n) cin >> a[i];

    DynamicSegTree<S, op, e> tree;
    REP(i, n) tree.update(i-1, a[i]);

    REP(_, q) {
        int tp; cin >> tp;
        int u, v;
        cin >> u >> v;

        if (tp == 0) tree.update(u, v);
        else cout << tree.query(u, v-1) << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}