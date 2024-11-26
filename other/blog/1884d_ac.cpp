#include <bits/stdc++.h>
#ifdef LOCAL
#include <debug.hpp>
#else
#define debug(...) void(0)
#endif

namespace gcd_convolution {

// f(k) <- \sum_{k | i} f(i)
template <typename T> void divisor_transform(std::vector<T>& f) {
    int n = f.size();
    std::vector<bool> sieve(n, true);
    for (int p = 2; p < n; p++) {
        if (sieve[p]) {
            for (int k = (n - 1) / p; k > 0; k--) {
                sieve[k * p] = false;
                f[k] += f[k * p];
            }
        }
    }
    for (int i = 1; i < n; i++) f[i] += f[0];
}

// inverse of divisor transform
template <typename T> void inverse_divisor_transform(std::vector<T>& f) {
    int n = f.size();
    std::vector<bool> sieve(n, true);
    for (int i = 1; i < n; i++) f[i] -= f[0];
    for (int p = 2; p < n; p++) {
        if (sieve[p]) {
            for (int k = 1 / p; k * p < n; k++) {
                sieve[k * p] = false;
                f[k] -= f[k * p];
            }
        }
    }
}

template <typename T> std::vector<T> gcd_convolution(std::vector<T> f, std::vector<T> g) {
    assert(f.size() == g.size());
    divisor_transform(f);
    divisor_transform(g);
    for (int i = 0; i < int(f.size()); i++) f[i] *= g[i];
    inverse_divisor_transform(f);
    return f;
}

}  // namespace gcd_convolution

using namespace std;

typedef long long ll;
#define all(x) begin(x), end(x)
constexpr int INF = (1 << 30) - 1;
constexpr long long IINF = (1LL << 60) - 1;
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

template <class T> istream& operator>>(istream& is, vector<T>& v) {
    for (auto& x : v) is >> x;
    return is;
}

template <class T> ostream& operator<<(ostream& os, const vector<T>& v) {
    auto sep = "";
    for (const auto& x : v) os << exchange(sep, " ") << x;
    return os;
}

template <class T, class U = T> bool chmin(T& x, U&& y) { return y < x and (x = forward<U>(y), true); }

template <class T, class U = T> bool chmax(T& x, U&& y) { return x < y and (x = forward<U>(y), true); }

template <class T> void mkuni(vector<T>& v) {
    sort(begin(v), end(v));
    v.erase(unique(begin(v), end(v)), end(v));
}

template <class T> int lwb(const vector<T>& v, const T& x) { return lower_bound(begin(v), end(v), x) - begin(v); }

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    cin >> a;

    vector<ll> f(n + 1, 0);
    for (int& x : a) f[x]++;
    auto g = gcd_convolution::gcd_convolution(f, f);
    vector<bool> ng(n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (not f[i]) continue;
        for (int j = i; j <= n; j += i) ng[j] = true;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (not ng[i]) {
            ans += g[i];
        }
    }
    ans /= 2;

    // cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    for (; t--;) solve();
    return 0;
}
