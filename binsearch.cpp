bool check(int x) {

}

int last_true() {
    int lo = 0, hi = 1e9;
    
    while (lo < hi) {
		int mid = lo + (hi - lo + 1) / 2;
		if (check(mid)) lo = mid;
        else hi = mid - 1;
	}

    return lo;
}

int first_true() {
    int lo = 1, hi = 1e9 + 1;
    
    while (lo < hi) {
		int mid = lo + (hi - lo) / 2;
		if (check(mid)) hi = mid;
        else lo = mid + 1;
	}

    return lo;
}