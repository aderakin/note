template<
    class S, 
    S (*op) (S, S),
    S (*e) ()
> struct SegTree {
	int _n;
	vector<S> st;
	
	SegTree() {}
	SegTree(int _n) : _n(_n), st(_n*4+1, e()) {}

	void update(int p, S x, int id, int lx, int rx) {
		if (p > rx || p < lx) return;
		if (lx == rx) {
			st[id] = x;
			return;
		}

		int mid = (lx + rx) >> 1;
		update(p, x, id*2, lx, mid);
		update(p, x, id*2 + 1, mid+1, rx);

		st[id] = op(st[id*2], st[id*2 + 1]);
	}

	S query(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return e();
		if (u <= lx && v >= rx) return st[id];

		int mid = (lx + rx) >> 1;
		return op(query(u, v, id*2, lx, mid), query(u, v, id*2 + 1, mid+1, rx));
	}

	void update(int p, S x) { 
		update(p, x, 1, 0, _n); 
	}

	S query(int u, int v) {
		return query(u, v, 1, 0, _n); 
	}
};

using S = int;
S op(S l, S r) { return l + r; }
S e() { return 0; }
