#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define int long long
using pii = pair<int, int>;
 
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());
#define REP(i, n)  for (int i = 1, _n = (n); i <= _n; i++)
#define REPD(i, n)  for (int i = (n); i >= 1; i--)
#define FOR(i, a, b)  for (int i = (a), _b = (b); i <= _b; i++)
#define FORD(i, b, a)  for (int i = (b), _a = (a); i >= _a; i--)
 
#define endl '\n'
#define db(val) "[" #val " = " << (val) << "] "
#ifdef LOCAL_DEBUG  
#   define clog cerr 
#else
#   define clog if (0) cerr
#endif
 
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }
 
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
 
void solve() {
    int n, Q;
    cin >> n >> Q;
 
    REP(i, n) {
        int x; cin >> x;
        tree.update(i, i, x);
    }
 
    REP(_, Q) {
        int tp;
        cin >> tp;
        if (tp == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            tree.update(l, r, x);
        }
        else {
            int x; cin >> x;
            cout << tree.query(x, x) << endl;
        }
    }
}
 
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}