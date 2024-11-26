#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst ? (r=md-1):(l=md+1);} else fst ? (l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void dbg(A x) { cout<<x<<' ';}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
int n, m, q;
int x, y, k;
string s, t;

const int MXN = 2e6 + 2;
// int primes[MXN], prime_cnt; 
// bool st[MXN];
// int g[MXN], f[MXN]; //f[i]记录i的约数和
// void divs_sum(int n) {
//     g[1] = f[1] = 1;
//     for (int i = 2; i <= n; ++i) {
//         if (!st[i]) {
//             primes[prime_cnt++] = i;
//             g[i] = g[i] = i + 1;
//         }
//         for (int j = 0; primes[j] * 1ll * i <= n; j++) {
//             int t = primes[j] * i;
//             st[t] = true;
//             if (i % primes[j] == 0) {
//                 g[t] = g[i] * primes[j] + 1;
//                 f[t] = f[i] / g[i] * g[t];
//                 break;
//             } else g[t] = primes[j] + 1, f[t] = f[i] * g[t];
//         }
//     }
// }

const int N = 2e6+2;
int p1[N], vis[N], cnt;
//g[i]表示i的最小质因子的1+p^1+...+p^k
int g[N], f[N];//f[i]表示i的约数和

void get_f(int n){ //筛法求约数和
  g[1] = f[1] = 1;
  for(int i=2; i<=n; i++){
    if(!vis[i]){
      p1[++cnt] = i;
      g[i] = f[i] = i+1;
    }
    for(int j=1; i*p1[j]<=n; j++){
      int m = i*p1[j]; 
      vis[m] = 1;
      if(i%p1[j] == 0){
        g[m] = g[i]*p1[j]+1;
        f[m] = f[i]/g[i]*g[m];
        break;
      } 
      else{
        g[m] = p1[j]+1;
        f[m] = f[i]*g[m];
      }
    }
  }
}


template <class S, S (*op)(S, S), S (*e)()>
struct SegTree {
    int n, size, log;
    vector<S> d;
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<S>(n, e())) {}
    explicit SegTree(const vector<S> &v) : n(int(v.size())) {
        log = ceil_lg(n), size = 1 << log;
        d = vector<S>(2 * size, e());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) pull(i);
    }
    int ceil_lg(int x) {   // minimum non-neg x s.t. `n <= 2^x`
        return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);
    }
    void set(int p, S x) {  // assert(0 <= p < n)
        p += size, d[p] = x;
        for (int i = 1; i <= log; ++i) pull(p >> i);
    }
    S get(int p) const { return d[p + size];}
    S get(int l, int r) {   // [l, r)
        S sl = e(), sr = e();
        l += size, r += size;
        while (l < r) {
            if (l & 1) sl = op(sl, d[l++]);
            if (r & 1) sr = op(d[--r], sr);
            l >>= 1, r >>= 1;
        }
        return op(sl, sr);
    }
    S get_all() const {return d[1];}

    void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]);}
    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F>     // 0 <= l <= n, f(e()) is true
    int max_right(int l, F f) const { 
        if (l == n) return n;
        l += size;
        S x = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(x, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(x, d[l]))) {
                        x = op(x, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            x = op(x, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }
    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F>  // 0 <= r <= n, f(e()) is true
    int min_left(int r, F f) const {
        if (r == 0) return 0;
        r += size;
        S x = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], x))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], x))) {
                        x = op(d[r], x);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            x = op(d[r], x);
        } while ((r & -r) != r);
        return 0;
    }
};
using S = pair<int,ll> ;
S op(S x, S y) {
    return {x.first+y.first,x.second+y.second};
}
S e() {
    return S{};
}


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

vector<pair<int,int>> p[MXN];
int main() {
    get_f(MXN-2);
    int t,n,m;

    vector<int> v(MXN-2);
    for(int i=0;i<=2000000;++i){
        v[i]=f[i+1];
    }
    Discrete<int> d(v);
    int M=d.size();
    SegTree<S, op, e> seg(M);

    // f1(7)wt(f[i],' ');wt(nl);

    cin>>t;
    f0(t){
        cin>>n>>m;
        p[n].push_back({m,i});
    }
    vector<ll> ans(t);
    for(int i=1;i<=2000000;++i) {
        int pos=d(f[i]);
        auto [x,y]=seg.get(pos);
        seg.set(pos,{x+1,y+f[i]});
        if(!p[i].size()) continue;
        for(auto&[k,id]:p[i]) {
            int m=k;
            int r=seg.max_right(0,[&](S s){
                return s.first<=n-m;
            });
            int s1=seg.get(0,r).first;
            if(s1==n-m) {
                ans[id]=seg.get(r,M).second;
            }else{
                int d1=n-m-s1;
                auto [k,v]=seg.get(r);
                ans[id]=seg.get(r+1,M).second+v-d1*(v/k);
            }
        }
    }


    f0(t){
        wt(ans[i],nl);
    }
    return 0;
}
