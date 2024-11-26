#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://projecteuler.net/problem=3
// 600851475143


namespace fast_factorize {
  struct m64 {
    using i64 = int64_t;
    using u64 = uint64_t;
    using u128 = __uint128_t;
    inline static u64 m, r, n2; // r * m = -1 (mod 1<<64), n2 = 1<<128 (mod m)
    static void set_mod(u64 m) {
        assert(m < (1ull << 62));
        assert((m & 1) == 1);
        m64::m = m; n2 = -u128(m) % m; r = m;
        for (int _ = 0; _ < 5; ++ _) r *= 2 - m*r;
        r = -r;
        assert(r * m == -1ull);
    }
    static u64 reduce(u128 b) { return (b + u128(u64(b) * r) * m) >> 64; }
    u64 x;
    m64() : x(0) {}
    m64(u64 x) : x(reduce(u128(x) * n2)){};
    u64 val() const { u64 y = reduce(x); return y >= m ? y-m : y; }
    m64 &operator+=(m64 y) { x += y.x - (m << 1); x = (i64(x) < 0 ? x + (m << 1) : x);return *this; }
    m64 &operator-=(m64 y) {x -= y.x;x = (i64(x) < 0 ? x + (m << 1) : x);return *this;}
    m64 &operator*=(m64 y) { x = reduce(u128(x) * y.x); return *this; }
    m64 operator+(m64 y) const { return m64(*this) += y; }
    m64 operator-(m64 y) const { return m64(*this) -= y; }
    m64 operator*(m64 y) const { return m64(*this) *= y; }
    bool operator==(m64 y) const { return (x >= m ? x-m : x) == (y.x >= m ? y.x-m : y.x); }
    bool operator!=(m64 y) const { return not operator==(y); }
    m64 pow(u64 n) const {
        m64 y = 1, z = *this;
        for ( ; n; n >>= 1, z *= z) if (n & 1) y *= z;
        return y;
    }
  };
  constexpr int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  
  mt19937_64 rng_mt{random_device{}()};
  ll rnd(ll n) { return uniform_int_distribution<ll>(0, n - 1)(rng_mt); }
  bool primetest(const uint64_t x) {
      using u64 = uint64_t;
      if (x == 2 or x == 3 or x == 5 or x == 7) return true;
      if (x % 2 == 0 or x % 3 == 0 or x % 5 == 0 or x % 7 == 0) return false;
      if (x < 121) return x > 1;
      const u64 d = (x-1) >> __builtin_ctzll(x-1);
      m64::set_mod(x);
      const m64 one(1), minus_one(x-1);
      auto ok = [&](u64 a) {
          auto y = m64(a).pow(d);
          u64 t = d;
          while (y != one and y != minus_one and t != x-1) y *= y, t <<= 1;
          if (y != minus_one and t % 2 == 0) return false;
          return true;
      };
      if (x < (1ull << 32)) {
          for (u64 a : { 2, 7, 61 }) if (not ok(a)) return false;
      } else {
          for (u64 a : { 2, 325, 9375, 28178, 450775, 9780504, 1795265022 }) {
              if (x <= a) return true;
              if (not ok(a)) return false;
          }
      }
      return true;
  }
  ll rho(ll n, ll c) {
    m64::set_mod(n);
    assert(n > 1);
    const m64 cc(c);
    auto f = [&](m64 x) { return x * x + cc; };
    m64 x = 1, y = 2, z = 1, q = 1;
    ll g = 1;
    const ll m = 1LL << (lg(n) / 5); // ?
    for (ll r = 1; g == 1; r <<= 1) {
      x = y;
      for (int _ = 0; _ < r; ++ _) y = f(y);
      for (ll k = 0; k < r and g == 1; k += m) {
        z = y;
        for (int _ = 0, t = min(m, r - k); _ < t; ++ _)
          y = f(y), q *= x - y;
        g = gcd(q.val(), n);
      }
    }
    if (g == n)
      do {
        z = f(z);
        g = gcd((x - z).val(), n);
      } while (g == 1);
    return g;
  }
  ll find_prime_factor(ll n) {
    assert(n > 1);
    if (primetest(n)) return n;
    for (int _ = 0; _ < 100; ++ _) {
      ll m = rho(n, rnd(n));
      if (primetest(m)) return m;
      n = m;
    }
    cerr << "failed" << endl;
    assert(false);
    return -1;
  }
  vector<pair<ll, int>> factor(ll n) {
    assert(n >= 1);
    vector<pair<ll, int>> pf;
    for (int p = 2; p < 100; ++ p) {
      if (p * p > n) break;
      if (n % p == 0) {
        int e = 0;
        do {
          n /= p, e += 1;
        } while (n % p == 0);
        pf.emplace_back(p, e);
      }
    }
    while (n > 1) {
      ll p = find_prime_factor(n);
      int e = 0;
      do {
        n /= p, e += 1;
      } while (n % p == 0);
      pf.emplace_back(p, e);
    }
    sort(pf.begin(), pf.end());
    return pf;
  }
} // namespace fast_factorize

// auto p =  fast_factorize::factor(x);


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long t = 600851475143;
    auto p =  fast_factorize::factor(t);
    long long ans = -1;
    for (auto &[x, v] : p) {
    	if (x > ans) ans = x;
    }
    cout << ans << '\n';
    return 0;
}
