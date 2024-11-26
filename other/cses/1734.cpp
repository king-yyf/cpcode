#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1734

struct Mo {
  int width;
  vector<int> left, right, order;

  Mo(int N, int Q) : order(Q) {
    width = max<int>(1, 1.0 * N / max<double>(1.0, sqrt(Q * 2.0 / 3.0)));
    iota(begin(order), end(order), 0);
  }

  void insert(int l, int r) { /* [l, r) */
    left.emplace_back(l);
    right.emplace_back(r);
  }

  template <typename AL, typename AR, typename DL, typename DR, typename REM>
  void run(const AL &add_left, const AR &add_right, const DL &delete_left,
           const DR &delete_right, const REM &rem) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if (ablock != bblock) return ablock < bblock;
      if (ablock & 1) return right[a] < right[b];
      return right[a] > right[b];
    });
    int nl = 0, nr = 0;
    for (auto idx : order) {
      while (nl > left[idx]) add_left(--nl);
      while (nr < right[idx]) add_right(nr++);
      while (nl < left[idx]) delete_left(nl++);
      while (nr > right[idx]) delete_right(--nr);
      rem(idx);
    }
  }
};


template <class T>
struct Discrete {
    vector<T> xs;
    Discrete(const vector<T>& v) {
        xs = v;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }
    int get(const T& x) const {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    inline int operator()(const T& x) const { return get(x); }
    T operator[](int i) { return xs[i]; }
    int size() const { return xs.size(); }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];    
    }
    Discrete<int> v(a);
    for (int i = 0; i < n; ++i) {
    	a[i] = v(a[i]);
    }
    Mo mo(n, q);   // n个元素，q次询问
    for (int i = 0, l, r; i < q; ++i) {
        cin >> l >> r;
        mo.insert(l-1, r);  //query [l, r - 1]
    } 

    vector<int> ans(q), cnt(v.size() + 1);
    int cur = 0;
    auto add_l = [&](int x) {
        if (cnt[a[x]] == 0) cur++;
        cnt[a[x]]++;
    };
    auto add_r = [&](int x) {
        if (cnt[a[x]] == 0) cur++;
        cnt[a[x]]++;
    };
    auto del_l = [&](int x) {
        cnt[a[x]]--;
        if (cnt[a[x]] == 0) cur--;
    };
    auto del_r = [&](int x) {
        cnt[a[x]]--;
        if (cnt[a[x]] == 0) cur--;
    };

    auto rem = [&](int x) { ans[x] = cur; };
    mo.run(add_l,add_r,del_l,del_r,rem);

    for (int i = 0; i < q; ++i)
       cout << ans[i] << "\n";

    return 0;
}
