#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

#if __cplusplus >= 201703L
#define CHK(t) if constexpr (t)
#else
#define CHK(t) if (t)
#endif
template <typename T, bool auto_extend = false>
struct ObjPool {
    using val_type = T;
    using val_ptr = T*;
    template<bool B, class U, class F > using cand_t = typename conditional<B,U,F>::type;
    template <typename U> using container_type = cand_t<auto_extend, deque<U>, vector<U>>;
    container_type<val_type> pool;
    container_type<val_ptr> buff;
    decltype(buff.begin()) it;
    ObjPool() : ObjPool(0) {}
    ObjPool(int siz) : pool(siz), buff(siz) { clear();}
    int capacity() const { return pool.size(); }
    int size() const { return it - buff.begin(); }
    val_ptr alloc() { CHK(auto_extend) ensure(); return *it++;}
    void free(val_ptr t) { *--it = t;}
    void clear() {
        int siz = pool.size(); it = buff.begin();
        for (int i = 0; i < siz; i++) buff[i] = &pool[i];
    }
    void ensure() {
        if (it != buff.end()) return;
        int siz = buff.size();
        for (int i = siz; i <= siz * 2; ++i) buff.push_back(&pool.emplace_back());
        it = buff.begin() + siz;
    }
};
template <typename T, T(*op)(T, T), T(*e)()>
struct PersistentSegTree {
    struct Node;
    using val_type = T;
    using node_type = Node;
    using node_ptr = node_type*;
    struct Node {
        static inline ObjPool<node_type> _pool;
        node_ptr _ch[2]{ nullptr, nullptr };
        val_type _dat;
        Node() : _dat(e()) {}
        static node_ptr clone(node_ptr node) { return &(*_pool.alloc() = *node);}
        static void upd(node_ptr node) { node->_dat = op(node->_ch[0]->_dat, node->_ch[1]->_dat);}
        static bool is_leaf(node_ptr node) { return not node->_ch[0];}
        static node_ptr build(const std::vector<val_type>& dat) {
            function<node_ptr(int, int)> dfs = [&](int l, int r) {
                node_ptr res = _pool.alloc();
                if (r - l == 1) res->_dat = dat[l];
                else {
                    int m = (l + r) >> 1;
                    res->_ch[0] = dfs(l, m), res->_ch[1] = dfs(m, r);
                    upd(res);
                }
                return res;
            };                
            return dfs(0, dat.size());
        }
        static val_type get_all(node_ptr node) { return node ? node->_dat : e();}
        static val_type get(node_ptr node, int tl, int tr, int ql, int qr) {
            if (tr <= ql or qr <= tl) return e();
            if (ql <= tl and tr <= qr) return node->_dat;
            int tm = (tl + tr) >> 1;
            return op(get(node->_ch[0], tl, tm, ql, qr), get(node->_ch[1], tm, tr, ql, qr));
        }
        template <bool do_upd, typename F>
        static node_ptr search_node(node_ptr node, int siz, int i, F &&f) {
            static vector<node_ptr> path;
            node_ptr res = node;
            CHK(do_upd) res = clone(res);
            node_ptr cur = res;
            for (int l = 0, r = siz; r - l > 1;) {
                CHK(do_upd) path.push_back(cur);
                int m = (l + r) >> 1;
                if (i < m) {
                    CHK(do_upd) cur->_ch[0] = clone(cur->_ch[0]);
                    cur = cur->_ch[0], r = m;
                } else {
                    CHK(do_upd) cur->_ch[1] = clone(cur->_ch[1]);
                    cur = cur->_ch[1], l = m;
                }
            }
            f(cur);
            CHK(do_upd) {
                while (path.size()) upd(path.back()), path.pop_back();
                return res;
            } else return nullptr;
        }
        static val_type get(node_ptr node, int siz, int i) {
            val_type res;
            search_node</*do_upd =*/false>(node, siz, i, [&](node_ptr i_th_node) { res = i_th_node->_dat; });
            return res;
        }
        template <typename F>
        static node_ptr apply(node_ptr node, int siz, int i, F&& f) {
            return search_node</* do_upd = */true>(node, siz, i, [&](node_ptr i_th_node) { i_th_node->_dat = f(i_th_node->_dat); });
        }
        static node_ptr set(node_ptr node, int siz, int i, const val_type& dat) {
            return apply(node, siz, i, [&](const val_type&) { return dat; });
        }
        template <typename F>
        static int max_right(node_ptr node, int siz, int l, F&& f) {
            assert(f(e()));
            function<int(node_ptr, int, int, val_type)> dfs = [&](node_ptr cur, int tl, int tr, val_type& sum) {
                if (tr <= l) return tr;
                if (l <= tl) {
                    val_type nxt_sum = op(sum, cur->_dat);
                    if (f(nxt_sum)) {
                        sum = std::move(nxt_sum);
                        return tr;
                    }
                    if (tr - tl == 1) return tl;
                }
                int tm = (tl + tr) >> 1;
                int res_l = dfs(cur->_ch[0], tl, tm, sum);
                return res_l != tm ? res_l : dfs(cur->_ch[1], tm, tr, sum);
            };
            val_type sum = e();
            return dfs(node, 0, siz, sum);
        }
        template <typename F>
        static int min_left(node_ptr node, int siz, int r, F&& f) {
            assert(f(e()));
            function<int(node_ptr, int, int, val_type)> dfs = [&](node_ptr cur, int tl, int tr, val_type& sum) {
                if (r <= tl) return tl;
                if (tr <= r) {
                    val_type nxt_sum = op(cur->_dat, sum);
                    if (f(nxt_sum)) {
                        sum = move(nxt_sum);
                        return tl;
                    }
                    if (tr - tl == 1) return tr;
                }
                int tm = (tl + tr) >> 1;
                int res_r = dfs(cur->_ch[1], tm, tr, sum);
                return res_r != tm ? res_r : dfs(cur->_ch[0], tl, tm, sum);
            };
            val_type sum = e();
            return dfs(node, 0, siz, sum);
        }
        template <typename OutputIter>
        static void dump(node_ptr node, OutputIter it) {
            if (not node) return;
            function<void(node_ptr)> dfs = [&](node_ptr cur) {
                if (is_leaf(cur)) *it++ = cur->_dat;
                else dfs(cur->_ch[0]), dfs(cur->_ch[1]);
            };
            dfs(node);
        }
        static std::vector<val_type> dump(node_ptr node) {
            vector<val_type> res;
            dump(node, std::back_inserter(res));
            return res;
        }
    };
    PersistentSegTree() : _n(0), _root(nullptr) {}
    explicit PersistentSegTree(int n) : PersistentSegTree(vector<val_type>(n, e())) {}
    PersistentSegTree(const vector<val_type>& dat) : _n(dat.size()), _root(node_type::build(dat)) {}
    static void init_pool(int siz) { node_type::_pool = ObjPool<node_type>(siz);}
    static void clear_pool() { node_type::_pool.clear();}
    val_type get_all() { return node_type::get_all(_root);}
    val_type get(int l, int r) { // a[l,..r-1]
        assert(0 <= l and l <= r and r <= _n);
        return node_type::get(_root, 0, _n, l, r);
    }
    val_type operator()(int l, int r) { return get(l, r);}
    val_type get(int i) { assert(0 <= i and i < _n); return node_type::get(_root, _n, i);}
    val_type operator[](int i) { return get(i);}
    template <typename F>
    PersistentSegTree apply(int i, F&& f) { assert(0 <= i and i < _n);
        return PersistentSegTree(_n, node_type::apply(_root, _n, i, std::forward<F>(f)));
    }
    PersistentSegTree set(int i, const val_type& v) { assert(0 <= i and i < _n);
        return PersistentSegTree(_n, node_type::set(_root, _n, i, v));
    }
    template <typename F> int max_right(int l, F&& f) { assert(0 <= l and l <= _n);
        return node_type::max_right(_root, _n, l, std::forward<F>(f));
    }
    template <bool(*pred)(val_type)> static int max_right(int l) { return max_right(l, pred);}
    template <typename F> int min_left(int r, F&& f) { assert(0 <= r and r <= _n);
        return node_type::min_left(_root, _n, r, std::forward<F>(f));
    }
    template <bool(*pred)(val_type)> static int min_left(int r) { return min_left(r, pred);}
    template <typename OutputIter>
    void dump(OutputIter it) { node_type::dump(_root, it);}
    vector<val_type> dump() { return node_type::dump(_root);}
private:
    int _n;
    node_ptr _root;
    PersistentSegTree(int n, node_ptr root) : _n(n), _root(root) {}
};
using S = int;
S op(S x, S y) {
    return x + y;
}
S e() {
    return 0;
}
using Seg = PersistentSegTree<S, op, e>;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    Seg::init_pool(3600000); // 初始化存储
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    auto b = a;
    vector<vector<int>> qs(m);
    char op;
    for (int i = 0; i < m; ++i) {
    	cin >> op;
    	if (op == 'C') {
    		int x, v;
    		cin >> x >> v;
    		qs[i] = {x, v};
    	} else {
    		int l, r, k;
    		cin >> l >> r >> k;
    		b.push_back(k);
    		qs[i] = {l, r, k};
    	}
    }
    Discrete<int> v(b);

    int m1 = v.size();

    vector<Seg> segs(m1);
    segs[0] = Seg(n);

    for (int i = 1; i < m1; ++i) {
    	segs[i] = segs[i - 1];
    }
    for (int i = 0; i < n; ++i) {
    	a[i] = v(a[i]);
    	segs[a[i]] = segs[a[i]].apply(i, [](int e){return e + 1;});
    }
    for (int i = 0; i < m; ++i) {
    	if (qs[i].size() == 2) {
    		int p = qs[i][0] - 1, val = qs[i][1];
    		int x = v(val);

    		segs[a[p]] = segs[a[p]].apply(p, [](int e){return e - 1;});
    		segs[x] = segs[x].apply(p, [](int e){return e + 1;});

    		a[p] = x;

    	} else {
    		int l = qs[i][0] - 1, r = qs[i][1], x = v(qs[i][2]);
    		cout << segs[x].get(l, r) << '\n';
    	}
    }

    return 0;
}