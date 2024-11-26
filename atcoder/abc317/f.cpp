#ifndef ONLINE_JUDGE
#define ONLINE_JUDGE
#endif
#ifndef NO_STD_INCLUDES
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <array>
#include <queue>
#include <iomanip>
#include <complex>
#include <stdint.h>
#include <type_traits>
#include <numeric>
using namespace std;
#endif
typedef long long LL;
typedef unsigned long long ULL;
#define REP(i,f,t) for (int i = (f); i < (t); i++)
inline void YesNo(bool flag) {
    if (flag) cout << "Yes" << endl;
    else  cout << "No" << endl;
}
template <typename T1, typename T2>
istream& operator >>(istream& in, pair<T1, T2>& vec) {
    return in >> vec.first >> vec.second;
}
template <typename T>
istream& operator >>(istream& in, vector<T>& vec) {
    for (auto& v : vec) {
        in >> v;
    }
    return in;
}
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& vec) {
    bool flag = false;
    for (auto& v : vec) {
        if (flag) {
            out << ' ';
        }
        else {
            flag = true;
        }
        out << v;
    }
    return out;
}
#ifndef ONLINE_JUDGE
void io_redirect() {
    freopen("in.txt", "rt", stdin);
}
#else
void io_redirect() {}
#endif
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr long long bases[3] = {2, 7, 61};
    for (long long a : bases) {
        long long t = d;
        long long y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;
    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b
        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}
struct static_modint_base {};
template <class T>
using is_static_modint = std::is_base_of<static_modint_base, T>;
template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;
template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
struct static_modint : public static_modint_base {
    using mint = static_modint;
public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }
    static_modint() : _v(0) {}
    template <class T, std::enable_if_t<is_integral<T>::value&&
        std::is_signed<T>::value>* = nullptr>
    static_modint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }
    template <class T, std::enable_if_t<is_integral<T>::value&&
        std::is_unsigned<T>::value>* = nullptr>
    static_modint(T v) {
        _v = (unsigned int)(v % umod());
    }
    unsigned int val() const { return _v; }
    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++* this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --* this;
        return result;
    }
    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        if (prime) {
            assert(_v);
            return pow(umod() - 2);
        }
        else {
            auto eg = inv_gcd(_v, m);
            assert(eg.first == 1);
            return eg.second;
        }
    }
    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }
private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
    static constexpr bool prime = is_prime<m>;
};
template <class mint, is_static_modint_t<mint>* = nullptr>
istream& operator >>(istream& in, mint& val) {
    int v;
    cin >> v;
    val = v;
    return in;
}
template <class mint, is_static_modint_t<mint>* = nullptr>
ostream& operator <<(ostream& out, mint v) {
    return out << v.val();
}
namespace std {
    namespace
    {
        template <class T>
        inline void hash_combine(std::size_t& seed, T const& v)
        {
            seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
        struct HashValueImpl
        {
            static void apply(size_t& seed, Tuple const& tuple)
            {
                HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
                hash_combine(seed, std::get<Index>(tuple));
            }
        };
        template <class Tuple>
        struct HashValueImpl<Tuple, 0>
        {
            static void apply(size_t& seed, Tuple const& tuple)
            {
                hash_combine(seed, std::get<0>(tuple));
            }
        };
    }
    template <typename ... TT>
    struct hash<std::tuple<TT...>>
    {
        size_t
            operator()(std::tuple<TT...> const& tt) const
        {
            size_t seed = 0;
            HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
            return seed;
        }
    };
}
struct wrap {};
template<class Sig, class F, template<class...>class Hash = std::hash>
struct memoizer;
template<class R, class...Args, class F, template<class...>class Hash>
struct memoizer<R(Args...), F, Hash> {
    using base_type = F;
private:
    F base;
    mutable std::unordered_map< std::tuple<std::decay_t<Args>...>, R > cache;
public:
    template<class... Ts>
    R operator()(Ts&&... ts) const
    {
        auto args = std::make_tuple(ts...);
        auto it = cache.find(args);
        if (it != cache.end())
            return it->second;
        auto&& retval = base(*this, std::forward<Ts>(ts)...);
        cache.emplace(std::move(args), retval);
        return decltype(retval)(retval);
    }
    template<class... Ts>
    R operator()(Ts&&... ts)
    {
        auto args = std::tie(ts...);
        auto it = cache.find(args);
        if (it != cache.end())
            return it->second;
        auto&& retval = base(*this, std::forward<Ts>(ts)...);
        cache.emplace(std::move(args), retval);
        return decltype(retval)(retval);
    }
    memoizer(memoizer const&) = default;
    memoizer(memoizer&&) = default;
    memoizer& operator=(memoizer const&) = default;
    memoizer& operator=(memoizer&&) = default;
    memoizer() = delete;
    template<typename L>
    memoizer(wrap, L&& f) :
        base(std::forward<L>(f))
    {}
};
template<typename Sig, typename F>
memoizer<Sig, std::decay_t<F>> memorize(F&& f) { return { wrap{}, std::forward<F>(f) }; }
using mint = static_modint<998244353>;
struct Solution {
    long long N;
    vector<int> A;
    Solution(): A(3){
        cin >> N >> A;
    }
    int nextf(int f, int i, int n) {
        if (!f) {
            return 0;
        }
        i--;
        if ((1LL << i) & N) {
            if (n == 0) {
                return 0;
            }
            return 1;
        }
        else {
            if (n == 0) {
                return 1;
            }
            return -1;
        }
    }
    int nextm(int m, int n, int mod) {
        return (m * 2 + n) % mod;
    }
    void work() {
        auto F = memorize<mint(int, int, int, int, int, int, int)>([&](auto& F, int i, int f0, int m0, int f1, int m1, int f2, int m2) {
            mint ret = 0;
        if (i == 0) {
            if (m0 == 0 && m1 == 0 && m2 == 0) {
                return mint(1);
            }
            return mint(0);
        }
        for (int n0 = 0; n0<2; n0++) {
            int nf0 = nextf(f0, i, n0), nm0 = nextm(m0, n0, A[0]);
            if (nf0 < 0) continue;
            for (int n1 = 0; n1 < 2; n1++) {
                int nf1 = nextf(f1, i, n1), nm1 = nextm(m1, n1, A[1]);
                if (nf1 < 0) continue;
                {
                    int n2 = n0 ^ n1;
                    int nf2 = nextf(f2, i, n2), nm2 = nextm(m2, n2, A[2]);
                    if (nf2 < 0) continue;
                    ret += F(i - 1, nf0, nm0, nf1, nm1, nf2, nm2);
                }
            }
        }
        return ret;
            });
        mint ret = F(63, 1, 0, 1, 0, 1, 0);
        ret -= (N / lcm(A[0], A[1])) + 1;
        ret -= (N / lcm(A[0], A[2])) + 1;
        ret -= (N / lcm(A[1], A[2])) + 1;
        ret += 2;
        cout << ret << endl;
    }
};
int main()
{
    ios_base::sync_with_stdio(0);
    io_redirect();
    cin.tie(0);
    Solution s;
    s.work();
}
