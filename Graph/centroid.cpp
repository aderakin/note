#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());
#define REP(i, n)  for (int i = 1, _n = (n); i <= _n; i++)
#define REPD(i, n)  for (int i = (n); i--; )
#define FOR(i, a, b)  for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a)  for (int i = (b), _a = (a); i >= _a; i--)

#define endl '\n'
#define db(val) "[" #val " = " << (val) << "] "
#ifdef LOCAL_DEBUG  
#   define clog cerr 
#else
#   define clog if (0) cerr
#endif

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }

const int MAXN = 1e5 + 10;
const int inf = 2e9 + 10;

int n;
vector<int> g[MAXN];
int sz[MAXN], par[MAXN];
bool dead[MAXN];

void dfs_size(int u, int p) {
    sz[u] = 1;
    for (int v : g[u]) if (v != p && !dead[v]) {
        dfs_size(v, u);
        sz[u] += sz[v];
    }

    sz[u];
}

int get_centroid(int u, int p, int m) {
    for (int v : g[u]) if (v != p && !dead[v]) {
        if (sz[v]*2 > m) 
            return get_centroid(v, u, m);
    }
    return u;
}

int decompose(int u = 1) {
    dfs_size(u, -1);
    u = get_centroid(u, -1, sz[u]);
    
    // do something
    dead[u] = 1;

    for (int v : g[u]) if (!dead[v]) {
        int x = decompose(v);
        par[x] = u;
    }

    return u;
}

    
void solve() {
    cin >> n;
    REP(i, n-1) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    decompose();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}