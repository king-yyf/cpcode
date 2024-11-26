#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<int B_size = -1>
struct SqrtDecomposition{
  using S = int; // 待分块数据类型
  using T = int; // 答案数据类型
  vector<S> A;
  int B; // 分块大小
  int n; // 数组长度
  T UNIT;
  bool has_init;
  SqrtDecomposition(const int _n) : n(_n), has_init(false) {
    A.resize(_n);
    B = B_size == -1 ? sqrt(n) : B_size;
  }
  SqrtDecomposition(const vector<S>& v_) : has_init(false){
    A = v_;
    n = (int)(A.size());
    B = B_size == -1 ? sqrt(n) : B_size;
    init();
  }
  int get_end_from_start(int bucket_start) const {
    return bucket_start + B < n ? bucket_start + B : n;
  }
  int get_start_from_index(int idx) const {
    return idx - idx % B;
  }
  int get_end_from_index(int idx) const {
    return get_end_from_start(get_start_from_index(idx));
  }
  T op(const T &x, const T &y) const {
    return x+y;
  }
  void init(){
    has_init = true;
    UNIT=0;
    for (int i = 0, j = 0; i < n; i += B, j++) {
      ;
    }
  }
  T get_part(int l, int r) {
    
  }
  T get_all(int l, int r) {
  }
  void update_part(int l, int r, S x) {
    
  }
  void update_all(int l, int r, S x) {

  }
  void prod(int l, int r, S val) {
    if (!has_init) init();
    int x = l / B, y = (r - 1) / B;
    if (x == y) {
      update_part(l, r, val);
    } else {
      update_part(l, x * B + B, val);
      for (int i = x + 1; i < y; ++i) 
        update_all(i * B, i * B + B, val);
      update_part(y * B, r, val);
    }
  }
  T get(int l, int r) {
    if (!has_init) init();
    int x = l / B, y = (r - 1) / B;
    T res = UNIT;
    if (x == y) {
      res = op(res, get_part(l, r));
    } else {
      res = op(res, get_part(l, x * B + B));
      for (int i = x + 1; i < y; ++i) 
        res = op(res, get_all(i * B, i * B + B));
      res = op(res, get_part(y * B, r));
    }
    return res;
  }
};
// SqrtDecomposition<450> sd(n); 

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    

    return 0;
}
