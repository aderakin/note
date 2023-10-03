#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

const int MAXN = 1e5 + 10;

int n, m;
vector<int> g[MAXN];
int tin[MAXN], low[MAXN];

bool vis[MAXN];

vector<pair<int, int>> bridges;

int timer = 0;
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

void find_bridge() {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i);
    }

    for (auto &[u, v] : bridges) if (u > v) swap(u, v);
    sort(all(bridges));

    cout << bridges.size() << '\n';
    for (auto &[u, v] : bridges) cout << u << " " << v << '\n';
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    find_bridge();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}