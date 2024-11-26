#include <bits/stdc++.h>
namespace suisen {
    template <class T> bool chmin(T& x, const T& y) { return y >= x ? false : (x = y, true); }
    template <class T> bool chmax(T& x, const T& y) { return y <= x ? false : (x = y, true); }
    template <class T> constexpr int pow_m1(T n) { return -(n & 1) | 1; }
    template <class T> constexpr T fld(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0)); }
    template <class T> constexpr T cld(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0)); }
}
namespace suisen::macro {
#define IMPL_REPITER(cond) auto& begin() { return *this; } auto end() { return nullptr; } auto& operator*() { return _val; } auto& operator++() { return _val += _step, *this; } bool operator!=(std::nullptr_t) { return cond; }
    template <class Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int> == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rep_impl {
        Int _val; const Int _end, _step;
        rep_impl(Int n) : rep_impl(0, n) {}
        rep_impl(IntL l, Int r, IntStep step = 1) : _val(l), _end(r), _step(step) {}
        IMPL_REPITER((_val < _end))
    };
    template <class Int, class IntL = Int, class IntStep = Int, std::enable_if_t<(std::is_signed_v<Int> == std::is_signed_v<IntL>), std::nullptr_t> = nullptr> struct rrep_impl {
        Int _val; const Int _end, _step;
        rrep_impl(Int n) : rrep_impl(0, n) {}
        rrep_impl(IntL l, Int r) : _val(r - 1), _end(l), _step(-1) {}
        rrep_impl(IntL l, Int r, IntStep step) : _val(l + fld<Int>(r - l - 1, step) * step), _end(l), _step(-step) {}
        IMPL_REPITER((_val >= _end))
    };
    template <class Int, class IntStep = Int> struct repinf_impl {
        Int _val; const Int _step;
        repinf_impl(Int l, IntStep step = 1) : _val(l), _step(step) {}
        IMPL_REPITER((true))
    };
#undef IMPL_REPITER
}

#include <iostream>

#include <limits>
#include <type_traits>

namespace suisen {
    template <typename ...Constraints> using constraints_t = std::enable_if_t<std::conjunction_v<Constraints...>, std::nullptr_t>;

    template <typename T, typename = std::nullptr_t> struct bitnum { static constexpr int value = 0; };
    template <typename T> struct bitnum<T, constraints_t<std::is_integral<T>>> { static constexpr int value = std::numeric_limits<std::make_unsigned_t<T>>::digits; };
    template <typename T> static constexpr int bitnum_v = bitnum<T>::value;
    template <typename T, size_t n> struct is_nbit { static constexpr bool value = bitnum_v<T> == n; };
    template <typename T, size_t n> static constexpr bool is_nbit_v = is_nbit<T, n>::value;

    template <typename T, typename = std::nullptr_t> struct safely_multipliable { using type = T; };
    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>, is_nbit<T, 32>>> { using type = long long; };
    template <typename T> struct safely_multipliable<T, constraints_t<std::is_signed<T>, is_nbit<T, 64>>> { using type = __int128_t; };
    template <typename T> struct safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 32>>> { using type = unsigned long long; };
    template <typename T> struct safely_multipliable<T, constraints_t<std::is_unsigned<T>, is_nbit<T, 64>>> { using type = __uint128_t; };
    template <typename T> using safely_multipliable_t = typename safely_multipliable<T>::type;

    template <typename T, typename = void> struct rec_value_type { using type = T; };
    template <typename T> struct rec_value_type<T, std::void_t<typename T::value_type>> {
        using type = typename rec_value_type<typename T::value_type>::type;
    };
    template <typename T> using rec_value_type_t = typename rec_value_type<T>::type;

    template <typename T> class is_iterable {
        template <typename T_> static auto test(T_ e) -> decltype(e.begin(), e.end(), std::true_type{});
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T> static constexpr bool is_iterable_v = is_iterable<T>::value;
    template <typename T> class is_writable {
        template <typename T_> static auto test(T_ e) -> decltype(std::declval<std::ostream&>() << e, std::true_type{});
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T> static constexpr bool is_writable_v = is_writable<T>::value;
    template <typename T> class is_readable {
        template <typename T_> static auto test(T_ e) -> decltype(std::declval<std::istream&>() >> e, std::true_type{});
        static std::false_type test(...);
    public:
        static constexpr bool value = decltype(test(std::declval<T>()))::value;
    };
    template <typename T> static constexpr bool is_readable_v = is_readable<T>::value;
} // namespace suisen
namespace suisen::io {
    template <typename IStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::istream, std::remove_reference_t<IStream>>, std::negation<std::is_const<std::remove_reference_t<IStream>>>>, std::nullptr_t> = nullptr>
    struct InputStream {
    private:
        using istream_type = std::remove_reference_t<IStream>;
        IStream is;
        struct { InputStream* is; template <typename T> operator T() { T e; *is >> e; return e; } } _reader{ this };
    public:
        template <typename IStream_> InputStream(IStream_ &&is) : is(std::move(is)) {}
        template <typename IStream_> InputStream(IStream_ &is) : is(is) {}
        template <typename T> InputStream& operator>>(T& e) {
            if constexpr (suisen::is_readable_v<T>) is >> e; else _read(e);
            return *this;
        }
        auto read() { return _reader; }
        template <typename Head, typename... Tail>
        void read(Head& head, Tail &...tails) { ((*this >> head) >> ... >> tails); }
        istream_type& get_stream() { return is; }
    private:
        static __uint128_t _stou128(const std::string& s) {
            __uint128_t ret = 0;
            for (char c : s) if ('0' <= c and c <= '9') ret = 10 * ret + c - '0';
            return ret;
        }
        static __int128_t _stoi128(const std::string& s) { return (s[0] == '-' ? -1 : +1) * _stou128(s); }

        void _read(__uint128_t& v) { v = _stou128(std::string(_reader)); }
        void _read(__int128_t& v) { v = _stoi128(std::string(_reader)); }
        template <typename T, typename U>
        void _read(std::pair<T, U>& a) { *this >> a.first >> a.second; }
        template <size_t N = 0, typename ...Args>
        void _read(std::tuple<Args...>& a) { if constexpr (N < sizeof...(Args)) *this >> std::get<N>(a), _read<N + 1>(a); }
        template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void _read(Iterable& a) { for (auto& e : a) *this >> e; }
    };
    template <typename IStream>
    InputStream(IStream &&) -> InputStream<IStream>;
    template <typename IStream>
    InputStream(IStream &) -> InputStream<IStream&>;

    InputStream cin{ std::cin };

    auto read() { return cin.read(); }
    template <typename Head, typename... Tail>
    void read(Head& head, Tail &...tails) { cin.read(head, tails...); }
} // namespace suisen::io
namespace suisen { using io::read; } // namespace suisen

namespace suisen::io {
    template <typename OStream, std::enable_if_t<std::conjunction_v<std::is_base_of<std::ostream, std::remove_reference_t<OStream>>, std::negation<std::is_const<std::remove_reference_t<OStream>>>>, std::nullptr_t> = nullptr>
    struct OutputStream {
    private:
        using ostream_type = std::remove_reference_t<OStream>;
        OStream os;
    public:
        template <typename OStream_> OutputStream(OStream_ &&os) : os(std::move(os)) {}
        template <typename OStream_> OutputStream(OStream_ &os) : os(os) {}
        template <typename T> OutputStream& operator<<(const T& e) {
            if constexpr (suisen::is_writable_v<T>) os << e; else _print(e);
            return *this;
        }
        void print() { *this << '\n'; }
        template <typename Head, typename... Tail>
        void print(const Head& head, const Tail &...tails) { *this << head, ((*this << ' ' << tails), ...), *this << '\n'; }
        template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void print_all(const Iterable& v, std::string sep = " ", std::string end = "\n") {
            for (auto it = v.begin(); it != v.end();) if (*this << *it; ++it != v.end()) *this << sep;
            *this << end;
        }
        ostream_type& get_stream() { return os; }
    private:
        void _print(__uint128_t value) {
            char buffer[41], *d = std::end(buffer);
            do *--d = '0' + (value % 10), value /= 10; while (value);
            os.rdbuf()->sputn(d, std::end(buffer) - d);
        }
        void _print(__int128_t value) {
            if (value < 0) *this << '-';
            _print(__uint128_t(value < 0 ? -value : value));
        }
        template <typename T, typename U>
        void _print(const std::pair<T, U>& a) { *this << a.first << ' ' << a.second; }
        template <size_t N = 0, typename ...Args>
        void _print(const std::tuple<Args...>& a) {
            if constexpr (N < std::tuple_size_v<std::tuple<Args...>>) {
                if constexpr (N) *this << ' ';
                *this << std::get<N>(a), _print<N + 1>(a);
            }
        }
        template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
        void _print(const Iterable& a) { print_all(a, " ", ""); }
    };
    template <typename OStream_>
    OutputStream(OStream_ &&) -> OutputStream<OStream_>;
    template <typename OStream_>
    OutputStream(OStream_ &) -> OutputStream<OStream_&>;

    OutputStream cout{ std::cout }, cerr{ std::cerr };

    template <typename... Args>
    void print(const Args &... args) { cout.print(args...); }
    template <typename Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    void print_all(const Iterable& v, const std::string& sep = " ", const std::string& end = "\n") { cout.print_all(v, sep, end); }
} // namespace suisen::io
namespace suisen { using io::print, io::print_all; } // namespace suisen

namespace suisen {
    template <class T, class ToKey, class CompKey = std::less<>, std::enable_if_t<std::conjunction_v<std::is_invocable<ToKey, T>, std::is_invocable_r<bool, CompKey, std::invoke_result_t<ToKey, T>, std::invoke_result_t<ToKey, T>>>, std::nullptr_t> = nullptr>
    auto comparator(const ToKey& to_key, const CompKey& comp_key = std::less<>()) {
        return [=](const T& x, const T& y) { return comp_key(to_key(x), to_key(y)); };
    }
    template <class Compare, std::enable_if_t<std::is_invocable_r_v<bool, Compare, int, int>, std::nullptr_t> = nullptr>
    std::vector<int> sorted_indices(int n, const Compare& compare) {
        std::vector<int> p(n);
        return std::iota(p.begin(), p.end(), 0), std::sort(p.begin(), p.end(), compare), p;
    }
    template <class ToKey, std::enable_if_t<std::is_invocable_v<ToKey, int>, std::nullptr_t> = nullptr>
    std::vector<int> sorted_indices(int n, const ToKey& to_key) { return sorted_indices(n, comparator<int>(to_key)); }
    template <class T, class Comparator>
    auto priority_queue_with_comparator(const Comparator& comparator) { return std::priority_queue<T, std::vector<T>, Comparator>{ comparator }; }
    template <class Iterable, std::enable_if_t<suisen::is_iterable_v<Iterable>, std::nullptr_t> = nullptr>
    void sort_unique_erase(Iterable& a) { std::sort(a.begin(), a.end()), a.erase(std::unique(a.begin(), a.end()), a.end()); }

    template <size_t D> struct Dim : std::array<int, D> {
        template <typename ...Ints> Dim(const Ints& ...ns) : std::array<int, D>::array{ static_cast<int>(ns)... } {}
    };
    template <typename ...Ints> Dim(const Ints& ...) -> Dim<sizeof...(Ints)>;
    template <class T, size_t D, size_t I = 0>
    auto ndvec(const Dim<D> &ns, const T& value = {}) {
        if constexpr (I + 1 < D) {
            return std::vector(ns[I], ndvec<T, D, I + 1>(ns, value));
        } else {
            return std::vector<T>(ns[I], value);
        }
    }
}
namespace suisen {
    using int128 = __int128_t;
    using uint128 = __uint128_t;
    template <class T> using min_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;
    template <class T> using max_priority_queue = std::priority_queue<T, std::vector<T>, std::less<T>>;
}
namespace suisen { const std::string Yes = "Yes", No = "No", YES = "YES", NO = "NO"; }

#ifdef LOCAL
#  define debug(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    suisen::io::cerr << "[\033[32mDEBUG\033[m] " << s << ": " << h, ((suisen::io::cerr << ", " << t), ..., (suisen::io::cerr << "\n"));
}
#else
#  define debug(...) void(0)
#endif
#define FOR(e, v) for (auto &&e : v)
#define CFOR(e, v) for (const auto &e : v)
#define REP(i, ...) CFOR(i, suisen::macro::rep_impl(__VA_ARGS__))
#define RREP(i, ...) CFOR(i, suisen::macro::rrep_impl(__VA_ARGS__))
#define REPINF(i, ...) CFOR(i, suisen::macro::repinf_impl(__VA_ARGS__))
#define LOOP(n) for ([[maybe_unused]] const auto& _ : suisen::macro::rep_impl(n))
#define ALL(iterable) std::begin(iterable), std::end(iterable)

using namespace suisen;
using namespace std;
struct io_setup {
    io_setup(int precision = 20) {
        std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
        std::cout << std::fixed << std::setprecision(precision);
    }
} io_setup_ {};

constexpr int iinf = std::numeric_limits<int>::max() / 2;
constexpr long long linf = std::numeric_limits<long long>::max() / 2;

#include <algorithm>
#include <cassert>
#include <vector>

namespace suisen {
template <typename T>
class CoordinateCompressorBuilder {
    public:
        struct Compressor {
            public:
                static constexpr int absent = -1;

                // default constructor
                Compressor() : _xs(std::vector<T>{}) {}
                // Construct from strictly sorted vector
                Compressor(const std::vector<T> &xs) : _xs(xs) {
                    assert(is_strictly_sorted(xs));
                }

                // Return the number of distinct keys.
                int size() const {
                    return _xs.size();
                }
                // Check if the element is registered.
                bool has_key(const T &e) const {
                    return std::binary_search(_xs.begin(), _xs.end(), e);
                }
                // Compress the element. if not registered, returns `default_value`. (default: Compressor::absent)
                int comp(const T &e, int default_value = absent) const {
                    const int res = min_geq_index(e);
                    return res != size() and _xs[res] == e ? res : default_value;
                }
                // Restore the element from the index.
                T decomp(const int compressed_index) const {
                    return _xs[compressed_index];
                }
                // Compress the element. Equivalent to call `comp(e)`
                int operator[](const T &e) const {
                    return comp(e);
                }
                // Return the minimum registered value greater than `e`. if not exists, return `default_value`.
                T min_gt(const T &e, const T &default_value) const {
                    auto it = std::upper_bound(_xs.begin(), _xs.end(), e);
                    return it == _xs.end() ? default_value : *it;
                }
                // Return the minimum registered value greater than or equal to `e`. if not exists, return `default_value`.
                T min_geq(const T &e, const T &default_value) const {
                    auto it = std::lower_bound(_xs.begin(), _xs.end(), e);
                    return it == _xs.end() ? default_value : *it;
                }
                // Return the maximum registered value less than `e`. if not exists, return `default_value`
                T max_lt(const T &e, const T &default_value) const {
                    auto it = std::upper_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>());
                    return it == _xs.rend() ? default_value : *it;
                }
                // Return the maximum registered value less than or equal to `e`. if not exists, return `default_value`
                T max_leq(const T &e, const T &default_value) const {
                    auto it = std::lower_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>());
                    return it == _xs.rend() ? default_value : *it;
                }
                // Return the compressed index of the minimum registered value greater than `e`. if not exists, return `compressor.size()`.
                int min_gt_index(const T &e) const {
                    return std::upper_bound(_xs.begin(), _xs.end(), e) - _xs.begin();
                }
                // Return the compressed index of the minimum registered value greater than or equal to `e`. if not exists, return `compressor.size()`.
                int min_geq_index(const T &e) const {
                    return std::lower_bound(_xs.begin(), _xs.end(), e) - _xs.begin();
                }
                // Return the compressed index of the maximum registered value less than `e`. if not exists, return -1.
                int max_lt_index(const T &e) const {
                    return int(_xs.rend() - std::upper_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>())) - 1;
                }
                // Return the compressed index of the maximum registered value less than or equal to `e`. if not exists, return -1.
                int max_leq_index(const T &e) const {
                    return int(_xs.rend() - std::lower_bound(_xs.rbegin(), _xs.rend(), e, std::greater<T>())) - 1;
                }
            private:
                std::vector<T> _xs;
                static bool is_strictly_sorted(const std::vector<T> &v) {
                    return std::adjacent_find(v.begin(), v.end(), std::greater_equal<T>()) == v.end();
                }
        };
        CoordinateCompressorBuilder() : _xs(std::vector<T>{}) {}
        explicit CoordinateCompressorBuilder(const std::vector<T> &xs) : _xs(xs) {}
        explicit CoordinateCompressorBuilder(std::vector<T> &&xs) : _xs(std::move(xs)) {}
        template <typename Gen, constraints_t<std::is_invocable_r<T, Gen, int>> = nullptr>
        CoordinateCompressorBuilder(const int n, Gen generator) {
            reserve(n);
            for (int i = 0; i < n; ++i) push(generator(i));
        }
        // Attempt to preallocate enough memory for specified number of elements.
        void reserve(int n) {
            _xs.reserve(n);
        }
        // Add data.
        void push(const T &first) {
            _xs.push_back(first);
        }
        // Add data.
        void push(T &&first) {
            _xs.push_back(std::move(first));
        }
        // Add data in the range of [first, last). 
        template <typename Iterator>
        auto push(const Iterator &first, const Iterator &last) -> decltype(std::vector<T>{}.push_back(*first), void()) {
            for (auto it = first; it != last; ++it) _xs.push_back(*it);
        }
        // Add all data in the container. Equivalent to `push(iterable.begin(), iterable.end())`.
        template <typename Iterable>
        auto push(const Iterable &iterable) -> decltype(std::vector<T>{}.push_back(*iterable.begin()), void()) {
            push(iterable.begin(), iterable.end());
        }
        // Add data.
        template <typename ...Args>
        void emplace(Args &&...args) {
            _xs.emplace_back(std::forward<Args>(args)...);
        }
        // Build compressor.
        auto build() {
            std::sort(_xs.begin(), _xs.end()), _xs.erase(std::unique(_xs.begin(), _xs.end()), _xs.end());
            return Compressor {_xs};
        }
        // Build compressor from vector.
        static auto build(const std::vector<T> &xs) {
            return CoordinateCompressorBuilder(xs).build();
        }
        // Build compressor from vector.
        static auto build(std::vector<T> &&xs) {
            return CoordinateCompressorBuilder(std::move(xs)).build();
        }
        // Build compressor from generator.
        template <typename Gen, constraints_t<std::is_invocable_r<T, Gen, int>> = nullptr>
        static auto build(const int n, Gen generator) {
            return CoordinateCompressorBuilder<T>(n, generator).build();
        }
    private:
        std::vector<T> _xs;
};

} // namespace suisen

#include <atcoder/lazysegtree>

using S = int;
using F = int;

S op(S x, S y) {
    return max(x, y);
}
S e() {
    return -iinf;
}
S mapping(F f, S x) {
    return f + x;
}
F composition(F f, F g) {
    return f + g;
}
F id() {
    return 0;
}

void solve() {
    int n, d, w;
    read(n, d, w);
    vector<pair<int, int>> ps(n);

    CoordinateCompressorBuilder<int> xs, ys;
    map<int, vector<tuple<int, int, int>>> ev;
    REP(i, n) {
        int t, x;
        read(t, x);
        ev[x - w + 1].emplace_back(t - d + 1, t + 1, +1);
        ev[x + 1].emplace_back(t - d + 1, t + 1, -1);
        ys.push(t - d + 1);
        ys.push(t + 1);
        xs.push(x - w + 1);
        xs.push(x + 1);
    }
    auto cmp_x = xs.build();
    auto cmp_y = ys.build();

    int ans = 0;
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<int>(cmp_y.size(), 0));
    for (const auto &[x, evs] : ev) {
        for (auto [l, r, i] : evs) {
            seg.apply(cmp_y[l], cmp_y[r], i);
        }
        chmax(ans, seg.all_prod());
    }
    print(ans);
}

int main() {
    int test_case_num = 1;
    // read(test_case_num);
    LOOP(test_case_num) solve();
    return 0;
}
