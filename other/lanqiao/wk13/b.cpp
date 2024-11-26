#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ar(x) array<int,x> 
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> T f_div(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0));}
template <class T> T c_div(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0));}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
#ifdef sigma-yyf
#define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    cerr << s << ": " << h, ((cerr << ", " << t), ..., (cerr << "\n"));
}
#else
#define dbg(...) void(0)
#endif
template<class Fun> class Y_comb {
    Fun _f;
public:
    template<class T> explicit Y_comb(T &&fun): _f(forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...As) {return _f(ref(*this), forward<Args>(As)...);}
};
template<class Fun> decltype(auto) y_comb(Fun &&fun) { return Y_comb<decay_t<Fun>>(forward<Fun>(fun));}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;
constexpr char nl = '\n';
constexpr int inf = 1'061'109'567;
constexpr ll infll = 2'000'000'000'000'000'000;
constexpr int N = 2e5 + 5;
int n, m, q;
int x, y, k;
string s, t;

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


void solve(int tt) {
    ll n;
    rd(n);
    // if(n==1){
    // 	wt("L\n");
    // 	return;
    // }
    // if(n==2){
    // 	wt("Q\n");
    // 	return;
    // }
    auto p =  fast_factorize::factor(n);
    ll c=1;
    for(auto&[k,v]:p){
    	c*=(v+1);
    }
    // dbg(c);
    if(c%2==0){
    	wt("Q",nl);
    }else wt("L",nl);
}
bool boolf(int tt) {
    return 0;
}

int main() {
    int T = 1, fun_type = 0;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        if (fun_type == 0) solve(cas);
        else if (fun_type == 1) cout << (boolf(cas) ? "Yes" : "No") << '\n';
        else cout << (boolf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}