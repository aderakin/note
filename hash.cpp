#include <bits/stdc++.h>
using namespace std;
using ll = ll;
using ld = long double;
// #define int ll

#define all(v) v.begin(), v.end()
#define create_unique(vec) sort(all(vec)); vec.resize(unique(all(vec))-vec.begin());

struct HashedString {
	static const ll M = 1e9 + 9;
	static const ll B = 9973;

	static vector<ll> pows;
	vector<ll> p_hash;

	HashedString(const string &s) : p_hash(s.size() + 1) {
		while (pows.size() < s.size()) { pows.push_back((pows.back() * B) % M); }

		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

	// [l, r]
	ll get_hash(int l, int r) {
		ll raw_val = (p_hash[r] - (p_hash[l-1] * pows[r - l + 1]));
		return (raw_val % M + M) % M;
	}

};
vector<ll> HashedString::pows = {1};

