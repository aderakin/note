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

template<
    class S,                 // node data type
    S (*op) (S, S),          // combine 2 nodes
    S (*e) (),               // identity element
    class F,                 // lazy propagation tag
    S (*mapping) (F, S),     // apply tag F on a node
    F (*composition) (F, F), // combine 2 tags
    F (*lz_e) ()             // identity tag
>
struct LazySegTree {
	LazySegTree(int _n, vector<S> &a) : _n(_n) {
        st = vector<S> (_n*4+1, e());
        lz = vector<F> (_n*4+1, lz_e());
        if (a.size()) build(a, 1, 1, _n);
    }

    void build(vector<S> &a, int id, int lx, int rx) {
        if (lx == rx) {
            st[id] = a[lx];
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, id*2, lx, mid);
        build(a, id*2+1, mid+1, rx);

        update(id);
    }

	void apply(int u, int v, F f, int id, int lx, int rx) {
		if (u > rx || v < lx) return;
		if (u <= lx && v >= rx) {
            all_apply(id, f);
			return;
		}
        push(id);

		int mid = (lx + rx) / 2;
		apply(u, v, f, id*2, lx, mid);
		apply(u, v, f, id*2 + 1, mid+1, rx);

        update(id);
	}

    void apply(int u, int v, F f) { 
		apply(u, v, f, 1, 1, _n); 
	}

	S query(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return e();
		if (u <= lx && v >= rx) return st[id];
        push(id);

		int mid = (lx + rx) / 2;
		return op(query(u, v, id*2, lx, mid), query(u, v, id*2 + 1, mid+1, rx));
	}

	S query(int u, int v) {
		return query(u, v, 1, 1, _n); 
	}

private:
    int _n;
    vector<S> st;
    vector<F> lz;

    void update(int id) {
        st[id] = op(st[2*id], st[2*id+1]);
    }
    void all_apply(int id, F f) {
        st[id] = mapping(f, st[id]);
        lz[id] = composition(f, lz[id]);
    }
    void push(int id) {
        all_apply(2*id, lz[id]);
        all_apply(2*id+1, lz[id]);
        lz[id] = lz_e();
    }
};

// S op(S l, S r) { return S{}; }

// S e() { return S{0}; }

// S mapping(F f, S s) { return S{}; }

// F composition(F f, F g) { return F{}; }

// F lz_e() { return F{}; }

// LazySegTree<S, op, e, F, mapping, composition, lz_e> tree

struct RangeSetAddMinSumOps {
    struct S { long long sum, min, sz; };
    static S op(S l, S r) { return S { l.sum + r.sum, min(l.min, r.min), l.sz + r.sz }; }
    static S e() { return S {0LL, INT_MAX, 0}; }

    static const long long NOT_SET = -1000111000;
    struct F { long long set, add; };

    static S mapping(F f, S s) {
        if (f.set == NOT_SET) {
            return S {
                s.sum + f.add * s.sz,
                s.min + f.add,
                s.sz,
            };
        }
        return S {
            (f.set + f.add) * s.sz,
            f.set + f.add,
            s.sz,
        };
    }
    static F composition(F f, F g) {
        if (f.set == NOT_SET) {
            return F { g.set, g.add + f.add };
        }
        return f;
    }
    static F id() {
        return F { NOT_SET, 0 };
    }
};

// addmul
const int MOD = 998244353;

ll add(ll x, ll y) {
    return (x + y) % MOD;
}

ll mul(ll x, ll y) {
    return (x % MOD * (y % MOD)) % MOD;
}

struct S {
    ll a;
    int size;
};

struct F {
    ll b, c;
};

S op(S l, S r) { return S{add(l.a, r.a), l.size + r.size}; }

S e() { return S{0, 0}; }

S mapping(F f, S s) { return S{add( mul(s.a, f.b), mul(s.size, f.c) ), s.size}; }

F composition(F f, F g) { return F{mul(g.b, f.b), (mul(g.c, f.b) % MOD + f.c) % MOD}; }

F lz_e() { return F{1, 0}; }

void solve() {
    int q;
    int n; cin >> n;
    cin >> q;
    vector<S> a(n+1);
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        a[i+1] = S{x, 1};
    }

    LazySegTree<S, op, e, F, mapping, composition, lz_e> seg(n, a);

    for (int i = 0; i < q; i++) {
        char tp; cin >> tp;

        if (tp == '0') {
            int l, r, b, c; cin >> l >> r >> b >> c;
            l++;
            r++;
            seg.apply(l, r-1, F{b, c});
        }

        if (tp == '1') {
            int l, r;
            cin >> l >> r;
            l++; r++;

            cout << seg.query(l, r-1).a << "\n";
        }
    }
}

signed main() {
    setIO("");
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
