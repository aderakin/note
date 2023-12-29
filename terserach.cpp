template<class B> ld ternary_search(int lo, int hi, B f) {
	REP(_, 11) {
		int x1 = lo + (hi - lo) / 3;
		int x2 = hi - (hi - lo) / 3;

		if (f(x1) > f(x2)) hi = x2;
		else lo = x1;
	}

	ld res = f(lo);
	FOR(i, lo, hi) ckmax(res, f(i));

	return res;
}