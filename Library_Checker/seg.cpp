#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

const int inf = 1e9 + 10;

// 1-based
struct Segtree {
	typedef ll T;
	static constexpr T unit = inf;

	int sz;
	vector<T> st;
	
	Segtree(int ssz) : sz(ssz) {
		st.resize(ssz*4 + 1);
	}

	T f(T a, T b) { return min(a, b); }

	void update(int p, T x, int id, int lx, int rx) {
		if (p > rx || p < lx) return;
		if (lx == rx) {
			st[id] = x;
			return;
		}

		int mid = (lx + rx) / 2;
		update(p, x, id*2, lx, mid);
		update(p, x, id*2 + 1, mid+1, rx);

		st[id] = f(st[id*2], st[id*2 + 1]);
	}

	T get(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return unit;
		if (u <= lx && v >= rx) return st[id];

		int mid = (lx + rx) / 2;
		return f(get(u, v, id*2, lx, mid), get(u, v, id*2 + 1, mid+1, rx));
	}

	void update(int p, T x) { 
		update(p, x, 1, 1, sz); 
	}

	T get(int u, int v) {
		return get(u, v, 1, 1, sz); 
	}
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n+1);
    
    Segtree tree(n);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tree.update(i, a[i]);
    }

    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l++, r++;

        cout << tree.get(l, r-1) << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while (t--) solve();
}