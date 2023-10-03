#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

const int MAXN = 5e5 + 10;

vector<int> g[MAXN];
int timer = 0, tin[MAXN], euler_tour[2*MAXN];

void dfs(int u, int p) {
	tin[u] = ++timer;  // The time when we first visit a node
	euler_tour[timer] = u;

	for (int i : g[u]) {
		if (i != p) {
			dfs(i, u);
			euler_tour[++timer] = u;
		}
	}
}

int mn_tin(int u, int v) {
	if (u == -1) return v;
	if (v == -1) return u;

	return (tin[u] < tin[v] ? u : v);
}

// 1-based
struct SegtreeLCA {
	typedef ll T;
	static constexpr T unit = -1;

	int sz;
	vector<T> st;
	
	SegtreeLCA(int ssz) : sz(ssz) {
		st.resize(ssz*4 + 1);
	}

	T f(T a, T b) { return mn_tin(a, b); }

	void update(int p, T x, int id, int lx, int rx) {
		if (p > rx || p < lx) return;
		if (lx == rx) {
			st[id] = x;
			return;
		}

		int mid = (lx + rx) / 2;
		update(p, x, id*2, lx, mid);
		update(p, x, id*2 + 1, mid+1, rx);

		st[id] = f(st[id*2], st[id*2 + 1]);
	}

	T query(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return unit;
		if (u <= lx && v >= rx) return st[id];

		int mid = (lx + rx) / 2;
		return f(query(u, v, id*2, lx, mid), query(u, v, id*2 + 1, mid+1, rx));
	}

	void update(int p, T x) { 
		update(p, x, 1, 1, sz); 
	}

	T query(int u, int v) {
		return query(u, v, 1, 1, sz); 
	}
};

SegtreeLCA tree_lca(2*MAXN);

void build_lca() {
    dfs(1, -1);

    for (int i = 1; i <= timer; i++) {
        tree_lca.update(i, euler_tour[i]);
    }
}

int lca(int a, int b) {
    if (tin[a] > tin[b]) swap(a, b);
    return tree_lca.query(tin[a], tin[b]);
}

void solve() {
    int n, q;
    cin >> n >> q;

    for (int i = 2; i <= n; i++) {
        int x; cin >> x;
        x++;
        g[i].push_back(x);
        g[x].push_back(i);
    }

    build_lca();

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u++, v++;
        cout << lca(u, v)-1 << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}