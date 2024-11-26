#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

using Int = long long;

template <class T1, class T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <class T> ostream &operator<<(ostream &os, const vector<T> &as) { const int sz = as.size(); os << "["; for (int i = 0; i < sz; ++i) { if (i >= 256) { os << ", ..."; break; } if (i > 0) { os << ", "; } os << as[i]; } return os << "]"; }
template <class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cerr << *i << " "; cerr << endl; }
template <class T> bool chmin(T &t, const T &f) { if (t > f) { t = f; return true; } return false; }
template <class T> bool chmax(T &t, const T &f) { if (t < f) { t = f; return true; } return false; }
#define COLOR(s) ("\x1b[" s "m")

// T: monoid representing information of an interval.
//   T()  should return the identity.
//   T(S s)  should represent a single element of the array.
//   T::push(T &l, T &r)  should push the lazy update.
//   T::pull(const T &l, const T &r)  should pull two intervals.
template <class T> struct SegmentTreeRange {
  int logN, n;
  vector<T> ts;
  SegmentTreeRange() : logN(0), n(0) {}
  explicit SegmentTreeRange(int n_) {
    for (logN = 0, n = 1; n < n_; ++logN, n <<= 1) {}
    ts.resize(n << 1);
  }
  template <class S> explicit SegmentTreeRange(const vector<S> &ss) {
    const int n_ = ss.size();
    for (logN = 0, n = 1; n < n_; ++logN, n <<= 1) {}
    ts.resize(n << 1);
    for (int i = 0; i < n_; ++i) at(i) = T(ss[i]);
    build();
  }
  T &at(int i) {
    return ts[n + i];
  }
  void build() {
    for (int u = n; --u; ) pull(u);
  }

  inline void push(int u) {
    ts[u].push(ts[u << 1], ts[u << 1 | 1]);
  }
  inline void pull(int u) {
    ts[u].pull(ts[u << 1], ts[u << 1 | 1]);
  }

  // Applies T::f(args...) to [a, b).
  template <class F, class... Args>
  void ch(int a, int b, F f, Args &&... args) {
    assert(0 <= a); assert(a <= b); assert(b <= n);
    if (a == b) return;
    a += n; b += n;
    for (int h = logN; h; --h) {
      const int aa = a >> h, bb = b >> h;
      if (aa == bb) {
        if ((aa << h) != a || (bb << h) != b) push(aa);
      } else {
        if ((aa << h) != a) push(aa);
        if ((bb << h) != b) push(bb);
      }
    }
    for (int aa = a, bb = b; aa < bb; aa >>= 1, bb >>= 1) {
      if (aa & 1) (ts[aa++].*f)(args...);
      if (bb & 1) (ts[--bb].*f)(args...);
    }
    for (int h = 1; h <= logN; ++h) {
      const int aa = a >> h, bb = b >> h;
      if (aa == bb) {
        if ((aa << h) != a || (bb << h) != b) pull(aa);
      } else {
        if ((aa << h) != a) pull(aa);
        if ((bb << h) != b) pull(bb);
      }
    }
  }

  // Calculates the product for [a, b).
  T get(int a, int b) {
    assert(0 <= a); assert(a <= b); assert(b <= n);
    if (a == b) return T();
    a += n; b += n;
    for (int h = logN; h; --h) {
      const int aa = a >> h, bb = b >> h;
      if (aa == bb) {
        if ((aa << h) != a || (bb << h) != b) push(aa);
      } else {
        if ((aa << h) != a) push(aa);
        if ((bb << h) != b) push(bb);
      }
    }
    T prodL, prodR, t;
    for (int aa = a, bb = b; aa < bb; aa >>= 1, bb >>= 1) {
      if (aa & 1) { t.pull(prodL, ts[aa++]); prodL = t; }
      if (bb & 1) { t.pull(ts[--bb], prodR); prodR = t; }
    }
    t.pull(prodL, prodR);
    return t;
  }

  // Calculates T::f(args...) of a monoid type for [a, b).
  //   op(-, -)  should calculate the product.
  //   e()  should return the identity.
  template <class Op, class E, class F, class... Args>
#if __cplusplus >= 201402L
  auto
#else
  decltype((std::declval<T>().*F())())
#endif
  get(int a, int b, Op op, E e, F f, Args &&... args) {
    assert(0 <= a); assert(a <= b); assert(b <= n);
    if (a == b) return e();
    a += n; b += n;
    for (int h = logN; h; --h) {
      const int aa = a >> h, bb = b >> h;
      if (aa == bb) {
        if ((aa << h) != a || (bb << h) != b) push(aa);
      } else {
        if ((aa << h) != a) push(aa);
        if ((bb << h) != b) push(bb);
      }
    }
    auto prodL = e(), prodR = e();
    for (int aa = a, bb = b; aa < bb; aa >>= 1, bb >>= 1) {
      if (aa & 1) prodL = op(prodL, (ts[aa++].*f)(args...));
      if (bb & 1) prodR = op((ts[--bb].*f)(args...), prodR);
    }
    return op(prodL, prodR);
  }

  // Find min b s.t. T::f(args...) returns true,
  // when called for the partition of [a, b) from left to right.
  //   Returns n + 1 if there is no such b.
  template <class F, class... Args>
  int findRight(int a, F f, Args &&... args) {
    assert(0 <= a); assert(a <= n);
    if ((T().*f)(args...)) return a;
    if (a == n) return n + 1;
    a += n;
    for (int h = logN; h; --h) push(a >> h);
    for (; ; a >>= 1) if (a & 1) {
      if ((ts[a].*f)(args...)) {
        for (; a < n; ) {
          push(a);
          if (!(ts[a <<= 1].*f)(args...)) ++a;
        }
        return a - n + 1;
      }
      ++a;
      if (!(a & (a - 1))) return n + 1;
    }
  }

  // Find max a s.t. T::f(args...) returns true,
  // when called for the partition of [a, b) from right to left.
  //   Returns -1 if there is no such a.
  template <class F, class... Args>
  int findLeft(int b, F f, Args &&... args) {
    assert(0 <= b); assert(b <= n);
    if ((T().*f)(args...)) return b;
    if (b == 0) return -1;
    b += n;
    for (int h = logN; h; --h) push((b - 1) >> h);
    for (; ; b >>= 1) if ((b & 1) || b == 2) {
      if ((ts[b - 1].*f)(args...)) {
        for (; b <= n; ) {
          push(b - 1);
          if (!(ts[(b <<= 1) - 1].*f)(args...)) --b;
        }
        return b - n - 1;
      }
      --b;
      if (!(b & (b - 1))) return -1;
    }
  }
};

////////////////////////////////////////////////////////////////////////////////

constexpr Int INF = 1001001001001001001LL;

struct NodeMin {
  Int mn;
  Int lz;
  NodeMin() : mn(INF), lz(0) {}
  NodeMin(Int val) : mn(val), lz(0) {}
  void push(NodeMin &l, NodeMin &r) {
    if (lz) {
      l.add(lz);
      r.add(lz);
      lz = 0;
    }
  }
  void pull(const NodeMin &l, const NodeMin &r) {
    mn = min(l.mn, r.mn);
  }
  void add(Int val) {
    mn += val;
    lz += val;
  }
  // leaf
  void change(Int val) {
    mn = val;
  }
};


constexpr int L = 200'010;

int N, A, B;
vector<int> X, Y;

int main() {
  for (; ~scanf("%d%d%d", &N, &A, &B); ) {
    X.resize(N);
    Y.resize(N);
    for (int i = 0; i < N; ++i) {
      scanf("%d%d", &X[i], &Y[i]);
    }
    
    vector<vector<pair<int, int>>> add(L + 1), rem(L + 1);
    for (int i = 0; i < N; ++i) {
      // x <= X[i] < x + A
      int x0 = X[i] - A + 1;
      int x1 = X[i] + 1;
      int y0 = Y[i] - B + 1;
      int y1 = Y[i] + 1;
      chmax(x0, 0); chmin(x1, L);
      chmax(y0, 0); chmin(y1, L);
      add[x0].emplace_back(y0, y1);
      rem[x1].emplace_back(y0, y1);
    }
    SegmentTreeRange<NodeMin> seg(L);
    for (int y = 0; y < L; ++y) {
      seg.at(y) = 0;
    }
    seg.build();
    Int ans = 0;
    for (int x = 0; x < L; ++x) {
      for (const auto &e : rem[x]) seg.ch(e.first, e.second, &NodeMin::add, +1);
      for (const auto &e : add[x]) seg.ch(e.first, e.second, &NodeMin::add, -1);
      chmax(ans, -seg.ts[1].mn);
    }
    printf("%lld\n", ans);
  }
  return 0;
}
