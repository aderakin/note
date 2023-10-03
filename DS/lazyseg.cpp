#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define all(v) v.begin(), v.end

const int MAXN = 1e6 + 10;
const int inf = 1e9 + 10;

struct Node {
    int val;
    int lazy;

    friend bool operator < (const Node &x, const Node &y) {
        return x.val < y.val;
    }
};

struct LazySegtree {
	typedef Node T;
	static constexpr Node unit = {0, inf};

    int _n;
	vector<T> st;

	LazySegtree(int _n) : _n(_n), st(_n*4+1, unit) {}
    LazySegtree(int _n, vector<T> &a) : _n(_n) {
    st = vector<T> (_n*4+1, unit);
    build(a, 1, 1, _n);
}

	T f(T a, T b) { return min(a, b); } // (any associative fn)

    void build(vector<T> &a, int id, int lx, int rx) {
        if (lx == rx) {
            st[id] = a[lx];
            return;
        }

        int mid = (lx + rx) / 2;
        build(a, id*2, lx, mid);
        build(a, id*2+1, mid+1, rx);

        st[id] = f(st[id*2], st[id*2 + 1]);
    }

    void push(int id, int lx, int rx) {
        int t = st[id].lazy;
        if (t == -1) return;

        st[id*2].lazy = t; 
        st[id*2].val = t; 

        st[id*2 + 1].lazy = t;
        st[id*2 + 1].val = t;

        st[id].lazy = -1;
    }

	void update(int u, int v, T x, int id, int lx, int rx) {
		if (u > rx || v < lx) return;
		if (u <= lx && v >= rx) {
            st[id] = x;
			return;
		}
        push(id, lx, rx);

		int mid = (lx + rx) / 2;
		update(u, v, x, id*2, lx, mid);
		update(u, v, x, id*2 + 1, mid+1, rx);

        st[id] = f(st[id*2], st[id*2+1]);
	}

    void update(int u, int v, int x) { 
		update(u, v, Node{x, x}, 1, 1, _n); 
	}

	T query(int u, int v, int id, int lx, int rx) {
		if (u > rx || v < lx) return unit;
		if (u <= lx && v >= rx) return st[id];

        push(id, lx, rx);

		int mid = (lx + rx) / 2;
		return f(query(u, v, id*2, lx, mid), query(u, v, id*2 + 1, mid+1, rx));
	}

	int query(int u, int v) {
		return query(u, v, 1, 1, _n).val; 
	}

    void print() {
        int ind = 1;
        int row_size = 1;
        
        while (ind <= _n) {
            for (int i = 0; i < row_size; i++) {
                cerr << st[ind].lazy << "/" << st[ind++].val << '\t';
            }
            cerr << endl;
            row_size *= 2;
        }
        cerr << endl;
    }
};