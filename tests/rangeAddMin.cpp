#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

template<
    class S,                 // node data type
    S (*op) (S, S),          // combine 2 nodes
    S (*e) (),               // identity element
    class F,                 // lazy propagation tag
    S (*mapping) (F, S),     // apply tag F on a node
    F (*composition) (F, F), // combine 2 tags
    F (*lz_id) ()            // identity tag
>
struct LazySegtree {
	LazySegtree(int _n) : LazySegtree(vector<S> (_n+1, e())) {}
	LazySegtree(int _n, vector<S> &a) : _n(_n) {
        d = vector<S> (_n*4+1, e());
        lz = vector<F> (_n*4+1, lz_id());
        build(a, 1, 1, _n);
    }

    void build(vector<S> &a, int id, int lx, int rx) {
        if (lx == rx) {
            d[id] = a[lx];
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
		if (u <= lx && v >= rx) return d[id];
        push(id);

		int mid = (lx + rx) / 2;
		return op(query(u, v, id*2, lx, mid), query(u, v, id*2 + 1, mid+1, rx));
	}

	S query(int u, int v) {
		return query(u, v, 1, 1, _n); 
	}

    void print() {
        int ind = 1;
        int row_size = 1;
        
        while (ind <= _n) {
            for (int i = 0; i < row_size; i++) {
                cerr << d[ind].lazy << "/" << d[ind++].val << '\t';
            }
            cerr << endl;
            row_size *= 2;
        }
        cerr << endl;
    }

private:
    int _n;
    vector<S> d;
    vector<F> lz;

    void update(int k) {
        d[k] = op(d[2*k], d[2*k+1]);
    }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2*k, lz[k]);
        all_apply(2*k+1, lz[k]);
        lz[k] = lz_id();
    }
};

const int inf = 1e9 + 10;

struct S {
    int val;
};

struct F {
    int add;
};

S op(S l, S r) { return S {min(l.val, r.val)}; }

S e() { return S{inf}; };

S mapping(F f, S s) {
    return S {s.val + f.add};
}

// f(g(x))
F composition(F f, F g) { 
    return F {f.add + g.add};
}

F lz_id() { return F {0}; };

void solve() {
    int n, q; 
    cin >> n >> q;
    vector<S> a(n+1);
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        a[i] = S {x};
    }

    LazySegtree<S, op, e, F, mapping, composition, lz_id> tree(n, a);

    for (int i = 0; i < q; i++) {
        int tp; cin >> tp;
        if (tp == 1) {
            int u, v, x;
            cin >> u >> v >> x;
            tree.apply(u, v, F{x});
        }
        else {
            int u, v; 
            cin >> u >> v;
            auto val = tree.query(u, v);

            cout << val.val << endl;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}