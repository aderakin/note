const int SZ = 1e9 + 1e5 + 10;
template<
	class S,
	S (*op) (S, S),
	S (*e) ()
> struct DynamicSegTree {
	S val = e(); DynamicSegTree<S, op, e> *c[2];
	DynamicSegTree() { c[0] = c[1] = NULL; }

	void update(int p, S x, int lx = 0LL, int rx = SZ) { // add x
		if (p > rx || p < lx) return;
		if (lx == p && rx == p) { 
			// val = op(val, x);
			val = x; 
			return; 
		}

		int mid = (lx + rx) >> 1;
		if (p <= mid) {
			if (!c[0]) c[0] = new DynamicSegTree<S, op, e>();
			c[0]->update(p, x, lx, mid);
		} 
		else {
			if (!c[1]) c[1] = new DynamicSegTree<S, op, e>();
			c[1]->update(p, x, mid+1, rx);
		}

		val = e(); FOR(i,0,1) if (c[i]) val = op(val, c[i]->val);
	}
	S query(int u, int v, int lx = 0LL, int rx = SZ) { // query sum of segment
		if (v < lx || rx < u) return e();
		if (u <= lx && rx <= v) return val;

		int mid = (lx + rx) >> 1; S res = e();
		if (c[0]) res = op(res, c[0]->query(u, v, lx, mid));
		if (c[1]) res = op(res, c[1]->query(u, v, mid+1, rx));

		return res;
	}	
};

using S = int;
S op(S l, S r) { return l+r; }
S e() { return 0; }