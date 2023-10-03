#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(), v.end()

const int MAXN = 1e6 + 10;
const ll inf = 2e18 + 10;

// 1-based
struct SegTree {
	typedef ll T;
	static constexpr T unit = inf;

	int _n;
	vector<T> st;
	
	SegTree(int _n) : _n(_n), st(_n*4+1, unit) {}

	T op(T a, T b) { return min(a, b); }

	void update(int p, T x, int id, int lx, int rx) {
		if (p > rx || p < lx) return;
		if (lx == rx) {
			st[id] = x;
			return;
		}

		int mid = (lx + rx) / 2;
		update(p, x, id*2, lx, mid);
		update(p, x, id*2 + 1, mid+1, rx);

		st[id] = op(st[id*2], st[id*2 + 1]);
	}

	T query(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return unit;
		if (u <= lx && v >= rx) return st[id];

		int mid = (lx + rx) / 2;
		return op(query(u, v, id*2, lx, mid), query(u, v, id*2 + 1, mid+1, rx));
	}

	void update(int p, T x) { 
		update(p, x, 1, 1, _n); 
	}

	T query(int u, int v) {
		return query(u, v, 1, 1, _n); 
	}
};

int k;

SegTree tree(k);
int main () {
	cout << tree._n;
}