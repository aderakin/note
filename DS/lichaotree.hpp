// Lichao tree
// Usage: lt.add_line({a, b})
//		  lt.query(x)

using point = complex<ll>;
ll f(point L, ll x) {return L.real() * x + L.imag();}

const ll inf = 2e18 + 10;

const int SZ = 1e9 + 10;
struct LichaoTree {
	struct Node {
		point line;
		Node *l, *r;

		Node() : line(point(0LL, inf)), l(NULL), r(NULL) {}
	};

	Node *root = new Node();

	void expand(Node *me) {
		if(!me->l) me->l = new Node();
		if(!me->r) me->r = new Node();
	}

	void add_line(Node *me, int lx, int rx, point nw) {
		int mid = (lx + rx) >> 1;
		bool c1 = f(nw, lx) < f(me->line, lx);
		bool c2 = f(nw, mid) < f(me->line, mid);
		if(c2) swap(me->line, nw);
		if(lx == rx) return;

		expand(me);
		if(c1 != c2) add_line(me->l, lx, mid, nw);
		else add_line(me->r, mid+1, rx, nw);
	}

	ll query(Node *me, int lx, int rx, int x) {
		int mid = (lx + rx) >> 1;
		if(lx == rx) return f(me->line, x);

		expand(me);
		if(x < mid) return min(f(me->line, x), query(me->l, lx, mid, x));
		else return min(f(me->line, x), query(me->r, mid+1, rx, x));
	}

	void add_line(point nw) { add_line(root, 0, SZ, nw); }
	ll query(int x) { return query(root, 0, SZ, x); } 
} lt;
