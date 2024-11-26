#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
link:https://yukicoder.me/problems/no/1234
长度为n的数目，q次操作，两种类型
1. a[l,r]的元素 +x
2. 求 a[l,r]区间最小值
*/

template<int B_size = -1>
struct SqrtDecomposition{
  using S = long long; // 待分块数据类型
  using T = long long; // 答案数据类型
  vector<S> A;
  vector<long long> lazy, mns;
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
    return min(x,y);
  }
  void init(){
    has_init = true;
    UNIT=1e18;
    int m=(n+B-1)/B;
    lazy.assign(m, 0);
    mns.resize(m);
    for (int i = 0, j = 0; i < n; i += B, j++) {
    	mns[j] = *min_element(A.begin() + i, A.begin() + get_end_from_start(i));
    }
  }
  T get_part(int l, int r) {
    T res = 1e18;
    int b = l / B;
    for(int i=l;i<r;++i){
    	if(A[i]+lazy[b]<res) res=A[i]+lazy[b];
    }
    return res;
  }
  T get_all(int l, int r) {
    return mns[l/B];
  }
  void update_part(int l, int r, S x) {
    int b = l / B;
  	for (int i = l; i < r; ++i) {
  		A[i] += x;
  	}
  	mns[b] = 1e18;
  	for (int i = get_start_from_index(l); i < get_end_from_index(l); ++i) {
  		mns[b] = min(mns[b], A[i] + lazy[b]);
  	}
  }
  void update_all(int l, int r, S x) {
  	lazy[l / B] += x;
  	mns[l / B] += x;
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

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n;
    SqrtDecomposition<350> s(n);
    for (auto &x : s.A){
    	cin >> x;
    }
    s.init();
    cin >> q;
    for (int _i = 0; _i < q; ++_i) {
    	int k, l, r, c;
    	cin >> k >> l >> r >> c;
    	l--;
    	if (k == 1) {
    		s.prod(l, r, c);
    	} else {
    		cout << s.get(l, r) << '\n';    		
    	}
    }

    return 0;
}

