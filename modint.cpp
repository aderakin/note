#define def_op(op, uop, body) \
    inline self_t& operator uop(const self_t& o) { body; return *this; } \
    friend inline self_t operator op (self_t lhs, const self_t & rhs) { return lhs uop rhs; }
#define def_cmp_op(op, body) friend inline bool operator op(const self_t& u, const self_t& v) { return body; }

const int MOD = 1e9 + 7;
struct ModInt {
    using self_t = ModInt;
    int x;
    ModInt(): x(0) {}
    ModInt(int v): x(v >= MOD ? v - MOD : v < 0 ? v + MOD : v) {}
    def_op(+, +=, {x += o.x; if (x >= MOD) x -= MOD;})
    def_op(-, -=, {x -= o.x; if (x < 0) x += MOD;}) 
    def_op(*, *= , {x = (int)(1ll * x * o.x % MOD); })
    def_op(/, /=, {x = o.pow(MOD - 2, x).x; })
    self_t pow(long long exp, self_t ans = 1) const {
        self_t base = *this;
        for (; exp > 0; exp >>= 1) {
            if (exp & 1) ans *= base;
            base *= base;
        }
        return ans;
    }
    def_cmp_op(==, u.x == v.x;)
    def_cmp_op(!=, u.x != v.x;) 
    def_cmp_op(<, u.x < v.x;) 
    friend ostream& operator<<(ostream& out, const self_t& u) { return out << u.x; }
};