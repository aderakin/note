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
        if (dsu.unite(u, v)) {
            total += c;
            // tree.push_back(e);
        }
    }

    return total;
}