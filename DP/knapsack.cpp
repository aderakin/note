#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

void setIO(string name = ""){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (!name.empty()) {
        if (fopen((name + ".inp").c_str(), "r")) { 
            freopen((name + ".inp").c_str(), "r", stdin);
            freopen((name + ".out").c_str(), "w", stdout);
        }
    }

}

const int MAXN = 1e3 + 10;
const int MAXM = 1e4 + 10;

int c[MAXN];
int v[MAXM];

int dp[MAXN][MAXM];

int knap(int i, int w) {
    if (i <= 0) return 0;

    int &res = dp[i][w];
    if (res != -1) return res;

    if (w - c[i] < 0) return res = knap(i-1, w);
    return res = max(knap(i-1, w), v[i] + knap(i-1, w-c[i]));
}

vector<int> ans;
void trace(int i, int w) {
    if (i <= 0 || w < 0) return;

    int res = knap(i, w);
    if (res == knap(i-1, w)) return trace(i-1, w);

    ans.push_back(i);
    return trace(i-1, w-c[i]);
}

void solve() {
    int n, w; cin >> n >> w;

    for (int i = 1; i <= n; i++) cin >> c[i] >> v[i];

    memset(dp, -1, sizeof dp);
    trace(n, w);

    cout << knap(n, w) << endl;
    cout << ans.size() << endl;
    reverse(all(ans));
    for (int i : ans) cout << i << " ";
}

signed main() {
    setIO("knapsack2");
    int t = 1;
    // cin >> t;
    while (t--) solve();
}