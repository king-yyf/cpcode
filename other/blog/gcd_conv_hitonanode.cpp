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


template <class T> void multiple_zeta(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = N / p; j > 0; --j) f[j] += f[j * p];
    }
}
// inverse of multiple_zeta O(N loglog N)
template <class T> void multiple_moebius(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = 1; j * p <= N; ++j) f[j] -= f[j * p];
    }
}
// 对于n的所有约数m,求f(m)的总和 O(N loglog N)
template <class T> void divisor_zeta(std::vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; ++p) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = 1; j * p <= N; ++j) f[j * p] += f[j];
    }
}
// inverse of divisor_zeta()
template <class T> void divisor_moebius(std::vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; ++p) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = N / p; j > 0; --j) f[j * p] -= f[j];
    }
} 
// GCD convolution, ret[k] = \sum_{gcd(i, j) = k} f[i] * g[j]
template <class T> vector<T> gcdconv(std::vector<T> f, std::vector<T> g) {
    assert(f.size() == g.size());
    multiple_zeta(f); multiple_zeta(g);
    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];
    multiple_moebius(f);
    return f;
}
// LCM convolution ret[k] = \sum_{lcm(i, j) = k} f[i] * g[j]
template <class T> vector<T> lcmconv(vector<T> f, vector<T> g) {
    assert(f.size() == g.size());
    divisor_zeta(f); divisor_zeta(g);
    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];
    divisor_moebius(f);
    return f;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    std::vector<mint> A(N + 1), B(N + 1);
    for (int i = 1; i <= N; ++i) cin >> A[i];
    for (int i = 1; i <= N; ++i) cin >> B[i];
    auto ret = gcdconv(A, B);
    for (int i = 1; i <= N; ++i) cout << ret[i] << (i == N ? '\n' : ' ');
}
