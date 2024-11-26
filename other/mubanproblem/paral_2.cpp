#include <bits/stdc++.h>
using namespace std;
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2563

using ll = long long;

template<typename ...Ts>
decltype(auto) zip(vector<Ts>... args){
  vector<decltype(make_tuple(args[0]...))> res;
  int n=min({args.size()...});
  res.reserve(n);
  for(int i=0;i<n;i++) res.emplace_back(args[i]...);
  return res;
}


template <class S,           // 线段树维护的数据信息
          S (*op)(S, S),    // 左右子节点信息合并到当前节点
          S (*e)(),
          class F,          // 懒标记维护的信息
          S (*tag)(F, S),  // 查询时给当去节点打上懒标记
          F (*merge)(F, F),  // 懒标记合并
          F (*id)()>        // 懒标记的默认值, 用于清空父节点的懒标记
struct LazySegTree {
    int n, size, log;
    vector<S> d;
    vector<F> lz;
    void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void push_down(int k, F f) {
        d[k] = tag(f, d[k]);
        if (k < size) lz[k] = merge(f, lz[k]);
    }
    void push(int k) {
        push_down(2 * k, lz[k]), push_down(2 * k + 1, lz[k]);
        lz[k] = id();
    }
    LazySegTree() : LazySegTree(0) {}
    explicit LazySegTree(int N) : LazySegTree(vector<S>(N, e())) {}
    explicit LazySegTree(const vector<S>& v) : n(int(v.size())) {
        log = ceil_lg(n), size = 1 << log;
        d = vector<S>(2 * size, e()), lz = vector<F>(size, id());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) pull(i);
    }
    int ceil_lg(int x) {   // minimum non-neg x s.t. `n <= 2^x`
        return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);
    }
    void set(int p, S x) {   // 0 <= p < n
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) pull(p >> i);
    }
    S get(int p) {     // Assert 0 <= p < n
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
    S get(int l, int r) {   // op(a[l], ..., a[r - 1])
        if (l == r) return e();
        l += size, r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sl = e(), sr = e();
        while (l < r) {
            if (l & 1) sl = op(sl, d[l++]);
            if (r & 1) sr = op(d[--r], sr);
            l >>= 1, r >>= 1;
        }
        return op(sl, sr);
    }
    S get_all() { return d[1]; }
    void apply(int p, F f) {   // 0 <= p < n
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = tag(f, d[p]);
        for (int i = 1; i <= log; i++) pull(p >> i);
    }
    void apply(int l, int r, F f) {  // a[i] = f(a[i]), [l, r)
        if (l == r) return;
        l += size, r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        int l2 = l, r2 = r;
        while (l < r) {
            if (l & 1) push_down(l++, f);
            if (r & 1) push_down(--r, f);
            l >>= 1, r >>= 1;
        }
        l = l2, r = r2;
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) pull(l >> i);
            if (((r >> i) << i) != r) pull((r - 1) >> i);
        }
    }
    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) { // 0 <= l <= n, g(e()) is true
        if (l == n) return n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) sm = op(sm, d[l]), l++;
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) { // 0 <= r <= n, g(e()) is true
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm)))  sm = op(d[r], sm), r--;
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
};
/*
using P = pair<ll, int>;
auto f=[&](P a,P b){return P(a.first+b.first,a.second+b.second);};
auto g=[&](P a,int b){return P(a.first+(ll)b*a.second,a.second);};
auto h=[&](int a,int b){return a+b;};
SegmentTree<P, int> seg(f,g,h,P(0,0),0);
*/
using S = pair<ll, int>;
using F = long long;
S op(S x, S y) {
    S s;
    s = S{x.first+y.first,x.second+y.second};
    return s;
}
S e() {
    return S();
};
S tag(F f, S s) { return S{s.first + f * s.second, s.second}; }
F merge(F x, F y) { return x + y; }
F id() { return 0; }
// 


void wt(vector<int> &v){
	for(auto&x:v)cout<<x<<' ';cout<<'\n';
}

vector<int> parallel_binary_search(int n,int q,
                                   function<void(void)> init,
                                   function<void(int)> apply,
                                   function<bool(int)> check){
  vector< vector<int> > C(q);
  vector<int> L(n,-1),R(n,q);
  bool flg=1;
  while(flg){
    flg=0;
    init();
    for(int i=0;i<n;i++)
      if(L[i]+1<R[i]) C[(L[i]+R[i])>>1].emplace_back(i);
    for(int i=0;i<q;i++){
      flg|=!C[i].empty();
      apply(i);
      for(int j:C[i]){
        if(check(j)) R[j]=i;
        else L[j]=i;
      }
      C[i].clear();
    }
  }
  return R;
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


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> a{0,1000000007};
    vector<int> as(m), bs(m), vs(m);
    for (int i = 0; i < m; ++i) {
        cin >> as[i] >> bs[i] >> vs[i];
        as[i]--;
        a.push_back(as[i]);
        a.push_back(bs[i]);
    }

    auto vt=zip(vs,as,bs);

 
    sort(vt.begin(),vt.end());
    for(int i=0;i<m;i++) 
    	tie(vs[i],as[i],bs[i])=vt[i];


    vector<int> xs(q),ys(q);
    vector<ll> js(q);
    for(int i=0;i<q;i++){
        cin>>xs[i]>>ys[i]>>js[i],xs[i]--;
        a.push_back(xs[i]);
        a.push_back(ys[i]);
    }

    Discrete<int> v(a);
    const auto &ps=v.xs;

	vector<S> vp(ps.size()-1);
	for(int i=0;i+1<(int)ps.size();i++) vp[i]=S(0,ps[i+1]-ps[i]);
	LazySegTree<S, op, e, F, tag, merge, id> seg(vp.size());

	for(int &a:as) a=v(a);
	for(int &b:bs) b=v(b);
	for(int &x:xs) x=v(x);
	for(int &y:ys) y=v(y);

	auto init=[&](){
		for(int i=0;i<vp.size();++i){
			seg.set(i,vp[i]);
		}
	};
	auto apply=[&](int i){
		seg.apply(as[i],bs[i],1);
	};
	auto check=[&](int i){
	return seg.get(xs[i],ys[i]).first>=js[i];
	};


	auto ans=parallel_binary_search(q,m,init,apply,check);
	for(int i=0;i<q;i++) cout<<vs[ans[i]]<<"\n";

    return 0;
}