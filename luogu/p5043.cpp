#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

// struct DSU {
//     vector<int> p, siz;
//     DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
//     inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
//     bool same(int x, int y) { return get(x) == get(y); }
//     bool merge(int x, int y) {
//         x = get(x), y = get(y);
//         if (x == y) return false;
//         if(x > y) {
//         	siz[y] += siz[x];
//         	p[x]=y;
//         }
//         else{
//         	siz[x] += siz[y];
//         	p[y] = x;
//         }
//         return true;
//     }
//     int size(int x) { return siz[get(x)]; }
//     vector<vector<int>> groups() {
//         vector<vector<int>> res(p.size());
//         for (int i = 0; i < p.size(); i++) res[get(i)].push_back(i);
//         res.erase(
//             remove_if(res.begin(), res.end(),
//                            [&](const vector<int>& v) { return v.empty(); }),
//             res.end());
//         return res;
//     }
// };

int p[55];
int get(int x){
	if(p[x]==x) return x;
	return p[x]=get(p[x]);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,m;
    cin >> m;
    for(int i=0;i<m;++i)p[i]=i;
    using Hash = YYF::Hash<2>;
    set<Hash> st[m];
    for (int i = 0; i < m; ++i) {
    	cin >> n;
    	vector<vector<int>> g(n);
    	for (int j = 0, v; j < n; ++j) {
    		cin >> v;
    		v--;
    		if (v == -1) {
    			continue;
    		}
    		g[v].push_back(j);
    		g[j].push_back(v);
    	}
    	for(int j=0;j<n;++j){
    		TreeHash hs(g,j);
    		st[i].insert(hs.hash[j]);
    	}
    }
    for (int i =0;i<m;++i){
    	for (auto &hs:st[i]){
    		for(int j=i+1;j<m;++j){
    			if(st[j].count(hs)){
    				p[j]=get(p[i]);
    				break;
    			}
    		}
    	}
    }
    for (int i = 0; i < m; ++i) {
        	cout<<p[i]+1<<"\n";
    }

    return 0;
}
