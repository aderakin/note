template<class T, class B>
T binpow(T &x, int k, T e, B f) {
    T res = e;
	while (k) {
		if (k & 1) res = f(res, x);
		x = f(x, x);
		k >>= 1;
	}

	return res;
}

template<class T> 
T binpow(T &x, int k) {
    T res = 1;
	while (k) {
		if (k & 1) res = res * x;
		x = x * x;
		k >>= 1;
	}

	return res;
}