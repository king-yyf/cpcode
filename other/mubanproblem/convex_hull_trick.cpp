#include<bits/stdc++.h>
using namespace std;


template <typename T>
struct safely_multipliable {};
template <>
struct safely_multipliable<int> { using type = long long; };
template <>
struct safely_multipliable<long long> { using type = __int128_t; };
template <>
struct safely_multipliable<unsigned int> { using type = unsigned long long; };
template <>
struct safely_multipliable<unsigned long int> { using type = __uint128_t; };
template <>
struct safely_multipliable<unsigned long long> { using type = __uint128_t; };
template <>
struct safely_multipliable<float> { using type = float; };
template <>
struct safely_multipliable<double> { using type = double; };
template <>
struct safely_multipliable<long double> { using type = long double; };
template <typename T>
using safely_multipliable_t = typename safely_multipliable<T>::type;

namespace convex_hull_trick {
    template <typename T>
    struct Line {
        // f(x)=ax+b,m=max{x|f=argmin_{f' in S}{f'(x)}}
        mutable T a, b, m;
        Line(const T& a, const T& b, const T& m) : a(a), b(b), m(m) {}
        bool operator<(const Line<T>& rhs) const { return a < rhs.a; }
        bool operator<(const T& x) const { return not (m < x); }
    };

    template <typename T, std::enable_if_t<std::is_integral<T>::value, std::nullptr_t> = nullptr>
    inline T div(const T& num, const T& den) {
        return num / den - ((num ^ den) < 0 and num % den);
    }
    template <typename T, std::enable_if_t<std::negation<std::is_integral<T>>::value, std::nullptr_t> = nullptr>
    inline T div(const T& num, const T& den) {
        return num / den;
    }
}

template <typename T, bool is_min_query = true>
class ConvexHullTrick : std::multiset<convex_hull_trick::Line<T>, std::less<>> {
    using iterator = typename std::multiset<convex_hull_trick::Line<T>>::iterator;
    using MultT = safely_multipliable_t<T>;
    using Line = convex_hull_trick::Line<T>;

    static constexpr T inf = std::numeric_limits<T>::max();
public:
    void add_line(T slope, T intercept) {
        if constexpr (not is_min_query) slope = -slope, intercept = -intercept;
        auto it = this->emplace(slope, intercept, inf);
        auto itl = it;
        for (; itl != this->begin();) {
            if (update_intersec_right(--itl, it)) {
                ++itl;
                break;
            }
        }
        auto itm = this->erase(itl, it), itr = std::next(itm);
        if (not update_intersec_right(itm, itr)) {
            update_intersec_right(--itm, itr);
        }
        for (it = itm; itr != this->end();) {
            itm = itr++;
            if (itr != this->end() and itm->m <= itr->m) {
                update_intersec_right(it, itr);
            } else {
                break;
            }
        }
        if (it != itm) this->erase(std::next(it), itm);
    }

    MultT query(T x) {
        assert(not this->empty());
        const iterator l = --(this-> template lower_bound<T>(x));
        auto res = (MultT) l->a * x + l->b;
        if constexpr (is_min_query) {
            return res;
        } else {
            return -res;
        }
    }
private:
    // updates r->m and returns whether l is necessary or not.
    bool update_intersec_right(iterator l, iterator r) {
        if (r == this->end()) return true;
        if (l->a == r->a) {
            r->m = r->b <= l->b ? inf : -inf;
        } else {
            r->m = convex_hull_trick::div(r->b - l->b, l->a - r->a);
        }
        return l->m > r->m;
    }
};
template <typename T> using minCHT = ConvexHullTrick<T, true>;
template <typename T> using maxCHT = ConvexHullTrick<T, false>;


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    ConvexHullTrick<long long> cht;
    for (int i = 0; i < n; ++i) {
        long long a, b;
        std::cin >> a >> b;
        cht.add_line(a, b);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;
        if (t == 0) {
            long long a, b;
            std::cin >> a >> b;
            cht.add_line(a, b);
        } else {
            int x;
            std::cin >> x;
            std::cout << (long long) cht.query(x) << '\n';
        }
    }
    return 0;
}