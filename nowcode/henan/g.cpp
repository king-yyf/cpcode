#include <iostream>
using namespace std;
int n, a[100005], d[270000], b[270000];
const long long mod=1e9+7;

long long  qpow(long long m, long long k, long long p) {

  if(m==1) return 1;
  if(k==1) return m%p;
    long long res = 1, t = m;
    while (k) {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

void build(int l, int r, int p) {  // 建树
  if (l == r) {
    d[p] = a[l];
    return;
  }
  int m = l + ((r - l) >> 1);
  build(l, m, p << 1), build(m + 1, r, (p << 1) | 1);
  d[p] = (1ll * d[p << 1] * d[(p << 1) | 1])%mod;
}

void update(int l, int r, int c, int s, int t,
            int p) {  // 更新，可以参考前面两个例题
  if (l <= s && t <= r) {
    // d[p] = (t - s + 1) * c;
    d[p]=qpow(c,t-s+1,mod);
    b[p] = c;
    return;
  }
  int m = s + ((t - s) >> 1);
  if (b[p]) {
    d[p << 1] = qpow(b[p],m-s+1,mod), d[(p << 1) | 1] = qpow(b[p],t-m,mod);
    b[p << 1] = b[(p << 1) | 1] = b[p];
    b[p] = 0;
  }
  if (l <= m) update(l, r, c, s, m, p << 1);
  if (r > m) update(l, r, c, m + 1, t, (p << 1) | 1);
  d[p] = (1ll * d[p << 1] * d[(p << 1) | 1])%mod;
}

int getsum(int l, int r, int s, int t, int p) {  // 取得答案，和前面一样
  if (l <= s && t <= r) return d[p];
  int m = s + ((t - s) >> 1);
  if (b[p]) {
    d[p << 1] = qpow(b[p],m-s+1,mod), d[(p << 1) | 1] = qpow(b[p],t-m,mod);
    b[p << 1] = b[(p << 1) | 1] = b[p];
    b[p] = 0;
  }
  long long sum = 0;
  if (l <= m) sum = getsum(l, r, s, m, p << 1);
  if (r > m) sum = (sum * 1ll * getsum(l, r, m + 1, t, (p << 1) | 1))%mod;
  return sum;
}

int main() {
  std::ios::sync_with_stdio(0);

  int q;
  cin>>q;
  n=q;
  

  for(int i=0;i<=n;++i) a[i]=1;
    build(1, n, 1);
  
  for(int i=1;i<=q;++i){
    int op;cin>>op;
    if(op==1){
      int xx;
      cin>>xx;
      update(i,i,xx,1,n,1);
    }else if(op==2){
      int l,r;
      cin>>l>>r;
      update(l,r,1,1,n,1);
    }else{
      long long s=getsum(1, i, 1, n, 1);
      cout<<s<<"\n";
    }
  }
  return 0;
}