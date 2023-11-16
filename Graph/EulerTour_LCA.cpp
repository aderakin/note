#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define int long long

#define all(v) v.begin(), v.end()
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

template<
    class S, 
    S (*op) (S, S),
    S (*e) ()
> struct SegTree {
	int _n;
	vector<S> st;
	
	SegTree(int _n) : _n(_n), st(_n*4+1, e()) {}

	void update(int p, S x, int id, int lx, int rx) {
		if (p > rx || p < lx) return;
		if (lx == rx) {
			st[id] = x;
			return;
		}

		int mid = (lx + rx) / 2;
		update(p, x, id*2, lx, mid);
		update(p, x, id*2 + 1, mid+1, rx);

		st[id] = op(st[id*2], st[id*2 + 1]);
	}

	S query(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return e();
		if (u <= lx && v >= rx) return st[id];

		int mid = (lx + rx) / 2;
		return op(query(u, v, id*2, lx, mid), query(u, v, id*2 + 1, mid+1, rx));
	}

	void update(int p, S x) { 
		update(p, x, 1, 1, _n); 
	}

	S query(int u, int v) {
		return query(u, v, 1, 1, _n); 
	}
};

const int MAXN = 2e5 + 10;

vector<int> g[MAXN];
int timer = 0, tin[MAXN], euler[MAXN*2], depth[MAXN];

void dfs_euler(int u, int p = -1) {
    tin[u] = ++timer;
    euler[timer] = u;

    for (int v : g[u]) if (v != p) {
		depth[v] = depth[u]+1;
        dfs_euler(v, u);
        euler[++timer] = u;
    }
}

int mn_tin(int u, int v) {
    if (u == -1) return v;
    if (v == -1) return u;

    return tin[u] < tin[v] ? u : v;
}

int e_lca() { return -1; }
SegTree<int, mn_tin, e_lca> tree_lca(MAXN*2);

void build_lca(int root) {
    dfs_euler(root);

    for (int i = 1; i <= timer; i++) {
        tree_lca.update(i, euler[i]);
    }
}

int lca(int u, int v) {
    if (tin[u] > tin[v]) swap(u, v);
	return tree_lca.query(tin[u], tin[v]);
}

int dist(int u, int v) { 
    return depth[u] + depth[v] - 2*depth[lca(u,v)]; 
}

void solve() {
	int n, root, m;
	cin >> n >> root >> m;
	REP(i, n-1) {
		int u, v; cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	build_lca(root);

	REP(_, m) {
		int u, v;
		cin >> u >> v;
		cout << lca(u, v) << endl;
	}
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}