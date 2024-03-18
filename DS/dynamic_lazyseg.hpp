const int SZ = 1e9 + 10;
struct DynamicLazySegTree {
    using S = int;
    using F = int;
 
    S op(S l, S r) { return S{max(l, r)}; }
 
    static S e() { return S{0}; }
 
    S mapping(F f, S s) { return S{f+s}; }
 
    F composition(F f, F g) { return F{f+g}; }
 
    static F lz_e() { return F{0}; }
 
	struct Node {
        S val;
        F lz;
		Node *l, *r;
 
		Node() : l(NULL), r(NULL) {
            val = e();
            lz = lz_e();
        }
	};
 
	Node *root = new Node();
 
	void expand(Node *me) {
		if(!me->l) me->l = new Node();
		if(!me->r) me->r = new Node();
	}
 
    void all_apply(Node *me, F f) {
        me->val = mapping(f, me->val);
        me->lz = composition(f, me->lz);
    }
 
    void push(Node *me) {
        all_apply(me->l, me->lz);
        all_apply(me->r, me->lz);
        me->lz = lz_e();
    }
 
    void update(Node *me, int u, int v, F f, int lx, int rx) {
        if (u > rx || v < lx) return;
        if (u <= lx && v >= rx) {
            all_apply(me, f);
            return;
        }
 
        expand(me);
        push(me);
 
		int mid = (lx + rx) >> 1; 
        update(me->l, u, v, f, lx, mid);
        update(me->r, u, v, f, mid+1, rx);
 
        me->val = e();
        me->val = op(me->val, me->l->val);
        me->val = op(me->val, me->r->val);
    }
 
    S query(Node *me, int u, int v, int lx, int rx) { 
        if (u > rx || v < lx) return e();
		if (u <= lx && v >= rx) return me->val;
 
        expand(me); 
        push(me);
 
        S res = e();
		int mid = (lx + rx) >> 1; 
        res = op(res, query(me->l, u, v, lx, mid));
        res = op(res, query(me->r, u, v, mid+1, rx));
 
        return res;
	}	
 
    void update(int u, int v, F f) {
        update(root, u, v, f, 0, SZ);
    }
 
    S query(int u, int v) {
        return query(root, u, v, 0, SZ);
    }
} tree;
