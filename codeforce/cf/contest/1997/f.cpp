// Problem: F. Chips on a Line
// Contest: Codeforces - Educational Codeforces Round 168 (Rated for Div. 2)
// URL: https://codeforces.com/contest/1997/problem/F
// Memory Limit: 512 MB
// Time Limit: 5000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

// Author: EnucAI
#include <bits/stdc++.h>

#ifdef LOCAL
#include "debug.h"
#else
#define D(...) ((void)0)
#endif

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = std::vector<int>;
using pii = std::pair<int, int>;

constexpr int inf = std::numeric_limits<int>::max() / 2;
constexpr ll infll = std::numeric_limits<ll>::max() / 2;
constexpr ld eps = 1e-8l;

#define all(x) (x).begin(), (x).end()
#define sz(x) ((int)((x).size()))
#define rep(i, j, k) for (int i = (j); i <= (k); i++)
#define per(i, j, k) for (int i = (j); i >= (k); i--)
#define fi first
#define se second
#define mp std::make_pair
#define pb push_back
#define ppb pop_back
#define eb emplace_back

template <class X, class Y> void chkmax(X &x, const Y &y) { if (x < y) x = y; }
template <class X, class Y> void chkmin(X &x, const Y &y) { if (x > y) x = y; }

template <int P>
class mod_int {
  using Z = mod_int;

private:
  static int mo(int x) { return x < 0 ? x + P : x; }

public:
  int x;
  int val() const { return x; }
  mod_int() : x(0) {}
  template <class T>
  mod_int(const T &x_) : x(x_ >= 0 && x_ < P ? static_cast<int>(x_) : mo(static_cast<int>(x_ % P))) {}
  bool operator==(const Z &rhs) const { return x == rhs.x; }
  bool operator!=(const Z &rhs) const { return x != rhs.x; }
  Z operator-() const { return Z(x ? P - x : 0); }
  Z pow(ll k) const {
    Z res = 1, t = *this;
    while (k) {
      if (k & 1) res *= t;
      if (k >>= 1) t *= t;
    }
    return res;
  }
  Z &operator++() {
    x < P - 1 ? ++x : x = 0;
    return *this;
  }
  Z &operator--() {
    x ? --x : x = P - 1;
    return *this;
  }
  Z operator++(int) {
    Z ret = x;
    x < P - 1 ? ++x : x = 0;
    return ret;
  }
  Z operator--(int) {
    Z ret = x;
    x ? --x : x = P - 1;
    return ret;
  }
  Z inv() const { return pow(P - 2); }
  Z &operator+=(const Z &rhs) {
    (x += rhs.x) >= P && (x -= P);
    return *this;
  }
  Z &operator-=(const Z &rhs) {
    (x -= rhs.x) < 0 && (x += P);
    return *this;
  }
  Z &operator*=(const Z &rhs) {
    x = 1ULL * x * rhs.x % P;
    return *this;
  }
  Z &operator/=(const Z &rhs) { return *this *= rhs.inv(); }
#define setO(T, o)                                 \
  friend T operator o(const Z &lhs, const Z &rhs) {\
    Z res = lhs;                                   \
    return res o## = rhs;                          \
  }
  setO(Z, +) setO(Z, -) setO(Z, *) setO(Z, /)
#undef setO
};
constexpr int P = 998244353;
using Z = mod_int<P>;

constexpr int maxn = 1e3 + 5, maxx = 10 + 5, maxv = maxn * 55;

int n, x, m;
int fib[maxn], len;

std::bitset<maxv> f[maxn];
Z dp[maxn][maxv];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);
  fib[1] = fib[2] = 1;
  len = 2;
  while (true) {
    fib[len + 1] = fib[len] + fib[len - 1];
    if (fib[len + 1] > maxv) break;
    len++;
  }
  std::cin >> n >> x >> m;
  f[0].set(0);
  rep(i, 1, m) {
    rep(j, 1, len) f[i] |= f[i - 1] << fib[j];
  }
  rep(i, 0, n * fib[x]) if (f[m].test(i) && !f[m - 1].test(i)) dp[n][i] = 1;
  per(i, x, 1) {
    int val = n * fib[i];
    per(j, n, 0) per(k, val, 0) if (dp[j][k].val()) {
      if (j && k >= fib[i]) dp[j - 1][k - fib[i]] += dp[j][k];
    }
  }
  std::cout << dp[0][0].val() << '\n';
}