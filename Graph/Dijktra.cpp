#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
// #define int long long

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

const int MAXN = 1e5 + 10;

vector<pair<int, ll>> g[MAXN];
ll dist[MAXN];

void dijktra(int start) {
    memset(dist, 0x3f, sizeof dist);

    using T = pair<ll, int>; // <dist, node>
	priority_queue<T, vector<T>, greater<T>> pq;

	dist[start] = 0;
	pq.push({0LL, start});

	while (!pq.empty()) {
		const auto [d, u] = pq.top();
		pq.pop();
		if (d != dist[u]) { continue; }

		for (const auto &[v, w] : g[u]) {
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pq.push({dist[v], v});
			}
		}
	}
}