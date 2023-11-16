#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
#define int long long

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

const int MAXN = 5e5 + 10;
const int BLOCK_SIZE = 750;

struct Query {
    int l, r, id;

    bool operator < (Query other) {
        if (l / BLOCK_SIZE == other.l / BLOCK_SIZE) return r < other.r;
        return l / BLOCK_SIZE < other.l / BLOCK_SIZE;
    }
};

struct DS {
    int sum;
    int snapsum;

    void init() {
        sum = snapsum = 0;
    }

    void insert(int x) {
        sum += x;
    }

    void snapshot() {
        snapsum = sum;
    }

    void rollback() {
        sum = snapsum;
        snapsum = 0;
    }
};

int n, Q;
int a[MAXN];

vector<Query> queries;
vector<int> mo_algo() {
    vector<int> ans(queries.size() + 1);

    DS ds;
    ds.init();
    ds.snapshot();
    sort(all(queries));

    for (auto &q : queries) {
        if (q.r - q.l <= BLOCK_SIZE) {
            FOR(i, q.l, q.r) {
                ds.insert(a[i]);
            }
        }

        ans[q.id] = ds.sum;
        ds.rollback();
    }

    int last_bucket = -1;
    int cur_r = 0, border = 0;
    for (auto &q : queries) {
        if (q.r - q.l + 1 <= BLOCK_SIZE) continue;
        int bucket = q.l / BLOCK_SIZE;

        if (bucket != last_bucket) {
            ds.init();
            border = (bucket + 1) * BLOCK_SIZE - 1; // right border of the bucket
            cur_r = q.r;

            FOR(i, border, cur_r) {
                ds.insert(a[i]);
            }
        }
        last_bucket = bucket;

        while (cur_r < q.r) {
            cur_r++;
            ds.insert(a[cur_r]);
        }
        ds.snapshot();

        FOR(i, q.l, border - 1) {
            ds.insert(a[i]);
        }

        ans[q.id] = ds.sum;
        ds.rollback();
    }

    return ans;
}

void solve() {
    cin >> n >> Q;
    REP(i, n) cin >> a[i];

    REP(id, Q) {
        int l, r; cin >> l >> r;
        queries.push_back({l+1, r, id});
    }

    auto ans = mo_algo();
    REP(i, Q) cout << ans[i] << endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}