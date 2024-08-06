// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

//#define int long long
#define endl '\n'

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

constexpr int inf = 1001001001;
constexpr long long infLL = 4004004004004004004LL;

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

#pragma region DS/segtree_beats
// [l, r)
struct AngelBeats {
    using i64 = long long;
    static constexpr i64 INF = numeric_limits<i64>::max() / 2.1;

    struct alignas(32) Node {
        i64 sum = 0, g1 = 0, l1 = 0;
        i64 g2 = -INF, gc = 1, l2 = INF, lc = 1, add = 0;
    };

    vector<Node> v;
    i64 n, log;

    AngelBeats() {}
    AngelBeats(int _n) : AngelBeats(vector<i64>(_n)) {}
    AngelBeats(const vector<i64>& vc) {
        n = 1, log = 0;
        while (n < (int)vc.size()) n <<= 1, log++;
        v.resize(2 * n);
        for (i64 i = 0; i < (int)vc.size(); ++i) {
            v[i + n].sum = v[i + n].g1 = v[i + n].l1 = vc[i];
        }
        for (i64 i = n - 1; i; --i) update(i);
    }

    void range_chmin(int l, int r, i64 x) { inner_apply<1>(l, r, x); }
    void range_chmax(int l, int r, i64 x) { inner_apply<2>(l, r, x); }
    void range_add(int l, int r, i64 x) { inner_apply<3>(l, r, x); }
    void range_update(int l, int r, i64 x) { inner_apply<4>(l, r, x); }
    i64 range_min(int l, int r) { return inner_fold<1>(l, r); }
    i64 range_max(int l, int r) { return inner_fold<2>(l, r); }
    i64 range_sum(int l, int r) { return inner_fold<3>(l, r); }

   private:
    void update(int k) {
        Node& p = v[k];
        Node& l = v[k * 2 + 0];
        Node& r = v[k * 2 + 1];

        p.sum = l.sum + r.sum;

        if (l.g1 == r.g1) {
            p.g1 = l.g1;
            p.g2 = max(l.g2, r.g2);
            p.gc = l.gc + r.gc;
        } else {
            bool f = l.g1 > r.g1;
            p.g1 = f ? l.g1 : r.g1;
            p.gc = f ? l.gc : r.gc;
            p.g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
        }

        if (l.l1 == r.l1) {
            p.l1 = l.l1;
            p.l2 = min(l.l2, r.l2);
            p.lc = l.lc + r.lc;
        } else {
            bool f = l.l1 < r.l1;
            p.l1 = f ? l.l1 : r.l1;
            p.lc = f ? l.lc : r.lc;
            p.l2 = min(f ? r.l1 : l.l1, f ? l.l2 : r.l2);
        }
    }

    void push_add(int k, i64 x) {
        Node& p = v[k];
        p.sum += x << (log + __builtin_clz(k) - 31);
        p.g1 += x;
        p.l1 += x;
        if (p.g2 != -INF) p.g2 += x;
        if (p.l2 != INF) p.l2 += x;
        p.add += x;
    }
    void push_min(int k, i64 x) {
        Node& p = v[k];
        p.sum += (x - p.g1) * p.gc;
        if (p.l1 == p.g1) p.l1 = x;
        if (p.l2 == p.g1) p.l2 = x;
        p.g1 = x;
    }
    void push_max(int k, i64 x) {
        Node& p = v[k];
        p.sum += (x - p.l1) * p.lc;
        if (p.g1 == p.l1) p.g1 = x;
        if (p.g2 == p.l1) p.g2 = x;
        p.l1 = x;
    }
    void push(int k) {
        Node& p = v[k];
        if (p.add != 0) {
            push_add(k * 2 + 0, p.add);
            push_add(k * 2 + 1, p.add);
            p.add = 0;
        }
        if (p.g1 < v[k * 2 + 0].g1) push_min(k * 2 + 0, p.g1);
        if (p.l1 > v[k * 2 + 0].l1) push_max(k * 2 + 0, p.l1);

        if (p.g1 < v[k * 2 + 1].g1) push_min(k * 2 + 1, p.g1);
        if (p.l1 > v[k * 2 + 1].l1) push_max(k * 2 + 1, p.l1);
    }

    void subtree_chmin(int k, i64 x) {
        if (v[k].g1 <= x) return;
        if (v[k].g2 < x) {
            push_min(k, x);
            return;
        }
        push(k);
        subtree_chmin(k * 2 + 0, x);
        subtree_chmin(k * 2 + 1, x);
        update(k);
    }

    void subtree_chmax(int k, i64 x) {
        if (x <= v[k].l1) return;
        if (x < v[k].l2) {
            push_max(k, x);
            return;
        }
        push(k);
        subtree_chmax(k * 2 + 0, x);
        subtree_chmax(k * 2 + 1, x);
        update(k);
    }

    template <int cmd>
    inline void _apply(int k, i64 x) {
        if constexpr (cmd == 1) subtree_chmin(k, x);
        if constexpr (cmd == 2) subtree_chmax(k, x);
        if constexpr (cmd == 3) push_add(k, x);
        if constexpr (cmd == 4) subtree_chmin(k, x), subtree_chmax(k, x);
    }

    template <int cmd>
    void inner_apply(int l, int r, i64 x) {
        if (l == r) return;
        l += n, r += n;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) _apply<cmd>(l++, x);
                if (r & 1) _apply<cmd>(--r, x);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <int cmd>
    inline i64 e() {
        if constexpr (cmd == 1) return INF;
        if constexpr (cmd == 2) return -INF;
        return 0;
    }

    template <int cmd>
    inline void op(i64& a, const Node& b) {
        if constexpr (cmd == 1) a = min(a, b.l1);
        if constexpr (cmd == 2) a = max(a, b.g1);
        if constexpr (cmd == 3) a += b.sum;
    }

    template <int cmd>
    i64 inner_fold(int l, int r) {
        if (l == r) return e<cmd>();
        l += n, r += n;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        i64 lx = e<cmd>(), rx = e<cmd>();
        while (l < r) {
            if (l & 1) op<cmd>(lx, v[l++]);
            if (r & 1) op<cmd>(rx, v[--r]);
            l >>= 1;
            r >>= 1;
        }
        if constexpr (cmd == 1) lx = min(lx, rx);
        if constexpr (cmd == 2) lx = max(lx, rx);
        if constexpr (cmd == 3) lx += rx;
        return lx;
    }
};
#pragma endregion

#pragma region DS/HLD
// Index from 0
// Best used with SegTree.h
//
// Usage:
// HLD hld(g, root);
// // build segment tree. Note that we must use hld.order[i]
// vector<T> nodes;
// for (int i = 0; i < n; i++)
//   nodes.push_back(initial_value[hld.order[i]])
// SegTree<S, op, e> st(nodes);
//
// // Update single vertex
// st.set(hld.in[u], new_value)
//
// // Update path
// hld.apply_path(from, to, is_edge, [&] (int l, int r) {
//   st.apply(l, r+1, F);
// });
//
// // Query path
// hld.prod_path_commutative<S, op, e> (from, to, is_edge, [&] (int l, int r) {
//   return st.prod(l, r+1);
// });
struct HLD {
    HLD(const vector<vector<int>>& _g, int root)
            : n(_g.size()), g(_g),
            parent(n), depth(n), sz(n),
            dfs_number(0), nxt(n), in(n), out(n), order(n)
    {
        assert(0 <= root && root < n);

        // init parent, depth, sz
        // also move most heavy child of u to g[u][0]
        depth[root] = 0;
        dfs_sz(root, -1);

        // init nxt, in, out
        nxt[root] = root;
        dfs_hld(root);
    }

    int lca(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        while (true) {
            if (in[u] > in[v]) swap(u, v); // in[u] <= in[v]
            if (nxt[u] == nxt[v]) return u;
            v = parent[nxt[v]];
        }
    }

    // return k-th parent
    // if no such parent -> return -1
    int kth_parent(int u, int k) const {
        assert(0 <= u && u < n);
        if (depth[u] < k) return -1;

        while (true) {
            int v = nxt[u];
            if (in[u] - k >= in[v]) return order[in[u] - k];
            k -= in[u] - in[v] + 1;
            u = parent[v];
        }
    }

    // return k-th vertex on path from u -> v (0 <= k)
    // if k > distance -> return -1
    int kth_vertex_on_path(int u, int v, int k) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);

        int l = lca(u, v);
        int ul = depth[u] - depth[l];
        if (k <= ul) return kth_parent(u, k);
        k -= ul;
        int vl = depth[v] - depth[l];
        if (k <= vl) return kth_parent(v, vl - k);
        return -1;
    }

    int dist(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        int l = lca(u, v);
        return depth[u] + depth[v] - 2*depth[l];
    }

    // apply f on vertices on path [u, v]
    // edge = true -> apply on edge
    //
    // f(l, r) should update segment tree [l, r] INCLUSIVE
    void apply_path(int u, int v, bool edge, const function<void(int, int)> &f) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (u == v && edge) return;

        while (true) {
            if (in[u] > in[v]) swap(u, v); // in[u] <= in[v]
            if (nxt[u] == nxt[v]) break;
            f(in[nxt[v]], in[v]);
            v = parent[nxt[v]];
        }
        if (u == v && edge) return;
        f(in[u] + edge, in[v]);
    }

    // get prod of path u -> v
    // edge = true -> get on edges
    //
    // f(l, r) should query segment tree [l, r] INCLUSIVE
    // f must be commutative. For non-commutative, use getSegments below
    template<class S, S (*op) (S, S), S (*e)()>
    S prod_path_commutative(
            int u, int v, bool edge,
            const function<S(int, int)>& f) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        if (u == v && edge) {
            return e();
        }
        S su = e(), sv = e();
        while (true) {
            if (in[u] > in[v]) { swap(u, v); swap(su, sv); }
            if (nxt[u] == nxt[v]) break;
            sv = op(sv, f(in[nxt[v]], in[v]));
            v = parent[nxt[v]];
        }
        if (u == v && edge) {
            return op(su, sv);
        } else {
            return op(su, op(sv, f(in[u] + edge, in[v])));
        }
    }

    // f(l, r) modify seg_tree [l, r] INCLUSIVE
    void apply_subtree(int u, bool edge, const function<void(int, int)>& f) {
        assert(0 <= u && u < n);
        f(in[u] + edge, out[u] - 1);
    }

    // f(l, r) queries seg_tree [l, r] INCLUSIVE
    template<class S>
    S prod_subtree_commutative(int u, bool edge, const function<S(S, S)>& f) {
        assert(0 <= u && u < n);
        return f(in[u] + edge, out[u] - 1);
    }

    // Useful when functions are non-commutative
    // Return all segments on path from u -> v
    // For this problem, the order (u -> v is different from v -> u)
    vector< pair<int,int> > getSegments(int u, int v) const {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        vector< pair<int,int> > upFromU, upFromV;

        int fu = nxt[u], fv = nxt[v];
        while (fu != fv) {  // u and v are on different chains
            if (depth[fu] >= depth[fv]) { // move u up
                upFromU.push_back({u, fu});
                u = parent[fu];
                fu = nxt[u];
            } else { // move v up
                upFromV.push_back({fv, v});
                v = parent[fv];
                fv = nxt[v];
            }
        }
        upFromU.push_back({u, v});
        reverse(upFromV.begin(), upFromV.end());
        upFromU.insert(upFromU.end(), upFromV.begin(), upFromV.end());
        return upFromU;
    }

    // return true if u is ancestor
    bool isAncestor(int u, int v) const {
        return in[u] <= in[v] && out[v] <= out[u];
    }

// private:
    int n;
    vector<vector<int>> g;
    vector<int> parent;   // par[u] = parent of u. par[root] = -1
    vector<int> depth;    // depth[u] = distance from root -> u
    vector<int> sz;       // sz[u] = size of subtree rooted at u
    int dfs_number;
    vector<int> nxt;      // nxt[u] = vertex on heavy path of u, nearest to root
    vector<int> in, out;  // subtree(u) is in range [in[u], out[u]-1]
    vector<int> order;    // euler tour

    void dfs_sz(int u, int fu) {
        parent[u] = fu;
        sz[u] = 1;
        // remove parent from adjacency list
        auto it = std::find(g[u].begin(), g[u].end(), fu);
        if (it != g[u].end()) g[u].erase(it);

        for (int& v : g[u]) {
            depth[v] = depth[u] + 1;
            dfs_sz(v, u);

            sz[u] += sz[v];
            if (sz[v] > sz[g[u][0]]) swap(v, g[u][0]);
        }
    }

    void dfs_hld(int u) {
        order[dfs_number] = u;
        in[u] = dfs_number++;

        for (int v : g[u]) {
            nxt[v] = (v == g[u][0] ? nxt[u] : v);
            dfs_hld(v);
        }
        out[u] = dfs_number;
    }
};
#pragma endregion

// https://oj.uz/problem/view/BOI18_minmaxtree
void solve() {

}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while (t--) solve();
}