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

const int MAXN = 1e6 + 10;
const int MOD = 1e9 + 7;

struct Node {
    int child[27];
    int end = 0;
} trie[MAXN];
int timer = 0;

void trie_add(string &s) {
    int x = 0;

    for (char c : s) {
        int id = c - 'a';

        if (trie[x].child[id] == 0) {
            trie[x].child[id] = ++timer;
        }

        x = trie[x].child[id];
    }

    trie[x].end = 1;
}

int find_string(string &s) {
    int x = 0;
    for (char c : s) {
        int id = c - 'a';
        if(trie[x].child[id] == 0) {
            return 0;
        }
        x = trie[x].child[id];
    }

    return trie[x].end;
}

void solve() {
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        
        trie_add(s);
    }

    string X; cin >> X;
    int m = X.size();
    vector<int> dp(m+1);

    dp[0] = 1;
    for (int i = 0; i < m; i++) {
        int x = 0;

        for (int j = i; j < m; j++) {
            int id = X[j] - 'a';

            if (trie[x].child[id] != 0) {
                dp[j+1] += dp[i] %= MOD;
                x = trie[x].child[id];
            }
            else break;
        }   
    }

    cout << dp.back();
}

signed main() {
    setIO("");
    int t = 1;
    // cin >> t;
    while (t--) solve();
}