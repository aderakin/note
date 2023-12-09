struct MergeSortTree {
	int _n;
	vector<vector<int>> st;
	
	MergeSortTree() {}
	MergeSortTree(int _n) : _n(_n), st(_n*4+1, vector<int>()) {}

	void init(int __n) {
		_n = __n;
		st.resize(_n*4+1);
	}

	void build(const vector<int> &x, int id, int lx, int rx) {
		if (lx == rx) {
			st[id].push_back(x[lx]);
			return;
		}

		int mid = (lx + rx) >> 1;
		build(x, id*2, lx, mid);
		build(x, id*2 + 1, mid+1, rx);

		merge(all(st[id*2]), all(st[id*2 + 1]), back_inserter(st[id]));
	}

	int query(int u, int v, int k, int id, int lx, int rx) {
		if (u > rx || v < lx) return 0;
		if (u <= lx && v >= rx) {
            int res = upper_bound(all(st[id]), k) - st[id].begin();
            return res;
        }

		int mid = (lx + rx) >> 1;
		return query(u, v, k, id*2, lx, mid) + query(u, v, k, id*2 + 1, mid+1, rx);
	}

    int query(int u, int v, int k) {
        return query(u, v, k, 1, 1, _n);
    }
};