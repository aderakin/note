// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

using ll = long long;
using ld = long double;
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

#define print_op(...) ostream& operator<<(ostream& out, const __VA_ARGS__& u)
#define db(val) "["#val" = "<<(val)<<"] "
#define CONCAT_(x, y) x##y
#define CONCAT(x, y) CONCAT_(x, y)
#ifdef LOCAL_DEBUG   
#   define clog cerr << setw(__db_level * 2) << setfill(' ') << "" << setw(0)
#   define DB() debug_block CONCAT(dbbl, __LINE__)
    int __db_level = 0;
    struct debug_block {
        debug_block() { clog << "{" << endl; ++__db_level; }
        ~debug_block() { --__db_level; clog << "}" << endl; }
    };
#else
#   define clog if (0) cerr
#   define DB(...)
#endif

template<class U, class V> print_op(pair<U, V>) {
    return out << "(" << u.first << ", " << u.second << ")";
}
template<class Con, class = decltype(begin(declval<Con>()))>
typename enable_if<!is_same<Con, string>::value, ostream&>::type
operator<<(ostream& out, const Con& con) { 
    out << "{";
    for (auto beg = con.begin(), it = beg; it != con.end(); ++it)
        out << (it == beg ? "" : ", ") << *it;
    return out << "}";
}
template<size_t i, class T> ostream& print_tuple_utils(ostream& out, const T& tup) {
    if constexpr(i == tuple_size<T>::value) 
        return out << ")"; 
    else 
        return print_tuple_utils<i + 1, T>(out << (i ? ", " : "(") << get<i>(tup), tup); 
}
template<class ...U> print_op(tuple<U...>) {
    return print_tuple_utils<0, tuple<U...>>(out, u);
}

template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return b > a ? a = b, 1 : 0; }


#undef int

namespace internal {

#ifndef _MSC_VER
template<class T> using is_signed_int128 = typename std::conditional<std::is_same<T, __int128_t>::value || std::is_same<T, __int128>::value, std::true_type, std::false_type>::type;
template<class T> using is_unsigned_int128 = typename std::conditional<std::is_same<T, __uint128_t>::value || std::is_same<T, unsigned __int128>::value, std::true_type, std::false_type>::type;
template<class T> using make_unsigned_int128 = typename std::conditional<std::is_same<T, __int128_t>::value, __uint128_t, unsigned __int128>;
template<class T> using is_integral = typename std::conditional<std::is_integral<T>::value || is_signed_int128<T>::value || is_unsigned_int128<T>::value, std::true_type, std::false_type>::type;
template<class T> using is_signed_int = typename std::conditional<(is_integral<T>::value && std::is_signed<T>::value) || is_signed_int128<T>::value, std::true_type, std::false_type>::type;
template<class T> using is_unsigned_int = typename std::conditional<(is_integral<T>::value && std::is_unsigned<T>::value) || is_unsigned_int128<T>::value, std::true_type, std::false_type>::type;
template<class T> using to_unsigned = typename std::conditional< is_signed_int128<T>::value, make_unsigned_int128<T>, typename std::conditional<std::is_signed<T>::value, std::make_unsigned<T>, std::common_type<T>>::type>::type;
#else
template<class T> using is_integral = typename std::is_integral<T>;
template<class T> using is_signed_int = typename std::conditional<is_integral<T>::value && std::is_signed<T>::value, std::true_type, std::false_type>::type;
template<class T> using is_unsigned_int = typename std::conditional<is_integral<T>::value && std::is_unsigned<T>::value, std::true_type, std::false_type>::type;
template<class T> using to_unsigned = typename std::conditional<is_signed_int<T>::value, std::make_unsigned<T>, std::common_type<T>>::type;
#endif

template<class T> using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;
template<class T> using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;
template<class T> using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

namespace internal {

template<class T>
constexpr T safe_mod(T x, T m) {
	x %= m;
	if(x < 0) {
		x += m;
	}
	return x;
}

} // namespace internal

namespace internal {

template<class T>
constexpr std::pair<T, T> inv_gcd(T a, T b) {
	a = safe_mod(a, b);
	if(a == 0) {
		return {b, 0};
	}
	T s = b, t = a;
	T m0 = 0, m1 = 1;
	while(t) {
		T u = s / t;
		s -= t * u;
		m0 -= m1 * u;
		auto tmp = s;
		s = t;
		t = tmp;
		tmp = m0;
		m0 = m1;
		m1 = tmp;
	}
	if(m0 < 0) {
		m0 += b / s;
	}
	return {s, m0};
}

} // namespace internal

template<int id>
struct modint {
public:
	static constexpr int mod() { return (id > 0 ? id : md); }
 	
	static constexpr void set_mod(int m) {
		if(id > 0 || md == m) {
			return;
		}
		md = m;
		fact.resize(1);
		inv_fact.resize(1);
		invs.resize(1);
	}

	static constexpr void prepare(int n) {
		int sz = (int) fact.size();
		if(sz == mod()) {
			return;
		}
		n = 1 << std::__lg(2 * n - 1);
		if(n < sz) {
			return;
		}
		if(n < (sz - 1) * 2) {
			n = std::min((sz - 1) * 2, mod() - 1);
		}
		fact.resize(n + 1);
		inv_fact.resize(n + 1);
		invs.resize(n + 1);
		for(int i = sz; i <= n; i++) {
			fact[i] = fact[i - 1] * i;
		}
		auto eg = internal::inv_gcd(fact.back().val(), mod());
		assert(eg.first == 1);
		inv_fact[n] = eg.second;
		for(int i = n - 1; i >= sz; i--) {
			inv_fact[i] = inv_fact[i + 1] * (i + 1);
		}
		for(int i = n; i >= sz; i--) {
			invs[i] = inv_fact[i] * fact[i - 1];
		}
	}
 
	constexpr modint() : value(0) {} 
	template<class T, internal::is_signed_int_t<T>* = nullptr> constexpr modint(T v) : value(v >= 0 ? v % mod() : v % mod() + mod()) {}
	template<class T, internal::is_unsigned_int_t<T>* = nullptr> constexpr modint(T v) : value(v % mod()) {}
 
	constexpr int val() const { return value; }

	constexpr modint inv() const {
		if(id > 0 && value < std::min(mod() >> 1, 1 << 18)) {
			prepare(value);
			return invs[value];
		} else {
			auto eg = internal::inv_gcd(value, mod());
			assert(eg.first == 1);
			return eg.second;
		}
	}
 
	constexpr modint& operator+=(const modint& rhs) & {
		value += rhs.value;
		if(value >= mod()) {
			value -= mod();
		}
		return *this;
	}
 
	constexpr modint& operator-=(const modint& rhs) & {
		value -= rhs.value;
		if(value < 0) {
			value += mod();
		}
		return *this;
	}

	constexpr modint& operator*=(const modint& rhs) & {
		value = 1LL * value * rhs.value % mod();
		return *this;
	}

	constexpr modint& operator/=(const modint& rhs) & {
		return *this *= rhs.inv();
	}

	friend constexpr modint operator+(modint lhs, modint rhs) { return lhs += rhs; }
	friend constexpr modint operator-(modint lhs, modint rhs) { return lhs -= rhs; }
	friend constexpr modint operator*(modint lhs, modint rhs) { return lhs *= rhs; }
	friend constexpr modint operator/(modint lhs, modint rhs) { return lhs /= rhs; }

	constexpr modint operator+() const { return *this; }
	constexpr modint operator-() const { return modint() - *this; } 
	constexpr bool operator==(const modint& rhs) const { return value == rhs.value; } 
	constexpr bool operator!=(const modint& rhs) const { return value != rhs.value; }

	constexpr modint pow(unsigned long long p) const {
		modint a(*this), res(1);
		while(p) {
			if(p & 1) {
				res *= a;
			}
			a *= a;
			p >>= 1;
		}
		return res;
	}

	constexpr bool has_sqrt() const {
		if(mod() == 2 || value == 0) {
			return true;
		}
		if(pow((mod() - 1) / 2).val() != 1) {
			return false;
		}
		return true;
	}

	constexpr modint sqrt() const {
		if(mod() == 2 || value < 2) {
			return *this;
		}
		assert(pow((mod() - 1) / 2).val() == 1);
		modint b = 1;
		while(b.pow((mod() - 1) >> 1).val() == 1) {
			b += 1;
		}
		int m = mod() - 1, e = __builtin_ctz(m);
		m >>= e;
		modint x = modint(*this).pow((m - 1) >> 1);
		modint y = modint(*this) * x * x;
		x *= value;
		modint z = b.pow(m);
		while(y.val() != 1) {
			int j = 0;
			modint t = y;
			while(t.val() != 1) {
				t *= t;
				j++;
			}
			z = z.pow(1LL << (e - j - 1));
			x *= z;
			z *= z;
			y *= z;
			e = j;
		}
		return x;
	}

	friend constexpr std::istream& operator>>(std::istream& in, modint& num) {
		long long x;
		in >> x;
		num = modint<id>(x);
		return in;
	}
	
	friend constexpr std::ostream& operator<<(std::ostream& out, const modint& num) {
		return out << num.val();
	}

public:
	static std::vector<modint> fact, inv_fact, invs;

	static modint nCr(int n, int r) {
		prepare(n + 1);
		if (r > n || r < 0 || n < 0) {
			return 0;
		}
		return fact[n] * inv_fact[n - r] * inv_fact[r];
	}

	static modint partition(int sum, int parts) {
        if (parts == 0) return sum == 0;
        return nCr(sum + parts - 1, sum);
    }

	static modint partition1(int sum, int parts) {
        if (parts == 0) return sum == 0;
        return nCr(sum - 1, parts - 1);
    }
	
private:
	int value;
	static int md;
};

template<int id> int modint<id>::md = 998244353;
template<int id> std::vector<modint<id>> modint<id>::fact = {1};
template<int id> std::vector<modint<id>> modint<id>::inv_fact = {1};
template<int id> std::vector<modint<id>> modint<id>::invs = {0};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

namespace internal {

template<class T> struct is_modint : public std::false_type {};
template<int id> struct is_modint<modint<id>> : public std::true_type {};

template<class T, class ENABLE = void> struct is_static_modint : public std::false_type {};
template<int id> struct is_static_modint<modint<id>, std::enable_if_t<(id > 0)>> : public std::true_type {};
template<class T> using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

template<class T, class ENABLE = void> struct is_dynamic_modint : public std::false_type {};
template<int id> struct is_dynamic_modint<modint<id>, std::enable_if_t<(id <= 0)>> : public std::true_type {};
template<class T> using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

} // namespace internal

namespace internal {

template<class T, class U>
constexpr T pow_mod_constexpr(T x, long long n, U m) {
	if(m == 1) {
		return 0;
	}
	x = safe_mod<T>(x, m);
	T r = 1;
	while(n) {
		if(n & 1) {
			r = (r * x) % m;
		}
		x = (x * x) % m;
		n >>= 1;
	}
	return r;
}

} // namespace internal

namespace internal {

constexpr int primitive_root_constexpr(int m) {
	if(m == 998244353) return 3;
	if(m == 167772161) return 3;
	if(m == 469762049) return 3;
	if(m == 754974721) return 11;
	if(m == 880803841) return 26;
	if(m == 1045430273) return 3;
	if(m == 1051721729) return 6;
	if(m == 1053818881) return 7;
	int divs[20] = {};
	divs[0] = 2;
	int cnt = 1;
	int x = (m - 1) / 2;
	x >>= __builtin_ctz(x);
	for(int i = 3; 1LL * i * i <= x; i += 2) {
		if(x % i == 0) {
			divs[cnt++] = i;
			while(x % i == 0) {
				x /= i;
			}
		}
	}
	if(x > 1) {
		divs[cnt++] = x;
	}
	for(int g = 2;; g++) {
		bool ok = true;
		for(int i = 0; i < cnt; i++) {
			if(pow_mod_constexpr<unsigned long long, int>(g, (m - 1) / divs[i], m) == 1) {
				ok = false;
				break;
			}
		}
		if(ok) {
			return g;
		}
	}
	assert(false);
}

} // namespace internal

namespace internal {

template<int mod>
struct NTT_prepare {
	using mint = modint<mod>;

	static constexpr int primitive_root = primitive_root_constexpr(mod);
	static constexpr int level = __builtin_ctz(mod - 1);

	std::array<mint, level + 1> root, iroot;
	std::array<mint, std::max(0, level - 2 + 1)> rate2, irate2;
	std::array<mint, std::max(0, level - 3 + 1)> rate3, irate3;

	constexpr NTT_prepare() {
		root[level] = mint(primitive_root).pow((mod - 1) >> level);
		iroot[level] = root[level].inv();
		for(int i = level - 1; i >= 0; i--) {
			root[i] = root[i + 1] * root[i + 1];
			iroot[i] = iroot[i + 1] * iroot[i + 1];
		}
		{
			mint prod = 1, iprod = 1;
			for(int i = 0; i <= level - 2; i++) {
				rate2[i] = root[i + 2] * prod;
				irate2[i] = iroot[i + 2] * iprod;
				prod *= iroot[i + 2];
				iprod *= root[i + 2];
			}
		}
		{
			mint prod = 1, iprod = 1;
			for(int i = 0; i <= level - 3; i++) {
				rate3[i] = root[i + 3] * prod;
				irate3[i] = iroot[i + 3] * iprod;
				prod *= iroot[i + 3];
				iprod *= root[i + 3];
			}
		}
	}
};

template<int mod>
struct NTT {
	using mint = modint<mod>;

	static NTT_prepare<mod> info;

	static void NTT4(std::vector<mint>& a) {
		int n = (int) a.size();
		int h = __builtin_ctz(n);
		int len = 0;
		while(len < h) {
			if(h - len == 1) {
				int p = 1 << (h - len - 1);
				mint rot = 1;
				for(int s = 0; s < (1 << len); s++) {
					int offset = s << (h - len);
					for(int i = 0; i < p; i++) {
						auto l = a[i + offset];
						auto r = a[i + offset + p] * rot;
						a[i + offset] = l + r;
						a[i + offset + p] = l - r;
					}
					if(s + 1 != (1 << len)) {
						rot *= info.rate2[__builtin_ctz(~(unsigned int) s)];
					}
				}
				len++;
			} else {
				int p = 1 << (h - len - 2);
				mint rot = 1, imag = info.root[2];
				for(int s = 0; s < (1 << len); s++) {
					mint rot2 = rot * rot;
					mint rot3 = rot2 * rot;
					int offset = s << (h - len);
					for(int i = 0; i < p; i++) {
						auto mod2 = 1ULL * mod * mod;
						auto a0 = 1ULL * a[i + offset].val();
						auto a1 = 1ULL * a[i + offset + p].val() * rot.val();
						auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();
						auto a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();
						auto a1na3imag = 1ULL * mint(a1 + mod2 - a3).val() * imag.val();
						auto na2 = mod2 - a2;
						a[i + offset] = a0 + a2 + a1 + a3;
						a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
						a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
						a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
					}
					if(s + 1 != (1 << len))
						rot *= info.rate3[__builtin_ctz(~(unsigned int) s)];
				}
				len += 2;
			}
		}
	}

	static void iNTT4(std::vector<mint>& a) {
		int n = (int) a.size();
		int h = __builtin_ctz(n);
		int len = h;
		while(len) {
			if(len == 1) {
				int p = 1 << (h - len);
				mint irot = 1;
				for(int s = 0; s < (1 << (len - 1)); s++) {
					int offset = s << (h - len + 1);
					for(int i = 0; i < p; i++) {
						auto l = a[i + offset];
						auto r = a[i + offset + p];
						a[i + offset] = l + r;
						a[i + offset + p] = 1ULL * (mod + l.val() - r.val()) * irot.val();
					}
					if(s + 1 != (1 << (len - 1))) {
						irot *= info.irate2[__builtin_ctz(~(unsigned int) s)];
					}
				}
				len--;
			} else {
				int p = 1 << (h - len);
				mint irot = 1, iimag = info.iroot[2];
				for(int s = 0; s < (1 << (len - 2)); s++) {
					mint irot2 = irot * irot;
					mint irot3 = irot2 * irot;
					int offset = s << (h - len + 2);
					for(int i = 0; i < p; i++) {
						auto a0 = 1ULL * a[i + offset + 0 * p].val();
						auto a1 = 1ULL * a[i + offset + 1 * p].val();
						auto a2 = 1ULL * a[i + offset + 2 * p].val();
						auto a3 = 1ULL * a[i + offset + 3 * p].val();
						auto a2na3iimag = 1ULL * mint((mod + a2 - a3) * iimag.val()).val();
						a[i + offset] = a0 + a1 + a2 + a3;
						a[i + offset + 1 * p] = (a0 + (mod - a1) + a2na3iimag) * irot.val();
						a[i + offset + 2 * p] = (a0 + a1 + (mod - a2) + (mod - a3)) * irot2.val();
						a[i + offset + 3 * p] = (a0 + (mod - a1) + (mod - a2na3iimag)) * irot3.val();
					}
					if(s + 1 != (1 << (len - 2))) {
						irot *= info.irate3[__builtin_ctz(~(unsigned int) s)];
					}
				}
				len -= 2;
			}
		}
	}
};

template<int mod> NTT_prepare<mod> NTT<mod>::info;

template<class T>
std::vector<T> convolution_naive(const std::vector<T>& a, const std::vector<T>& b) {
	int n = (int) a.size(), m = (int) b.size();
	std::vector<T> ans(n + m - 1);
	if(n >= m) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				ans[i + j] += a[i] * b[j];
			}
		}
	} else {
		for(int j = 0; j < m; j++) {
			for(int i = 0; i < n; i++) {
				ans[i + j] += a[i] * b[j];
			}
		}
	}
	return ans;
}

template<class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution_ntt(std::vector<mint> a, std::vector<mint> b) {
	int n = (int) a.size(), m = (int) b.size();
	int sz = 1 << std::__lg(2 * (n + m - 1) - 1);
	a.resize(sz);
	b.resize(sz);
	NTT<mint::mod()>::NTT4(a);
	NTT<mint::mod()>::NTT4(b);
	for(int i = 0; i < sz; i++) {
		a[i] *= b[i];
	}
	NTT<mint::mod()>::iNTT4(a);
	a.resize(n + m - 1);
	mint iz = mint(sz).inv();
	for(int i = 0; i < n + m - 1; i++) {
		a[i] *= iz;
	}
	return a;
}

} // namespace internal

template<class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution(const std::vector<mint>& a, const std::vector<mint>& b) {
	int n = (int) a.size(), m = (int) b.size();
	if(n == 0 || m == 0) {
		return {};
	}
	int sz = 1 << std::__lg(2 * (n + m - 1) - 1);
	assert((mint::mod() - 1) % sz == 0);
	if(std::min(n, m) < 128) {
		return internal::convolution_naive(a, b);
	}
	return internal::convolution_ntt(a, b);
}

template<int mod, class T, std::enable_if_t<internal::is_integral<T>::value>* = nullptr>
std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b) {
	using mint = modint<mod>;

	int n = (int) a.size(), m = (int) b.size();
	if(n == 0 || m == 0) {
		return {};
	}
	int sz = 1 << std::__lg(2 * (n + m - 1) - 1);
	assert((mod - 1) % sz == 0);
	std::vector<mint> a2(a.begin(), a.end());
	std::vector<mint> b2(b.begin(), b.end());
	auto c2 = convolution(std::move(a2), std::move(b2));
	std::vector<T> c(n + m - 1);
	for(int i = 0; i < n + m - 1; i++) {
		c[i] = c2[i].val();
	}
	return c;
}

template<class T>
std::vector<__uint128_t> convolution_u128(const std::vector<T>& a, const std::vector<T>& b) {
	static constexpr int m0 = 167772161; // 2^25
	static constexpr int m1 = 469762049; // 2^26
	static constexpr int m2 = 754974721; // 2^24
	static constexpr int r01 = internal::inv_gcd(m0, m1).second;
	static constexpr int r02 = internal::inv_gcd(m0, m2).second;
	static constexpr int r12 = internal::inv_gcd(m1, m2).second;
	static constexpr int r02r12 = 1LL * r02 * r12 % m2;
	static constexpr long long w1 = m0;
	static constexpr long long w2 = 1LL * m0 * m1;

	int n = (int) a.size(), m = (int) b.size();
	if(n == 0 || m == 0) {
		return {};
	}
	std::vector<__uint128_t> c(n + m - 1);
	if(std::min(n, m) < 128) {
		std::vector<__uint128_t> a2(a.begin(), a.end());
		std::vector<__uint128_t> b2(b.begin(), b.end());
		return internal::convolution_naive(std::move(a2), std::move(b2));
	}

	static constexpr int MAX_AB_BIT = 24;
    static_assert(m0 % (1ULL << MAX_AB_BIT) == 1, "m0 isn't enough to support an array length of 2^24.");
    static_assert(m1 % (1ULL << MAX_AB_BIT) == 1, "m1 isn't enough to support an array length of 2^24.");
    static_assert(m2 % (1ULL << MAX_AB_BIT) == 1, "m2 isn't enough to support an array length of 2^24.");
    assert(n + m - 1 <= (1 << MAX_AB_BIT));

	auto c0 = convolution<m0>(a, b);
	auto c1 = convolution<m1>(a, b);
	auto c2 = convolution<m2>(a, b);
	for(int i = 0; i < n + m - 1; i++) {
		long long n1 = c1[i], n2 = c2[i];
		long long x = c0[i];
		long long y = (n1 + m1 - x) * r01 % m1;
		long long z = ((n2 + m2 - x) * r02r12 + (m2 - y) * r12) % m2;
		c[i] = x + y * w1 + __uint128_t(z) * w2;
	}
	return c;
}

template<class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution_large(const std::vector<mint>& a, const std::vector<mint>& b) {
	static constexpr int max_size = (mint::mod() - 1) & -(mint::mod() - 1);
	static constexpr int half_size = max_size >> 1;
	static constexpr int inv_max_size = internal::inv_gcd(max_size, mint::mod()).second;

	const int n = (int) a.size(), m = (int) b.size();
	if(n == 0 || m == 0) {
		return {};
	}
	if(std::min(n, m) < 128 || n + m - 1 <= max_size) {
		return internal::convolution_naive(a, b);
	}
	const int dn = (n + half_size - 1) / half_size;
	const int dm = (m + half_size - 1) / half_size;
	std::vector<std::vector<mint>> as(dn), bs(dm);
	for(int i = 0; i < dn; ++i) {
		const int offset = half_size * i;
		as[i] = std::vector<mint>(a.begin() + offset, a.begin() + std::min(n, offset + half_size));
		as[i].resize(max_size);
		internal::NTT<mint::mod()>::NTT4(as[i]);
	}
	for(int j = 0; j < dm; ++j) {
		const int offset = half_size * j;
		bs[j] = std::vector<mint>(b.begin() + offset, b.begin() + std::min(m, offset + half_size));
		bs[j].resize(max_size);
		internal::NTT<mint::mod()>::NTT4(bs[j]);
	}
	std::vector<std::vector<mint>> cs(dn + dm - 1, std::vector<mint>(max_size));
	for(int i = 0; i < dn; ++i) {
		for(int j = 0; j < dm; ++j) {
			for(int k = 0; k < max_size; ++k) {
				cs[i + j][k] += as[i][k] * bs[j][k];
			}
		}
	}
	std::vector<mint> c(n + m - 1);
	for(int i = 0; i < dn + dm - 1; ++i) {
		internal::NTT<mint::mod()>::iNTT4(cs[i]);
		const int offset = half_size * i;
		const int jmax = std::min(n + m - 1 - offset, max_size);
		for(int j = 0; j < jmax; ++j) {
			c[offset + j] += cs[i][j] * inv_max_size;
		}
	}
	return c;
}

using mint = modint998244353;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<mint> a(n), b(m);
    each(x, a) cin >> x;
    each(x, b) cin >> x;

    auto c = convolution_large(a, b);
    each(x, c) cout << x << " ";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t = 1;
    while (t--) solve();
}