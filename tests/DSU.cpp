#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

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

void solve() {
    int n, q; cin >> n >> q;

    DSU dsu(n);

    for (int i = 0; i < q; i++) {
        int tp, u, v;
        cin >> tp >> u >> v;
        if (tp == 0) {
            dsu.merge(u, v);
        }
        else {
            cout << (dsu.same_component(u, v)) << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}