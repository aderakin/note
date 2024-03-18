struct FenwickTree {
	int _n;
	vector<int> bit;

	FenwickTree(int _n) : _n(_n), bit(_n+1) {}

	void update(int i, int x) { for (; i <= _n; i += i&-i) bit[i] += x; }
	void update(int i, int j, int x) { update(i,x); update(j+1,-x); }
	int query(int i) { int sum = 0; for (; i; i -= i&-i) sum += bit[i]; return sum; }
	int query(int l, int r) { return query(r) - query(l-1); }
};
