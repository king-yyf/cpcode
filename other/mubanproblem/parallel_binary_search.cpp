#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2563

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

template<typename F, typename G, typename CHK> 
vector<int> paral_bs(int n, int q, F &&init, G &&apply,CHK &&check){
    vector<vector<int>> a(q);
    vector<int> l(n, -1), r(n, q);
    bool ok = 1;
    while (ok) {
    	ok = 0;
    	init();
    	for (int i = 0; i < n; ++i) if (l[i] + 1 < r[i])
    		a[(l[i] + r[i]) >> 1].push_back(i);
    	for (int i = 0; i < q; ++i) {
    		ok |= !a[i].empty();
    		apply(i);
    		for (int j : a[i]) {
    			if (check(j)) r[j] = i;
    			else l[j] = i;
    		}
    		a[i].clear();
    	}
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> a {0,1000000007};
    vector<array<int ,3>> op1(m);
    vector<array<int ,2>> op2(q);
    vector<long long> qs(q);
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < 3; ++j) {
        	cin >> op1[i][j];
        }
        op1[i][0]--;
        a.push_back(op1[i][0]);
        a.push_back(op1[i][1]);
    }

    sort(op1.begin(), op1.end(), [&](auto &x, auto &y){
    	return x[2] < y[2];
    });

    for (int i = 0; i < q; ++i) {
        cin >> op2[i][0] >> op2[i][1] >> qs[i];
        op2[i][0]--;
        a.push_back(op2[i][0]);
        a.push_back(op2[i][1]);
    }

    Discrete<int> v(a);
    
	vector<S> vp(v.size() - 1);
	for (int i = 0; i < v.size() - 1; ++i) {
		vp[i] = S{0, v[i + 1] - v[i]};
	}
	LazySegTree<S, op, e, F, tag, merge, id> seg(vp.size());

	for (int i = 0; i < m; ++i) {
		op1[i][0] = v(op1[i][0]);
		op1[i][1] = v(op1[i][1]);
	}
	for (int i = 0; i < q; ++i) {
		op2[i][0] = v(op2[i][0]);
		op2[i][1] = v(op2[i][1]);
	}

	auto init = [&](){
		for(int i = 0;i < vp.size(); ++i){
			seg.set(i, vp[i]);
		}
	};
	auto apply = [&](int i){
		seg.apply(op1[i][0], op1[i][1], 1);
	};
	auto chk = [&](int i){
		return seg.get(op2[i][0], op2[i][1]).first >= qs[i];
	};

	auto ans=paral_bs(q, m, init, apply, chk);
	
	for(int i = 0; i < q; i++) 
		cout << op1[ans[i]][2] << '\n';

    return 0;
}
