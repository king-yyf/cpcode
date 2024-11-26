#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1746

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
using mint = static_mod<1000000007>; // 1000000007


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
        a[i]--;
    }
    vector f(n, vector<mint>(m));

    if (a[0] >= 0) {
        f[0][a[0]] = 1;
    } else {
        for (int j = 0; j < m; ++j) {
            f[0][j] = 1;
        }
    }

    for (int i = 1; i < n; ++i) {
        if (a[i] >= 0) {
            for (int j = -1; j <= 1; ++j) {
                if (a[i] - j >= 0 && a[i] - j < m) {
                    f[i][a[i]] += f[i - 1][a[i] - j];
                }
            }
        } else {
            for (int j = 0; j < m; ++j) {
                for (int k = -1; k <= 1; ++k) {
                    if (j + k < 0 || j + k >= m) continue;
                    f[i][j] += f[i - 1][j + k];
                }
            }
        }
    }

    mint ans = 0;

    for (int i = 0; i < m; ++i) {
    	ans += f[n - 1][i];
    }

    cout << ans << '\n';

    return 0;
}
