// #pragma GCC optimize("O2,unroll-loops")
// #pragma GCC target("avx2")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
//#define int long long
using pii = pair<int, int>;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define UNIQUE(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());
#define each(x, a) for (auto &x : a)
#define REP(i, n)  for (int i = 1, _n = (n); i <= _n; i++)
#define REP1(i, n)  for (int i = 0, _n = (n); i < _n; i++)
#define FOR(i, a, b)  for (int i = (a), _b = (b); i <= _b; i++)
#define FOR1(i, a, b)  for (int i = (a), _b = (b); i < _b; i++)
#define FORD(i, b, a)  for (int i = (b), _a = (a); i >= _a; i--)

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }

#define endl '\n'
#define db(val) "[" #val " = " << (val) << "] "
#ifdef LOCAL_DEBUG  
#   define clog cerr 
#else
#   define clog if (0) cerr
#endif

void setIO(string name = ""){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    if (!name.empty()) {
        if (fopen((name + ".inp").c_str(), "r")) { 
            freopen((name + ".inp").c_str(), "r", stdin);
            freopen((name + ".out").c_str(), "w", stdout);
        }
    }

}

void solve() {
    cout << bitset<10>(6) << endl;
}

signed main() {
    int t = 1;
    while (t--) solve();
}