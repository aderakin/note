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

template<
    class S, 
    S (*op) (S, S),
    S (*e) ()
> struct SegTree {
	int _n;
	vector<S> st;
	
	SegTree() {}
	SegTree(int _n) : _n(_n), st(_n*4+1, e()) {}

	void update(int p, S x, int id, int lx, int rx) {
		if (p > rx || p < lx) return;
		if (lx == rx) {
			st[id] = x;
			return;
		}

		int mid = (lx + rx) >> 1;
		update(p, x, id*2, lx, mid);
		update(p, x, id*2 + 1, mid+1, rx);

		st[id] = op(st[id*2], st[id*2 + 1]);
	}

	S query(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return e();
		if (u <= lx && v >= rx) return st[id];

		int mid = (lx + rx) >> 1;
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
const bool VALS_IN_EDGES = false;

int n; vector<int> g[MAXN];
int par[MAXN], nxt[MAXN], depth[MAXN], sz[MAXN], dfs_number;
int in[MAXN]; 

void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }

void dfs_sz(int u) { 
    sz[u] = 1; 
    for (auto &v : g[u]) {
        par[v] = u; depth[v] = depth[u]+1;
        g[v].erase(find(all(g[v]), u)); /// remove parent 
        dfs_sz(v); sz[u] += sz[v];
        if (sz[v] > sz[g[u][0]]) swap(v,g[u][0]);
    }
}

void dfs_hld(int u) {
    in[u] = ++dfs_number;
    for (auto &v : g[u]) {
        nxt[v] = (v == g[u][0] ? nxt[u] : v);
        dfs_hld(v);
    }
}

int lca(int u, int v) {
    for (; nxt[u] != nxt[v]; v = par[nxt[v]]) {
        if (depth[nxt[u]] > depth[nxt[v]]) swap(u,v);
    }

    return depth[u] < depth[v] ? u : v;
}

int dist(int u, int v) { return depth[u]+depth[v]-2*depth[lca(u,v)]; }

using S = int;
S op(S l, S r) { return l + r; }
S e() { return 0; }

SegTree<S, op, e> tree(MAXN);

template <class B>
void processPath(int u, int v, B op_hld) {
    for (; nxt[u] != nxt[v]; v = par[nxt[v]]) {
        if (depth[nxt[u]] > depth[nxt[v]]) swap(u,v);
        op_hld(in[nxt[v]], in[v]); 
    }

    if (depth[u] > depth[v]) swap(u,v);

    op_hld(in[u]+VALS_IN_EDGES, in[v]); 
}

ll queryPath(int u, int v) { 
    ll res = e(); 
    processPath(u, v, [&res] (int l, int r) { 
        res = op(res, tree.query(l, r)); 
    });
    return res; 
}

void updateNode(int u, int x) { tree.update(in[u], x); }

// void updatePath(int u, int v, int x) { 
//     processPath(u, v, [&x] (int l, int r) {
//         tree.apply(l, r, x);
//     });
// }

void init(int rt = 1) { 
    par[rt] = depth[rt] = dfs_number = 0; 
    dfs_sz(rt); 
    nxt[rt] = rt; dfs_hld(rt); 
}

int a[MAXN];

void solve() {
    cin >> n;
    int Q; cin >> Q;

    REP(i, n) cin >> a[i];
    REP(_, n-1) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    init();
    REP(i, n) updateNode(i, a[i]);

    REP(_, Q) {
        int tp;
        cin >> tp;

        if (tp == 1) {
            int s, x;
            cin >> s >> x;
            updateNode(s, x);
        }
        else {
            int s;
            cin >> s;

            cout << queryPath(1, s) << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}