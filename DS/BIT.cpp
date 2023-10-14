#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }

struct BIT {
	int _n;
	vector<int> ft;

	BIT(int _n) : _n(_n), ft(_n+1) {}

	void u(int i, int x) { for (; i <= _n; i += i&-i) ft[i] += x; }
	int query(int i) { int sum = 0; for (; i; i -= i&-i) sum += ft[i]; return sum; }
	void update(int i, int j, int x) { u(i,x); u(j+1,-x); }
};