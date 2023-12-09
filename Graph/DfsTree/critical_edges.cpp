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

struct Brigdes {
    int n;
    int timer;
    vector<vector<int>> g;
    vector<int> tin, low;
    vector<bool> vis;

    vector<pii> bridges;

    Brigdes (int n, const vector<vector<int>> &g) : n(n), g(g), 
            timer(0), tin(n+1), low(n+1), vis(n+1, 0) {}

    void dfs(int u, int p = -1) {
        timer++;
        tin[u] = low[u] = timer;
        vis[u] = 1;

        for (int v : g[u]) {
            if (v == p) continue;

            if (vis[v]) { 
                // back edge
                low[u] = min(low[u], tin[v]);
            } 
            else { 
                dfs(v, u);

                // tree edge
                low[u] = min(low[u], low[v]);

                if (tin[u] < low[v]) {
                    bridges.push_back({u, v});
                }
            }
        }
    }

    vector<pii> find_bridge() {
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) dfs(i);
        }

        for (auto &[u, v] : bridges) if (u > v) swap(u, v);
        return bridges;
    }
};

struct Edge {
    int u, v, w;

    friend bool operator < (const Edge &x, const Edge &y) {
        return x.w < y.w;
    }
};

struct DSU {
    vector<int> root, sz;
    int connected;

    DSU(int _n) : root(_n+1), sz(_n+1) {
        connected = _n;
        for (int i = 1; i <= _n; i++) {
            sz[i] = 1;
            root[i] = i;        
        }
    }

    int get_root(int u) {
        if (u == root[u]) return u;
        return root[u] = get_root(root[u]);
    }

    bool unite(int u, int v) {
        u = get_root(u); v = get_root(v);
        if (u == v) return false;

        if (sz[u] < sz[v]) swap(u, v);
        connected--;
        sz[u] += sz[v];
        root[v] = u;
        return true;
    }

    bool same_component(int u, int v) {
        return get_root(u) == get_root(v);
    }

    int get_size(int u) {
        return sz[get_root(u)];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> E_tmp;
    vector<int> compress_tmp;

    REP(i, m) {
        int u, v, w;
        cin >> u >> v >> w;
        if (u > v) swap(u, v);

        E_tmp.push_back({u, v, w});
        compress_tmp.push_back(w);
    }    

    create_unique(compress_tmp);
    vector<vector<pii>> E(compress_tmp.size()+1);

    for (auto &[u, v, w] : E_tmp) {
        w = lower_bound(all(compress_tmp), w) - compress_tmp.begin() + 1;
        E[w].push_back({u, v});
    }

    vector<pii> ans;

    DSU dsu(n);
    REP(_, compress_tmp.size()) {
        clog << db(_) << endl;

        vector<vector<int>> g;
        map<pii, pii> mp;

        vector<int> points;
        for (auto &[u, v] : E[_]) {
            int ru = dsu.get_root(u);
            int rv = dsu.get_root(v);

            points.push_back(ru);
            points.push_back(rv);
        }

        create_unique(points);        
        g.resize(points.size()+1);

        for (auto &[u, v] : E[_]) {
            int ru = dsu.get_root(u), rv = dsu.get_root(v);
            ru = lower_bound(all(points), ru) - points.begin() + 1;
            rv = lower_bound(all(points), rv) - points.begin() + 1;

            g[ru].push_back(rv);
            g[rv].push_back(ru);

            if (ru > rv) swap(ru, rv);
            mp[{ru, rv}] = {u, v};
        }

        REP(i, points.size()) {
            clog << db(i);
            for (int v : g[i]) clog << v << " ";
            clog << endl;
        }

        Brigdes bri(points.size(), g);
        auto res = bri.find_bridge();

        auto check = [&] (pii &e) { 
            const auto &[u, v] = e;
            return count(all(g[u]), v) <= 1;
        };

        for (auto &e : res) if (check(e)) ans.push_back(mp[e]);

        for (auto &[u, v] : E[_]) dsu.unite(u, v); 
    }

    create_unique(ans);

    cout << ans.size() << endl;
    for (auto &[u, v] : ans) cout << u << " " << v << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}