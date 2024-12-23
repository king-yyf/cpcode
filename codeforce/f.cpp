#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
#pragma GCC optimize ("Ofast,unroll-loops")
#pragma GCC optimize("no-stack-protector,fast-math")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<double> vd;
typedef vector<vi> vvi;
typedef vector<vvi> vvvi;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<pii> vpii;
typedef vector<vpii> vvpii;
typedef vector<pll> vpll;
typedef vector<vpll> vvpll;
typedef vector<pdd> vpdd;
typedef vector<vd> vvd;
#define yn(ans) printf("%s\n", (ans)?"Yes":"No");
#define YN(ans) printf("%s\n", (ans)?"YES":"NO");
template<class T> bool chmax(T &a, T b) {
  if (a >= b) return false;
  a = b; return true;
}
template<class T> bool chmin(T &a, T b) {
  if (a <= b) return false;
  a = b; return true;
}
#define FOR(i, s, e, t) for ((i) = (s); (i) < (e); (i) += (t)) 
#define REP(i, e) for (int i = 0; i < (e); ++i) 
#define REP1(i, s, e) for (int i = (s); i < (e); ++i)
#define RREP(i, e) for (int i = (e); i >= 0; --i)
#define RREP1(i, e, s) for (int i = (e); i >= (s); --i)
#define all(v) v.begin(), v.end()
#define pb push_back
#define qb pop_back
#define pf push_front
#define qf pop_front
#define maxe max_element
#define mine min_element
ll inf = 1e18;
#define DEBUG printf("%d\n", __LINE__); fflush(stdout);
template<class T> void print(vector<T> &v, bool withSize = false) {
  if (withSize) cout << v.size() << endl;
  REP(i, v.size()) cout << v[i] << " "; 
  cout << endl;
}
mt19937_64 rng((unsigned int) chrono::steady_clock::now().time_since_epoch().count());

int __FAST_IO__ = []() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);
  return 0;
}();

// Mint & Combinatorics
 
template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  return u;
}
 
template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;
 
  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }
 
  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }
 
  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }
 
  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }
 
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, long long>::value, Modular>::type& operator*=(const Modular& rhs) {
    long long q = static_cast<long long>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }
 
  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }
 
  friend const Type& abs(const Modular& x) { return x.value; }
 
  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);
 
  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);
 
  template <typename V, typename U>
  friend V& operator>>(V& stream, Modular<U>& number);
 
 private:
  Type value;
};
 
template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }
 
template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
 
template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }
 
template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
 
template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
 
template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
 
template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
 
template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}
 
template <typename T>
bool IsZero(const Modular<T>& number) {
  return number() == 0;
}
 
template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}
 
// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
  return stream << number();
}
 
// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, long long>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}
 
struct MOD {
    static int value;
};
int MOD::value = 998244353;
using Mint = Modular<MOD>;
typedef vector<Mint> vm;
typedef vector<vm> vvm;


vector<vector<vector<int>>> readGraphWithWeight(int N, int M, bool isDirected = false) {
  vector<vvi> g(N);
    REP(i, M) {
      int u, v, w;
      cin >> u >> v >> w;
      --u, --v;
      g[u].push_back({v, w});
      if (!isDirected) g[v].push_back({u, w});
    }
    return g;
}

class Union {
public:
  Union(int _n): n(_n), tot(n), p(n, 0), c(n, 1) {REP(i, n) p[i] = i;}
  int find(int x) {return p[x] == x?x:(p[x] = find(p[x]));}
  bool merge(int x, int y) {
    int a = find(x), b = find(y);
    if (a == b) return false;
    p[max(a, b)] = p[min(a, b)];
    c[min(a, b)] += c[max(a, b)];
    c[max(a, b)] = 0;
    --tot;
    return true;
  }
  int ng() {return tot;}
  int count(int g) {return c[g];}
  
private:
  int n, tot;
  vector<int> p, c;
};

int main() {
    int t;
    cin >> t;
    while (t--) {
      int N, Q;
      cin >> N;
      vi v(N);
      REP(i, N) cin >> v[i];
      map<ll, int> m;
      REP(i, N) m[v[i]]++;
      
      cin >> Q;
      REP(i, Q) {
        ll x, y;
        cin >> x >> y;
        ll delta = x * x - 4 * y;
        ll d = sqrt(delta);
        ll ans = 0;
        auto check = [&](ll e) {
        //  printf("%lld %lld %lld\n", x, y, (ll)e);
          if (e % 2 != 0) return;
          e /= 2;
          ll f = x - e;
          if ((__int128_t)e * f != y) return;
          if (m.count(e) && m.count(f)) {
            if (e == f) ans += 1ll * (m[e] - 1) * m[e] / 2;
            else ans += 1ll * m[e] * m[f];
          }
        };
        if (d * d != delta) {
          ans = 0;
        } else {
          check(x + d);
        }
        printf("%lld ", ans);
      }
      printf("\n");
    }
    
    return 0;
}