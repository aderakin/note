// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

//#define int long long
#define endl '\n'

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define UNIQUE(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());
#define each(x, a) for (auto &x : a)
#define REP(i, n)  for (int i = 1, _n = (n); i <= _n; i++)
#define REP1(i, n)  for (int i = 0, _n = (n); i < _n; i++)
#define FOR(i, a, b)  for (int i = (a), _b = (b); i <= _b; i++)
#define FOR1(i, a, b)  for (int i = (a), _b = (b); i < _b; i++)
#define FORD(i, b, a)  for (int i = (b), _a = (a); i >= _a; i--)

#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)
#define db(val) "["#val" = "<<(val)<<"] "
#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#ifdef LOCAL_DEBUG   
#   define clog cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#   define DB() debug_block CONCAT(dbbl, __LINE__)
    int __db_level = 0;
    struct debug_block {
        debug_block() { clog << "{" << endl; ++__db_level; }
        ~debug_block() { --__db_level; clog << "}" << endl; }
    };
#else
#   define clog if (0) cerr
#   define DB(...)
#endif

template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) 
        return out << ")"; 
    else 
        return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }

#pragma region DS/trie

template <size_t X = 26, char margin = 'a'>
struct Trie {
    struct Node {
        array<int, X> nxt;
        int idx;
        ll num;
        Node(char c) : idx(-1), num(0LL) { fill(nxt.begin(), nxt.end(), -1); }
    };

    vector<Node> st;

    Trie(char c = '$') { st.emplace_back(c); }

    inline int &next(int i, int j) { return st[i].nxt[j]; }

    void add(const string &s, int x, int v = 1) {
        int pos = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int k = s[i] - margin;
            if (~next(pos, k)) {
                pos = next(pos, k);
                continue;
            }
            int npos = st.size();
            next(pos, k) = npos;
            st.emplace_back(s[i]);
            pos = npos;
        }
        st[pos].idx = x;
        st[pos].num += v;
    }

    int find(const string &s) {
        int pos = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            int k = s[i] - margin;
            if (next(pos, k) < 0) return -1;
            pos = next(pos, k);
        }
        return pos;
    }

    int move(int pos, char c) {
        assert(pos < (int)st.size());
        return pos < 0 ? -1 : next(pos, c - margin);
    }

    int size() const { return st.size(); }

    int idx(int pos) { return pos < 0 ? -1 : st[pos].idx; }

    int num(int pos) { return pos < 0 ? 0 : st[pos].num; }

    ll dfs(int u, int i, const string &s, int id) {
        if (u < 0) return 0;

        int k = s[i] - margin;
        int npos0 = next(u, 0), npos1 = next(u, 1);

        if (npos0 == -1 && npos1 == -1) {
            if (idx(u) != -1 && idx(u) < id) return num(u);
            return 0LL;
        }

        ll res = 0;
        if (~npos0) res += dfs(npos0, i+1, s, id);   
        
        if (k == 0) {
            if (~npos1) res += dfs(npos1, i+1, s, id);   
        }

        return res;
    }
};
#pragma endregion

void solve() {
    int n;
    cin >> n;

    vector<int> tmp(n);
    unordered_map<int, int> cnt;
    each(x, tmp) {
        cin >> x;
        cnt[x]++;
    }
    UNIQUE(tmp);
    n = tmp.size();

    vector<string> a(n);
    REP1(i, n) {
        a[i] = bitset<30>(tmp[i]).to_string();
    }

    Trie<2, '0'> trie;

    REP1(i, n) {
        trie.add(a[i], i, cnt[tmp[i]]);
    }

    ll ans = 0;
    REP1(i, n) ans += trie.dfs(0, 0, a[i], i) * cnt[tmp[i]];
    cout << ans << endl;
}

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

signed main() {
    setIO("IPN");

    int t = 1;
    while (t--) solve();
}
