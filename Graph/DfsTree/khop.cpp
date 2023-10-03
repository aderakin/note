#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

const int MAXN = 2e5 + 10;

vector<int> g[MAXN];
int timer = 0, tin[MAXN], low[MAXN], joint[MAXN];

void dfs(int u, int p = -1) {
    timer++;
    tin[u] = low[u] = timer;
    int child = 0;

    for (int v : g[u]) {
        if (v == p) continue;

        if (tin[v]) low[u] = min(low[u], tin[v]);
        else {
            dfs(v, u);

            low[u] = min(low[u], low[v]);
            child++;

            if (tin[u] <= low[v] && p != -1) {
                joint[u] = 1;
            }
        }
    }

    if (p == -1 && child > 1) joint[u] = 1;
}

void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!tin[i]) dfs(i);
    }

    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (joint[i]) ans.push_back(i);
    }

    cout << ans.size() << endl;
    for (int i : ans) cout << i << " ";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}