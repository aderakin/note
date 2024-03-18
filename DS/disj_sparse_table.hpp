template <class S, S (*op)(S, S)> struct disj_sparse_table {
    int N, sz;
    std::vector<std::vector<S>> d;
    static int _msb(int x) noexcept { return x == 0 ? 0 : (__builtin_clz(x) ^ 31); }
    disj_sparse_table() = default;
    disj_sparse_table(const std::vector<S> &seq) : N(seq.size()) {
        sz = 1 << (_msb(N - 1) + 1);
        d.assign(_msb(sz) + 1, std::vector<S>(sz));
        std::copy(seq.begin(), seq.end(), d[0].begin());

        for (int h = 1, half = 2; half < N; ++h, half <<= 1) {
            for (int i = half; i < sz; i += half * 2) {
                d[h][i - 1] = d[0][i - 1];
                for (int j = i - 2; j >= i - half; --j) d[h][j] = op(d[0][j], d[h][j + 1]);
                d[h][i] = d[0][i];
                for (int j = i + 1; j < i + half; ++j) d[h][j] = op(d[h][j - 1], d[0][j]);
            }
        }
    }
    // [l, r), 0-indexed
    S prod(int l, int r) const {
        assert(l >= 0 and r <= N and l < r);
        if (l + 1 == r) return d[0][l];
        int h = _msb(l ^ (r - 1));
        return op(d[h][l], d[h][r - 1]);
    }
};
