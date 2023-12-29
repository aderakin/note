
vector<int> tree_diameter(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<ll> dist(n+1);
    vector<int> parent(n+1);

    function<void(int, int, ll)> dfs = [&] (int u, int fu, ll cur_dist) {
        dist[u] = cur_dist;
        parent[u] = fu;
        for (auto v : adj[u]) if (v != fu) {
            dfs(v, u, cur_dist + 1);
        }
    };
    dfs(1, -1, 0);
    // r = furthest node from root
    int r = max_element(all(dist)) - dist.begin();
    dfs(r, -1, 0);
    // r->s = longest path
    int s = max_element(all(dist)) - dist.begin();

    vector<int> path;
    for (int x = s; x >= 0; x = parent[x]) path.push_back(x);

    return path;
}