#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll inverse(ll a, ll m) { 
    a %= m; if (a == 0) return 0; if (a < 0) a += m;
    ll u = 0, v = 1;
    while (a) { ll t = m / a;  m -= t * a; swap(a, m); u -= t * v; swap(u, v); }
    return u;
}
template <int m, bool is_prime = true>
struct static_mod {
    using mint = static_mod;
    static constexpr int mod() { return m; }
    static_mod() : _v(0) {}
    template <class T> static_mod(T v) {ll x = (ll)(v % (ll)(umod())); if (x < 0) x += umod(); _v = (unsigned int)(x);}
    static_mod(unsigned int v) { _v = (unsigned int)(v % umod());}
    unsigned int val() const { return _v; }
    mint& operator++() { _v++; if (_v == umod()) _v = 0; return *this;}
    mint& operator--() { if (_v == 0) _v = umod(); _v--; return *this;}
    mint operator++(int) { mint result = *this; ++*this; return result;}
    mint operator--(int) { mint result = *this; --*this; return result;}
    mint& operator+=(const mint& rhs) { _v += rhs._v; if (_v >= umod()) _v -= umod();return *this;}
    mint& operator-=(const mint& rhs) { _v -= rhs._v; if (_v >= umod()) _v += umod();return *this;}
    mint& operator*=(const mint& rhs) { unsigned long long z = _v; z *= rhs._v; _v = (unsigned int)(z % umod()); return *this;}
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(ll n) const {mint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x;n >>= 1;} return r;}
    mint inv() const { if(is_prime) {assert(_v);return pow(umod() - 2);} return inverse(_v, m);}
    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs;}
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs;}
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs;}
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v;}
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v;}
    friend ostream& operator << (ostream& out, const mint& n) { return out << n.val(); }
    friend istream& operator >> (istream& in, mint& n) { ll x; in >> x; n = mint(x); return in; }
private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
};
using mint = static_mod<998244353>; // 1000000007



#include <cassert>
#include <vector>

namespace suisen {
    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    struct CommutativeDualSegmentTree {
        CommutativeDualSegmentTree() {}
        CommutativeDualSegmentTree(std::vector<T>&& a) : n(a.size()), m(ceil_pow2(a.size())), data(std::move(a)), lazy(m, id()) {}
        CommutativeDualSegmentTree(const std::vector<T>& a) : CommutativeDualSegmentTree(std::vector<T>(a)) {}
        CommutativeDualSegmentTree(int n, const T& fill_value) : CommutativeDualSegmentTree(std::vector<T>(n, fill_value)) {}

        T operator[](int i) const {
            assert(0 <= i and i < n);
            T res = data[i];
            for (i = (i + m) >> 1; i; i >>= 1) res = mapping(lazy[i], res);
            return res;
        }
        T get(int i) const {
            return (*this)[i];
        }
        void apply(int l, int r, const F& f) {
            assert(0 <= l and r <= n);
            for (l += m, r += m; l < r; l >>= 1, r >>= 1) {
                if (l & 1) apply(l++, f);
                if (r & 1) apply(--r, f);
            }
        }
    protected:
        int n, m;
        std::vector<T> data;
        std::vector<F> lazy;

        void apply(int k, const F& f) {
            if (k < m) {
                lazy[k] = composition(f, lazy[k]);
            } else {
                data[k - m] = mapping(f, data[k - m]);
            }
        }
    private:
        static int ceil_pow2(int n) {
            int m = 1;
            while (m < n) m <<= 1;
            return m;
        }
    };
} // namespace suisen

namespace suisen {
    template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    struct DualSegmentTree : public CommutativeDualSegmentTree<T, F, mapping, composition, id> {
        using base_type = CommutativeDualSegmentTree<T, F, mapping, composition, id>;
        using base_type::base_type;
        void apply(int l, int r, const F& f) {
            push(l, r);
            base_type::apply(l, r, f);
        }
    private:
        void push(int k) {
            base_type::apply(2 * k, this->lazy[k]), base_type::apply(2 * k + 1, this->lazy[k]);
            this->lazy[k] = id();
        }
        void push(int l, int r) {
            static const int log = __builtin_ctz(this->m);
            l += this->m, r += this->m;
            for (int i = log; (l >> i) << i != l; --i) push(l >> i);
            for (int i = log; (r >> i) << i != r; --i) push(r >> i);
        }
    };

    // template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    // DualSegmentTree(int, T)->DualSegmentTree<T, F, mapping, composition, id>;

    // template <typename T, typename F, T(*mapping)(F, T), F(*composition)(F, F), F(*id)()>
    // DualSegmentTree(std::vector<T>)->DualSegmentTree<T, F, mapping, composition, id>;
} // namespace suisen

mint mapping(std::pair<mint, mint> f, mint x) {
    return f.first * x + f.second;
}
std::pair<mint, mint> composition(std::pair<mint, mint> f, std::pair<mint, mint> g) {
    return { f.first * g.first, f.first * g.second + f.second };
}
std::pair<mint, mint> id() {
    return { 1, 0 };
}
using Segtree = suisen::DualSegmentTree<mint, std::pair<mint, mint>, mapping, composition, id>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    std::vector<mint> a(n);
    for (auto &e : a) {
        int v;
        std::cin >> v;
        e = v;
    }

    Segtree seg(a);
    while (q --> 0) {
        int query_type;
        std::cin >> query_type;
        if (query_type == 0) {
            int l, r, b, c;
            std::cin >> l >> r >> b >> c;
            seg.apply(l, r, { b, c });
        } else {
            int x;
            std::cin >> x;
            std::cout << seg.get(x).val() << '\n';
        }
    }

    return 0;
}

