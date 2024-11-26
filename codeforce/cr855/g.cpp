#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define yn(cond) cout << ((cond) ? "Yes" : "No") << "\n";
#define YN(cond) cout << ((cond) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI = acos(-1.0);
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;


// 3哈希容易tle，默认双哈希, u128在cf上需要选c++20
namespace YYF {
using i64 = long long;
using u64 = unsigned long long;
using u128 = __uint128_t;
template <int BASE_NUM = 2>
struct Hash : array<u64, BASE_NUM> {
  using array<u64, BASE_NUM>::operator[];
  static constexpr int n = BASE_NUM;
  Hash() : array<u64, BASE_NUM>() {}
  static constexpr u64 md = (1ull << 61) - 1;
  constexpr static Hash set(const i64 &a) {
    Hash res;
    fill(begin(res), end(res), cast(a));
    return res;
  }
  Hash &operator+=(const Hash &r) {
    for (int i = 0; i < n; i++) if (((*this)[i] += r[i]) >= md) (*this)[i] -= md;
    return *this;
  }
  Hash &operator+=(const i64 &r) {
    u64 s = cast(r);
    for (int i = 0; i < n; i++) if (((*this)[i] += s) >= md) (*this)[i] -= md;
    return *this;
  }
  Hash &operator-=(const Hash &r) {
    for (int i = 0; i < n; i++) if (((*this)[i] += md - r[i]) >= md) (*this)[i] -= md;
    return *this;
  }
  Hash &operator-=(const i64 &r) {
    u64 s = cast(r);
    for (int i = 0; i < n; i++) if (((*this)[i] += md - s) >= md) (*this)[i] -= md;
    return *this;
  }
  Hash &operator*=(const Hash &r) {
    for (int i = 0; i < n; i++) (*this)[i] = modmul((*this)[i], r[i]);
    return *this;
  }
  Hash &operator*=(const i64 &r) {
    u64 s = cast(r);
    for (int i = 0; i < n; i++) (*this)[i] = modmul((*this)[i], s);
    return *this;
  }
  Hash operator+(const Hash &r) { return Hash(*this) += r; }
  Hash operator+(const i64 &r) { return Hash(*this) += r; }
  Hash operator-(const Hash &r) { return Hash(*this) -= r; }
  Hash operator-(const i64 &r) { return Hash(*this) -= r; }
  Hash operator*(const Hash &r) { return Hash(*this) *= r; }
  Hash operator*(const i64 &r) { return Hash(*this) *= r; }
  Hash operator-() const {
    Hash res;
    for (int i = 0; i < n; i++) res[i] = (*this)[i] == 0 ? 0 : md - (*this)[i];
    return res;
  }
  friend Hash pfma(const Hash &a, const Hash &b, const Hash &c) {
    Hash res;
    for (int i = 0; i < n; i++) res[i] = modfma(a[i], b[i], c[i]);
    return res;
  }
  friend Hash pfma(const Hash &a, const Hash &b, const i64 &c) {
    Hash res; u64 s = cast(c);
    for (int i = 0; i < n; i++) res[i] = modfma(a[i], b[i], s);
    return res;
  }
  Hash pow(long long e) {
    Hash a{*this}, res{Hash::set(1)};
    for (; e; a *= a, e >>= 1) if (e & 1) res *= a;
    return res;
  }
  static Hash get_basis() {
    static auto rand_t =
        chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count();
    static mt19937_64 rng(rand_t);
    Hash h;
    for (int i = 0; i < n; i++) {
      while (isPrimitive(h[i] = rng() % (md - 1) + 1) == false);
    }
    return h;
  }

 private:
  static u64 modpow(u64 a, u64 b) {
    u64 r = 1;
    for (a %= md; b; a = modmul(a, a), b >>= 1) r = modmul(r, a);
    return r;
  }
  static bool isPrimitive(u64 x) {
    for (auto &d : vector<u64>{2, 3, 5, 7, 11, 13, 31, 41, 61, 151, 331, 1321})
      if (modpow(x, (md - 1) / d) <= 1) return false;
    return true;
  }
  static inline constexpr u64 cast(const long long &a) {
    return a < 0 ? a + md : a;
  }
  static inline constexpr u64 modmul(const u64 &a, const u64 &b) {
    u128 ret = u128(a) * b;
    ret = (ret & md) + (ret >> 61);
    return ret >= md ? ret - md : ret;
  }
  static inline constexpr u64 modfma(const u64 &a, const u64 &b, const u64 &c) {
    u128 ret = u128(a) * b + c;
    ret = (ret & md) + (ret >> 61);
    return ret >= md ? ret - md : ret;
  }
};
} 
template <typename G>
struct TreeHash {
  using Hash = YYF::Hash<2>;
  const G& g;
  int n, root;
  vector<Hash> hash;
  vector<int> dep;
  vector<bool> syn;
  static vector<Hash>& xs() {
    static vector<Hash> _xs;
    return _xs;
  }
  TreeHash(const G& _g, int rt = 0) : n(g.size()), g(_g), dep(n, 0), hash(n), root(rt){
    while ((int)xs().size() <= n) xs().push_back(Hash::get_basis());
    dfs(root, -1);
  }
  void isomorphic() {
    syn.assign(n, false);
    dfs2(root, -1);
  }
 private:
  int dfs(int u, int p) {
    int d = 0;
    for (auto& v : g[u]) if (v != p) 
      d = max(d, dfs(v, u) + 1);
    Hash x = xs()[d], h = Hash::set(1);
    for (auto& v : g[u]) if (v != p) h = h * (x + hash[v]);
    hash[u] = h;
    return dep[u] = d;
  }
  void dfs2(int u, int p) {
    map<Hash,int> cnt, mp;
    for (auto &v : g[u]) if (v != p) {
      cnt[hash[v]]++;
      if (!mp.count(hash[v])) mp[hash[v]] = v;
      dfs2(v, u);
    }
    int d = -1;
    for (auto & [hsh, v] : cnt) if (v & 1) {
      if (~d) return;
      d = mp[hsh];
    }
    if (d == -1 || syn[d]) syn[u] = true;
  }
};

void ac_yyf(int tt) {
	  cin >> n;
    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }
    TreeHash hs(g);
    hs.isomorphic();
    cout << (hs.syn[0] ? "YES\n" : "NO\n");
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
