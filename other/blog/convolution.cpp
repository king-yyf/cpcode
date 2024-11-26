#include<bits/stdc++.h>
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

template <typename T>
void zeta(vector<T> &f) {
    const int n = f.size();
    vector<char> is_prime(n, true);
    auto cum = [&](const int p) {
        const int qmax = (n - 1) / p, rmax = qmax * p;
        for (int q = qmax, pq = rmax; q >= 1; --q, pq -= p) {
            f[q] = f[q] + f[pq];
            is_prime[pq] = false;
        }
    };
    for (int p = 2; p < n; ++p) if (is_prime[p]) cum(p);
}
template <typename T>
void mobius(vector<T> &f) {
    const int n = f.size();
    vector<char> is_prime(n, true);
    auto diff = [&](const int p) {
        for (int q = 1, pq = p; pq < n; ++q, pq += p) {
            f[q] = f[q] - f[pq];
            is_prime[pq] = false;
        }
    };
    for (int p = 2; p < n; ++p) if (is_prime[p]) diff(p);
}
template <typename T, auto transform, auto inv_transform>
vector<T> transform_convolution(vector<T> a, vector<T> b) {
    const size_t n = a.size(), m = b.size();
    assert(n == m);
    transform(a), transform(b);
    for (size_t i = 0; i < n; ++i) a[i] = a[i] * b[i];
    inv_transform(a);
    return a;
}
template <typename T>
vector<T> gcd_convolution(vector<T> a, vector<T> b) {
    return transform_convolution<T, zeta<T>, mobius<T>>(move(a), move(b));
}
template <typename T>
vector<T> lcm_convolution(vector<T> a, vector<T> b) {
    return transform_convolution<T, zeta<T>, mobius<T>>(move(a), move(b));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<mint> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> a[i];
    for (int i = 1; i <= n; ++i) std::cin >> b[i];

    std::vector<mint> c = gcd_convolution(a, b);
    for (int i = 1; i <= n; ++i) std::cout << c[i] << " \n"[i == n];
}

