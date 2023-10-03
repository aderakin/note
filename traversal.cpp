#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(), v.end()

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

vector<int> g[MAXN];

int dfs_leaf(int u, int p) {
    int res = 0;

    for (int v : g[u]) {
        if (v == p) continue;
        res += dfs_leaf(v, u);
    }

    if (res == 0) res++;

    return res;
}