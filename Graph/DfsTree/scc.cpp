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

vector<vector<int>> scc;

int timer = 0;

vector<int> order;
void dfs(int u) {
    timer++;
    tin[u] = low[u] = timer;
    vis[u] = 1;
    order.push_back(u);

    for (int v : g[u]) {
        if (tin[v] == -1) dfs(v);

        if (vis[v]) { 
            low[u] = min(low[u], low[v]);
        } 
    }

    if (low[u] == tin[u]) {
        scc.push_back(vector<int>());
        while (1) {
            int v = order.back(); order.pop_back(); vis[v] = 0;
            scc.back().push_back(v);

            if (u == v) break;
        }
    }
}

void tarjan() {
    memset(tin, -1, sizeof tin);
    for (int i = 1; i <= n; i++) if (tin[i] == -1) dfs(i);

    cout << scc.size() << '\n';

    for (auto &v : scc) sort(all(v));
    sort(all(scc), [] (vector<int> &x, vector<int> &y) {
        if (x.size() == y.size()) return x < y;
        return x.size() < y.size(); 
    });

    for (auto &v : scc) {
        cout << v.size() << '\n';
        for (int i : v) cout << i << " ";
        cout << '\n';
    } 
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }

    tarjan();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}