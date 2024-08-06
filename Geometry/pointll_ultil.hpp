vector<PointInt> convexHull(vector<PointInt> pts) {
	if (pts.size() <= 1) return pts;
	sort(all(pts));
	vector<PointInt> h(pts.size()+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		for (P p : pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

bool inHull(const vector<PointInt>& l, PointInt p, bool strict = true) {
	int a = 1, b = sz(l) - 1, r = !strict;
	if (sz(l) < 3) return r && onSegment(l[0], l.back(), p);
	if (sideOf(l[0], l[a], l[b]) > 0) swap(a, b);
	if (sideOf(l[0], l[a], p) >= r || sideOf(l[0], l[b], p)<= -r)
		return false;
	while (abs(a - b) > 1) {
		int c = (a + b) >> 1;
		(sideOf(l[0], l[c], p) > 0 ? b : a) = c;
	}   
	return sgn(l[a].cross(l[b], p)) < r;
}

pair<PointInt, PointInt> closest(vector<PointInt> v) {
	assert(sz(v) > 1);
	set<PointInt> S;
	sort(all(v), [](PointInt a, PointInt b) { return a.y < b.y; });
	pair<ll, pair<PointInt, PointInt>> ret{LLONG_MAX, {PointInt(), PointInt()}};
	int j = 0;
	for (PointInt p : v) {
		PointInt d{1 + (ll)sqrt(ret.first), 0};
		while (v[j].y <= p.y - d.x) S.erase(v[j++]);
		auto lo = S.lower_bound(p - d), hi = S.upper_bound(p + d);
		for (; lo != hi; ++lo)
			ret = min(ret, {(*lo - p).dist2(), {*lo, p}});
		S.insert(p);
	}
	return ret.second;
}
