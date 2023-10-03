#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

const int MAXN = 2e5 + 10;

int n;
int par[MAXN], s[MAXN], head[MAXN], depth[MAXN];
int ti = 0;
vector<int> g[MAXN];

// call dfs(root)
//      hld(root)

void dfs(int u) {
    s[u] = 1;

    for (int &v: g[u]) {
        par[v] = u; depth[v] = depth[u] + 1; 
        g[v].erase(find(all(g[v]), u)); // remove parent from adj list

        dfs(v); 
        s[u] += s[v];
        if (s[v] > s[g[u][0]]) swap(v, g[u][0]);
    }
}

void hld(int u) {
    for (int &v : g[u]) {
        head[v] = (v == g[u][0] ? head[u] : v);
        hld(v);
    }
}

int lca(int u, int v) {
    for (; head[u] != head[v]; v = par[head[v]]) {
        if (depth[head[u]] > depth[head[v]]) swap(u,v);
    }

    return depth[u] < depth[v] ? u : v;
}

int dist(int u, int v) { // # edges on path
    return depth[u] + depth[v] - 2*depth[lca(u,v)]; 
}