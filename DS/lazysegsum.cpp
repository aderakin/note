#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 10;
int n;
int a[MAXN];

struct Node {
    int lazy;
    int val;
} st[4*MAXN];

void print() {
    int ind = 1;
    int row_size = 1;
    
    while (ind <= n) {
        for (int i = 0; i < row_size; i++) {
            cerr << st[ind].lazy << " x " << st[ind++].val << '\t';
        }
        cerr << endl;
        row_size *= 2;
    }
    cerr << endl;
}

void build(int id = 1, int lx = 1, int rx = n) {
    if (lx == rx) {
        st[id].val = a[lx];
        st[id].lazy = 0;
        return;
    } 

    int mid = (lx + rx) / 2;

    build(id*2, lx, mid);
    build(id*2+1, mid+1, rx);

    st[id].val = st[id*2].val + st[id*2+1].val; 
    st[id].lazy = 0;
}

void push(int id, int lx, int rx) {
    int t = st[id].lazy;
    if (t == 0) return;

    int mid = (lx + rx) / 2;

    st[id*2].lazy += t;
    st[id*2].val += (mid-lx+1) * t;

    st[id*2+1].lazy += t;
    st[id*2+1].val += (rx-mid) * t;

    st[id].lazy = 0;
}

void update(int u, int v, int x, int id = 1, int lx = 1, int rx = n) {
    if (u > rx || v < lx) return;
    if (u <= lx && v >= rx) {
        st[id].val += (rx-lx+1) * x;
        st[id].lazy += x;
        return;
    }
    push(id, lx, rx);

    int mid = (lx + rx) / 2;
    update(u, v, x, id*2, lx, mid);
    update(u, v, x, id*2+1, mid+1, rx);

    st[id].val = st[id*2].val + st[id*2+1].val; 
}

int query(int u, int v, int id = 1, int lx = 1, int rx = n) {
    if (u > rx || v < lx) return 0;
    if (u <= lx && v >= rx) {
        return st[id].val;
    }

    push(id, lx, rx);
    // cerr << "here: " << u << " " << v << " " << lx << " " << rx << endl;
    // print();
    int mid = (lx + rx) / 2;

    return query(u, v, id*2, lx, mid) + query(u, v, id*2+1, mid+1, rx);
}


int main() {
    int q;
    cin >> n;
    cin >> q;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build();

    for (int i = 0; i < q; i++) {
        int tp;
        cin >> tp;

        if (tp == 1) {
            int u, v, x; 
            cin >> u >> v >> x;
            update(u, v, x);
        }
        else {
            int u, v; cin >> u >> v;
            cout << query(u, v) << endl;
        }
        print();
    }

}