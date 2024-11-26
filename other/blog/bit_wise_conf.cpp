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

template <typename T, typename F> 
void abstract_fwht(vector<T>& seq, F f) {
    const int n = seq.size();
    assert(__builtin_popcount(n) == 1);
    for (int w = 1; w < n; w *= 2) {
        for (int i = 0; i < n; i += w * 2) {
            for (int j = 0; j < w; j++) { f(seq[i + j], seq[i + j + w]); }
        }
    }
}
template <typename T, typename F1, typename F2> 
vector<T> bitwise_conv(vector<T> x, vector<T> y, F1 f, F2 finv) {
    const int n = x.size();
    assert(__builtin_popcount(n) == 1);
    assert(x.size() == y.size());
    if (x == y) { abstract_fwht(x, f), y = x;} 
    else { abstract_fwht(x, f), abstract_fwht(y, f);}
    for (size_t i = 0; i < x.size(); i++) { x[i] *= y[i]; }
    abstract_fwht(x, finv);
    return x;
}
template <typename T> vector<T> xorconv(vector<T> x, vector<T> y) {
    auto f = [](T& l, T& r){T c = l + r; r = l - r, l = c;};
    auto finv = [](T& l, T& r){T c = l + r; r = (l - r) / 2, l = c / 2;};
    return bitwise_conv(x, y, f, finv);
}
template <typename T> vector<T> andconv(vector<T> x, vector<T> y) {
    return bitwise_conv(x, y, [](T& l, T& r){l += r;}, [](T& l, T& r) {l -= r;});
}
template <typename T> vector<T> orconv(vector<T> x, vector<T> y) {
    return bitwise_conv(x, y, [](T& l, T& r){r += l;}, [](T& l, T& r) {r -= l;});
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<mint> A(1 << N), B(1 << N);
    for (auto &x : A) cin >> x;
    for (auto &x : B) cin >> x;

    for (auto x : xorconv(A, B)) cout << x << ' ';
}
