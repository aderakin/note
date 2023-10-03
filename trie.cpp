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

struct Node {
    pair<int, int> child[27];
    int end;
} trie[MAXN];
int timer = 0;

void trie_add(string &s) {
    int x = 0;

    for (char c : s) {
        int id = c - 'a';

        if (trie[x].child[id].first == 0) {
            trie[x].child[id].first = ++timer;
        }

        x = trie[x].child[id].first;
        trie[x].child[id].second++;

        trie[x].end = id;
    }

}

int find_string(string &s) {
    int x = 0;
    for (char c : s) {
        int id = c - 'a';
        if(trie[x].child[id].first == 0) {
            return 0;
        }
        
        x = trie[x].child[id].first;
    }

    return trie[x].child[(s.back() - 'a')].second;
}

void solve() {
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        trie_add(s);
    }

    int m; cin >> m; 
    for (int i = 0; i < m; i++) {
        string s; cin >> s;

        cout << find_string(s) << '\n';
    }
}

signed main() {
    setIO("");
    int t = 1;
    // cin >> t;
    while (t--) solve();
}