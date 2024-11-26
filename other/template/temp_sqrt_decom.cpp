#include <bits/stdc++.h>
using namespace std;

using ll = long long;


enum MergeType {
	SUM = 0, MIN = 1, MAX = 2,
	AND = 3, OR = 4, XOR = 5,
	MUL = 6, GCD = 7, LCM = 8
};
template<int B_size = -1, MergeType tp = MergeType::SUM>
struct SqrtDecomposition{
  using S = int; // 待分块数据类型
  using T = int; // 答案数据类型
  vector<S> A;
  int B; // 分块大小
  int n; // 数组长度
  T UNIT;
  bool has_init;
  T op(const T &x, const T &y) const {
  	switch (tp) {
	  	case SUM: return x + y;
	  	case MIN: return x < y ? x : y;
	    case MAX: return x > y ? x : y;
	    case AND: return (x & y);
	    case OR: return (x | y);
	    case XOR: return (x ^ y);
	    case MUL: return (x * y);
	    case GCD: return gcd(x, y);
	    case LCM: return lcm(x, y);
	    default: return x + y;
  	}
  	return UNIT;
  }
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
  void init(){
  	has_init = true;
  	if (tp == SUM || tp == OR || tp == XOR || tp == GCD) {
    	UNIT = T{0};
    } else if (tp == MIN) {
    	UNIT = numeric_limits<T>::max() / 2;
    } else if (tp == MAX) {
    	UNIT = numeric_limits<T>::min() / 2;
    } else if (tp == MUL || tp == LCM) {
    	UNIT = T{1};
    } else if (tp == AND) {
    	T max_value = numeric_limits<T>::max();
    	int mx_lg = 63 - __builtin_clzll(max_value);
    	UNIT = (1LL << mx_lg) - 1;
    }
    for (int i = 0, j = 0; i < n; i += B, j++) {
    	;
    }
  }
  T get_part(int l, int r) {
    T res = 0;
    return res;
  }
  T get_all(int l, int r) {
    T res;
    return res;
  }
  void update_part(int l, int r, S x) {

  }
  void update_all(int l, int r, S x) {

  }
  void prod(int l, int r, S val) {
  	if (!has_init) init();
    int x = l / B, y = r / B;
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
    int x = l / B, y = r / B;
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
// SqrtDecomposition<450, SUM> sd(n); 

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    vector<int> a{2,3};
    SqrtDecomposition<10, AND> s(2);
    s.A=a;
    s.init(); 

    // cout << log(s.UNIT) << ", " << log((int)(1e9));

    // cout << s.UNIT -1e9<< "\n";

    return 0;
}
