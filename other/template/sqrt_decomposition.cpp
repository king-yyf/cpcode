#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int V;

template<int B_size = -1>
struct SqrtDecomposition{
  using S = int; // 待分块数据类型
  using T = int; // 答案数据类型
  vector<S> A;
  vector<int> b;
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
    b=A;
    for (int i = 0, j = 0; i < n; i += B, j++) {
      sort(b.begin()+i, b.begin()+get_end_from_start(i));
    }
  }
  T get_part(int l, int r) {
    T res = 0;
    for(int i=l;i<r;++i){
      if(A[i]<=V){
        res++;
      }
    }
    return res;
  }
  T get_all(int l, int r) {
    return distance(b.begin()+l,upper_bound(b.begin()+l,b.begin()+r,V));
  }
  void update_part(int l, int r, S x) {
    int l1=get_start_from_index(l),r1=get_end_from_index(l);
    for(int i=l1; i<r1;++i){
      if(b[i]==A[l]){
        b[i]=x;
        while(i+1<r1&&b[i+1]<b[i]){
          swap(b[i],b[i+1]);i++;
        }
        while(i-1>=l1&&b[i-1]>b[i]){
          swap(b[i],b[i-1]);i--;
        }
        break;
      }
    }
    A[l]=x;
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
// SqrtDecomposition<450, SUM> sd(n); 


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin>>n>>q;

    SqrtDecomposition<500> s(n);
    for (int i = 0; i < n; ++i) {
      cin >> s.A[i];
    }

    s.init();

    for (int _ = 0; _ < q; ++_) {
      char type;
      cin>>type;
      if (type == 'M') {
        int i;
        cin>>i>>V;
        i--;
        s.prod(i, i + 1, V);
      } else {
        int l, r;
        cin>>l>>r>>V;
        l--;
        int ans=s.get(l,r);
        printf("%d\n", ans);
      }
    }

    return 0;
}
  