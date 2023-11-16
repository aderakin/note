#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

struct DSU {
    vector<int> lab, sz;
    int connected;

    DSU(int _n) : lab(_n+1), sz(_n+1) {
        connected = _n;
        for (int i = 1; i <= _n; i++) {
            sz[i] = 1;
            lab[i] = i;        
        }
    }

    int get_root(int u) {
        if (u == lab[u]) return u;
        return lab[u] = get_root(lab[u]);
    }

    bool merge(int u, int v) {
        u = get_root(u); v = get_root(v);
        if (u == v) return false;

        if (sz[u] < sz[v]) swap(u, v);
        connected--;
        sz[u] += sz[v];
        lab[v] = u;
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
        if (dsu.merge(u, v)) {
            total += c;
            // tree.push_back(e);
        }
    }

    return total;
}