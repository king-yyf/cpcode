#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-1644

using ll = long long;

template <class T, T (*op)(T, T)>
class ST {
 public:
  int n;
  vector<vector<T>> mat;
 
  ST(const vector<T>& a) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = op(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
 
  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return op(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};
ll op(ll x,ll y) {return min(x,y);}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, a, b;
    cin >> n >> a >> b;
    vector<long long> f(n + 1);
    for (int i = 0; i < n; ++i) {
    	cin >> f[i + 1];
    	f[i + 1] += f[i];
    }
    
    ST<ll,op> s(f);

    long long mx = -1e18;
    for (int i = a; i <= n; ++i) {
    	int l = max(0, i - b);
    	mx = max(mx, f[i] - s.get(l, i - a));
    }    
    cout << mx << '\n';
    return 0;
}
