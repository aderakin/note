#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(), v.end()

#define TASK "palin"
#define endl '\n'
// #define int long long

void solve() {

}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (fopen(TASK".inp", "r")) {
        freopen(TASK".inp", "r", stdin);
        freopen(TASK".out", "w", stdout);
        freopen(TASK".err", "w", stderr);
    }


    int t = 1;
    cin >> t;
    while (t--) solve();
}

// BINSEARCH
//======================================================================
bool check(int x) {

}

int last_true() {
    int lo = 0, hi = 1e9;
    
    while (lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;
		if (check(mid)) lo = mid;
        else hi = mid - 1;
	}

    return lo;
}

int first_true() {
    int lo = 1, hi = 1e9;
    
    while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (check(mid)) hi = mid;
        else lo = mid + 1;
	}

    return lo;
}

// COUNTING
//======================================================================
const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;

ll binpow(ll a, ll n, ll m) {
    a %= m;
    ll res = 1;

    while (n > 0) {
        if (n & 1) res = res * a % m;
        a = a * a % m;
        n /= 2;
    }
    return res;
}

ll fac[MAXN+1];
ll inv[MAXN+1];


ll nCr(int n, int r) { 
    return fac[n] * inv[r] % MOD * inv[n - r] % MOD; 
}

void _precalc() {
    fac[0] = 1;
	for (int i = 1; i <= MAXN; i++) { 
        fac[i] = fac[i - 1] * i % MOD; 
    }


    inv[MAXN] = binpow(fac[MAXN], MOD - 2, MOD);
	for (int i = MAXN; i >= 1; i--) { 
        inv[i - 1] = inv[i] * i % MOD; 
    }

}

// O(n^1/2)
map<int, int> factor(int n) {
	map<int, int> ret;
	for (int i = 2; i * i <= n; i++) {
		while (n % i == 0) {
            ret[i]++;
			n /= i;
		}
	}
	if (n > 1) { ret[n]++; }
	return ret;
} 

int v_p(int n, int p) {
    int ans = 0;

    int i = 1;
    while (n) {
        n /= p;
        ans += n;
    }

    return ans;
}

int max_div[];

void fc() {
    int x;
    int div_num = 1;
    
    while (x != 1) {
        int prime = max_div[x];
        int count = 0;
        while (x % prime == 0) {
            count++;
            x /= prime;
        }
        div_num *= count + 1;
    }
    
    cout << div_num << '\n';
}

// GRAPH
//======================================================================

const int MAXN = 1e5;

vector<int> adj[MAXN];
bool visited[MAXN];

void bfs(int u) {
    queue<int> q;
    q.push(u);

    while (!q.empty()) {
        int current_node = q.front();
        q.pop();

        visited[current_node] = true;

        for (int neighbor : adj[current_node]) {
            if (visited[neighbor]) continue; 
            q.push(neighbor); 
        }
    }
    
}

void dfs(int current_node) {

	visited[current_node] = true;

	for (int neighbor : adj[current_node]) { 
        if (visited[neighbor]) continue;
        dfs(neighbor); 
    }

}

// DSU-MST
//======================================================================

struct DSU {
    vector<int> lab;

    DSU(int _n) : lab(_n+1) {
        for (int i = 1; i <= _n; i++) lab[i] = i;        
    }

    int get_root(int u) {
        if (u == lab[u]) return u;
        return lab[u] = get_root(lab[u]);
    }

    bool merge(int u, int v) {
        u = get_root(u); v = get_root(v);
        if (u == v) return false;
        
        lab[v] = u;

        return true;
    }

    bool same_component(int u, int v) {
        return get_root(u) == get_root(v);
    }
};

int n;

struct Edge {
    int u, v; 
    ll w;

    friend bool operator < (const Edge& a, const Edge& b) {
        return a.w < b.w;
    }
};

vector<Edge> Graph;

ll mst(vector<Edge> &edges) {
    sort(all(edges));

    DSU dsu(n);
    ll total = 0;
    // vector<Edge> tree;

    for (const auto &e : edges) {
        const auto [u, v, c] = e;
        if (dsu.merge(u, v)) {
            total += c;
            // tree.push_back(e);
        }
    }

    return total;
}

// DIJKTRA
//======================================================================

const int MAXN = 1e5 + 10;

vector<pair<int, ll>> adj[MAXN];
ll dist[MAXN];

void dijktra(int start) {
    memset(dist, 0x3f, sizeof dist);

    using T = pair<ll, int>; // <dist, node>
	priority_queue<T, vector<T>, greater<T>> pq;

	dist[start] = 0;
	pq.push({0LL, start});

	while (!pq.empty()) {
		const auto [d, u] = pq.top();
		pq.pop();
		if (d != dist[u]) { continue; }

		for (const auto &[v, w] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
		}
	}
}

// EULER_TOUR LCA
//======================================================================
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

    void resize(int ssz) {
        sz = ssz;
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

	T get(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return unit;
		if (u <= lx && v >= rx) return st[id];

		int mid = (lx + rx) / 2;
		return f(get(u, v, id*2, lx, mid), get(u, v, id*2 + 1, mid+1, rx));
	}

	void update(int p, T x) { 
		update(p, x, 1, 1, sz); 
	}

	T get(int u, int v) {
		return get(u, v, 1, 1, sz); 
	}
};

SegtreeLCA tree_lca(0);

void build_lca() {
    dfs(1, -1);
    tree_lca.resize(timer);

    for (int i = 1; i <= timer; i++) {
        tree_lca.update(i, euler_tour[i]);
    }
}

int lca(int a, int b) {
    if (tin[a] > tin[b]) swap(a, b);
    return tree_lca.get(tin[a], tin[b]);
}


// SEGTREE
//======================================================================

// 1-based
struct Segtree {
	typedef ll T;
	static constexpr T unit = 0;

	int sz;
	vector<T> st;
	
	Segtree(int ssz) {
		sz = ssz;
		st.resize(ssz*4 + 1);
	}

	T f(T a, T b) { return min(a, b); }

	void update(int p, T x, int id = 1, int lx, int rx) {
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

	T query(int u, int v, int id = 1, int lx, int rx) {
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

const int MAXN = 1e6 + 10;
const int inf = 1e9 + 10;

int n;
int a[MAXN];

struct Node {
    int lazy;
    int val;

    friend bool operator < (const Node &x, const Node &y) {
        return x.val < y.val;
    }
};

// LAZY SEGTREE
//======================================================================

struct LazySegtree {
	typedef Node T;
	static constexpr Node unit = {0, inf};
	T st[4 * MAXN + 1];

	T f(T a, T b) { return min(a, b); } // (any associative fn)

    void build(int id = 1, int lx = 1, int rx = n) {
        if (lx == rx) {
            st[id].lazy = 0;
            st[id].val = a[lx];
            return;
        }

        int mid = (lx + rx) / 2;
        build(id*2, lx, mid);
        build(id*2+1, mid+1, rx);

        st[id] = f(st[id*2], st[id*2 + 1]);
    }

    void upd(int id) {
        st[id].val = f(st[id*2], st[id*2 + 1]).val;
        return;
    }

    void push(int id) {
        int t = st[id].lazy;
        if (t == 0) return;

        st[id*2].lazy = t; 
        st[id*2].val = t; 

        st[id*2 + 1].lazy = t;
        st[id*2 + 1].val = t;

        st[id].lazy = 0;
    }

	void update(int u, int v, int x, int id = 1, int lx = 1, int rx = n) {
		if (u > rx || v < lx) return;
		if (u <= lx && v >= rx) {
			st[id].val = x;
			st[id].lazy = x;

            // cerr << "here: " << u << " " << v << " " << lx << " " << rx << endl;
            // print();
			return;
		}

        push(id);

        // cerr << "here: " << u << " " << v << " " << lx << " " << rx << endl;
        // print();

		int mid = (lx + rx) / 2;
		update(u, v, x, id*2, lx, mid);
		update(u, v, x, id*2 + 1, mid+1, rx);

        upd(id);
	}

	T query(int u, int v, int id = 1, int lx = 1, int rx = n) {
		if (u > rx || v < lx) return unit;
		if (u <= lx && v >= rx) return st[id];

        push(id);

		int mid = (lx + rx) / 2;
		return f(query(u, v, id*2, lx, mid), query(u, v, id*2 + 1, mid+1, rx));
	}

    void print() {
        int ind = 1;
        int row_size = 1;
        
        while (ind <= n) {
            for (int i = 0; i < row_size; i++) {
                cerr << st[ind].lazy << "-" << st[ind++].val << '\t';
            }
            cerr << endl;
            row_size *= 2;
        }
        cerr << endl;
    }
} tree;
