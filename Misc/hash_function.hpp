#include <cassert>
#include <chrono>
using namespace std;

namespace internal {
unsigned long long non_deterministic_seed() {
    unsigned long long m =
        chrono::duration_cast<chrono::nanoseconds>(
            chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    m ^= 9845834732710364265uLL;
    m ^= m << 24, m ^= m >> 31, m ^= m << 35;
    return m;
}
unsigned long long deterministic_seed() { return 88172645463325252UL; }

// #define RANDOMIZED_SEED 
unsigned long long seed() {
#if !defined(RANDOMIZED_SEED)
    return deterministic_seed();
#else
    return non_deterministic_seed();
#endif
}

}  // namespace internal

#include <type_traits>

namespace internal {
template <typename T>
using is_broadly_integral =
    typename conditional_t<is_integral_v<T> || is_same_v<T, __int128_t> ||
                               is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_signed =
    typename conditional_t<is_signed_v<T> || is_same_v<T, __int128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_unsigned =
    typename conditional_t<is_unsigned_v<T> || is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

#define ENABLE_VALUE(x)   \
    template <typename T> \
    constexpr bool x##_v = x<T>::value;

ENABLE_VALUE(is_broadly_integral);
ENABLE_VALUE(is_broadly_signed);
ENABLE_VALUE(is_broadly_unsigned);
#undef ENABLE_VALUE

#define ENABLE_HAS_TYPE(var)                                     \
    template <class, class = void>                               \
    struct has_##var : false_type {};                            \
    template <class T>                                           \
    struct has_##var<T, void_t<typename T::var>> : true_type {}; \
    template <class T>                                           \
    constexpr auto has_##var##_v = has_##var<T>::value;

#define ENABLE_HAS_VAR(var)                                       \
    template <class, class = void>                                \
    struct has_##var : false_type {};                             \
    template <class T>                                            \
    struct has_##var<T, void_t<decltype(T::var)>> : true_type {}; \
    template <class T>                                            \
    constexpr auto has_##var##_v = has_##var<T>::value;

}  // namespace internal

namespace internal {
// 整数, 整数列を 64 bit unsigned int へ移す

using u64 = unsigned long long;
using u128 = __uint128_t;

ENABLE_HAS_TYPE(first_type);
ENABLE_HAS_TYPE(second_type);
ENABLE_HAS_TYPE(iterator);

template <typename T>
u64 hash_function(const T& x) {
    static u64 r = seed();
    constexpr u64 z1 = 11995408973635179863ULL;
    if constexpr (is_broadly_integral_v<T>) {
        // Integral
        return (u64(x) ^ r) * z1;
    } else if constexpr (has_first_type_v<T> && has_second_type_v<T>) {
        // pair
        constexpr u64 z2 = 10150724397891781847ULL;
        return hash_function(x.first) + hash_function(x.second) * z2;
    } else if constexpr (has_iterator_v<T>) {
        // Container
        constexpr u64 mod = (1LL << 61) - 1;
        constexpr u64 base = 950699498548472943ULL;
        u64 m = 0;
        for (auto& z : x) {
            u64 w;
            if constexpr (is_broadly_integral_v<T>) {
                w = u64(z) ^ r;
            } else {
                w = hash_function(z);
            }
            u128 y = u128(m) * base + (w & mod);
            m = (y & mod) + (y >> 61);
            if (m >= mod) m -= mod;
        }
        m ^= m << 24, m ^= m >> 31, m ^= m << 35;
        return m;
    } else {
        static_assert([]() { return false; }());
    }
}

template <typename Key>
struct HashObject {
    size_t operator()(const Key& x) const { return hash_function(x); }
};

}  // namespace internal
