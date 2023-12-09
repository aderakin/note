struct DSU {
    int _n;
    vector<int> root, sz;
    vector<array<int, 4>> mod;
    int connected, snap;

    DSU(int _n) : _n(_n), root(_n+1), sz(_n+1) {
        connected = _n;
        for (int i = 1; i <= _n; i++) {
            sz[i] = 1;
            root[i] = i;        
        }
    }

    void init() {
        connected = _n;
        snap = 0;
        for (int i = 1; i <= _n; i++) {
            sz[i] = 1;
            root[i] = i;        
        }
    }

    int get_root(int u) {
        if (u == root[u]) return u;
        return get_root(root[u]);
    }

    bool unite(int u, int v) {
        u = get_root(u); v = get_root(v);
        if (u == v) return false;

        if (sz[u] < sz[v]) swap(u, v);
        
        connected--;
        mod.push_back({u, v, sz[u], sz[v]});
        sz[u] += sz[v];
        root[v] = u;

        return true;
    }

    bool unite(pii &x) {
        return unite(x.first, x.second);
    }

    bool same_component(int u, int v) {
        return get_root(u) == get_root(v);
    }

    int get_size(int u) {
        return sz[get_root(u)];
    }

    void snapshot() {
        snap = mod.size();
    }

    void rollback(int t = -1) {
        if (t == -1) t = snap;

        while (mod.size() > t) {
            if (mod.empty()) return;
            auto a = mod.back(); mod.pop_back();
            connected++;

            root[a[0]] = a[0];
            root[a[1]] = a[1];
            sz[a[0]] = a[2];
            sz[a[1]] = a[3];
        } 
    }
};
