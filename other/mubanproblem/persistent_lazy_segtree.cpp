#include <bits/stdc++.h>
using namespace std;

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
template <class T, T(*op)(T, T), T(*e)(), class F, T(*tag)(F, T), F(*merge)(F, F), F(*id)()>
struct PersisLazySegTree {
    struct Node;
    using val_type = T;
    using op_type = F;
    using node_type = Node;
    using node_ptr = node_type*;
    struct Node {
        static inline ObjPool<node_type> _pool;
        node_ptr _ch[2]{ nullptr, nullptr };
        val_type _dat;
        op_type _laz;
        Node() : _dat(e()), _laz(id()) {}
        static node_ptr clone(node_ptr node) { return &(*_pool.alloc() = *node);}
        static void upd(node_ptr node) {node->_dat = op(node->_ch[0]->_dat, node->_ch[1]->_dat);}
        template <bool do_clone = true>
        static node_ptr push(node_ptr node) {
            node_ptr res = node;
            CHK(do_clone) res = clone(res);
            res->_ch[0] = apply_all(res->_ch[0], res->_laz);
            res->_ch[1] = apply_all(res->_ch[1], res->_laz);
            res->_laz = id();
            CHK(do_clone) return res;
            return nullptr;
        }
        static bool is_leaf(node_ptr node) { return not node->_ch[0];}
        static node_ptr build(const std::vector<val_type>& dat) {
            function<node_ptr(int, int)> dfs = [&](int l, int r) {
                node_ptr res = _pool.alloc();
                if (r - l == 1) {
                    res->_dat = dat[l]; res->_laz = id();
                } else {
                    int m = (l + r) >> 1;
                    res->_ch[0] = dfs(l, m), res->_ch[1] = dfs(m, r);
                    upd(res);
                    res->_laz = id();
                }
                return res;
            };
            return dfs(0, dat.size());
        }
        static val_type get_all(node_ptr node) { return node ? node->_dat : e();}
        static val_type get(node_ptr node, int tl, int tr, int ql, int qr, const op_type &f = id()) {
            if (tr <= ql or qr <= tl) return e();
            if (ql <= tl and tr <= qr) return tag(f, node->_dat);
            int tm = (tl + tr) >> 1;
            op_type g = merge(f, node->_laz);
            return op(get(node->_ch[0], tl, tm, ql, qr, g), get(node->_ch[1], tm, tr, ql, qr, g));
        }
        static node_ptr apply_all(node_ptr node, const op_type &f) {
            if (not node) return nullptr;
            node_ptr res = clone(node);
            res->_dat = tag(f, res->_dat); res->_laz = merge(f, res->_laz);
            return res;
        }
        static node_ptr apply(node_ptr node, int tl, int tr, int ql, int qr, const op_type &f) {
            if (tr <= ql or qr <= tl) return node;
            if (ql <= tl and tr <= qr) return apply_all(node, f);
            node_ptr res = push(node);
            int tm = (tl + tr) >> 1;
            res->_ch[0] = apply(res->_ch[0], tl, tm, ql, qr, f);
            res->_ch[1] = apply(res->_ch[1], tm, tr, ql, qr, f);
            upd(res);
            return res;
        }
        template <typename Func>
        static node_ptr upd_leaf(node_ptr node, int siz, int i, Func &&f) {
            static vector<node_ptr> path;
            node_ptr res = clone(node);
            node_ptr cur = res;
            for (int l = 0, r = siz; r - l > 1;) {
                path.push_back(cur);
                push</*do_clone = */false>(cur);
                int m = (l + r) >> 1;
                if (i < m) {
                    cur = cur->_ch[0]; r = m;
                } else {
                    cur = cur->_ch[1]; l = m;
                }
            }
            cur->_dat = f(cur->_dat);
            while (path.size()) upd(path.back()), path.pop_back();
            return res;
        }
        static val_type get(node_ptr node, int siz, int i) {
            op_type f = id();
            node_ptr cur = node;
            for (int l = 0, r = siz; r - l > 1;) {
                f = merge(f, cur->_laz);
                int m = (l + r) >> 1;
                if (i < m) {
                    cur = cur->_ch[0]; r = m;
                } else {
                    cur = cur->_ch[1]; l = m;
                }
            }
            return tag(f, cur->_dat);
        }
        template <typename Func>
        static node_ptr apply(node_ptr node, int siz, int i, Func&& f) {
            return upd_leaf(node, siz, i, [&](const val_type &v) { return f(v); });
        }
        static node_ptr set(node_ptr node, int siz, int i, const val_type& dat) {
            return apply(node, siz, i, [&](const val_type&) { return dat; });
        }
        template <typename G>
        static int max_right(node_ptr node, int siz, int l, G&& g) {
            assert(g(e()));
            function<int(node_ptr, int, int, val_type, op_type)> 
            dfs = [&](node_ptr cur, int tl, int tr, val_type& sum, const op_type &f) {
                if (tr <= l) return tr;
                if (l <= tl) {
                    val_type nxt_sum = op(sum, tag(f, cur->_dat));
                    if (g(nxt_sum)) {
                        sum = move(nxt_sum); return tr;
                    }
                    if (tr - tl == 1) return tl;
                }
                int tm = (tl + tr) >> 1;
                op_type g = merge(f, cur->_laz);
                int res_l = dfs(cur->_ch[0], tl, tm, sum, g);
                return res_l != tm ? res_l : dfs(cur->_ch[1], tm, tr, sum, g);
            };
            val_type sum = e();
            return dfs(node, 0, siz, sum, id());
        }
        template <typename G>
        static int min_left(node_ptr node, int siz, int r, G&& g) {
            assert(g(e()));
            function<void(node_ptr, int, int, val_type, op_type)> 
            dfs = [&](node_ptr cur, int tl, int tr, val_type& sum, const op_type &f) {
                if (r <= tl) return tl;
                if (tr <= r) {
                    val_type nxt_sum = op(tag(f, cur->_dat), sum);
                    if (g(nxt_sum)) {
                        sum = move(nxt_sum); return tl;
                    }
                    if (tr - tl == 1) return tr;
                }
                int tm = (tl + tr) >> 1;
                op_type g = merge(f, cur->_laz);
                int res_r = dfs(cur->_ch[1], tm, tr, sum, g);
                return res_r != tm ? res_r : dfs(cur->_ch[0], tl, tm, sum, g);
            };
            val_type sum = e();
            return dfs(node, 0, siz, sum, id());
        }
        template <typename OutputIter>
        static void dump(node_ptr node, OutputIter it) {
            if (not node) return;
            function<void(node_ptr, op_type)> dfs = [&](node_ptr cur, const op_type &f) {
                if (is_leaf(cur)) {
                    *it++ = tag(f, cur->_dat);
                } else {
                    *it++ = tag(f, cur->_dat);
                    dfs(cur->_ch[0], merge(cur->_laz, f)), dfs(cur->_ch[1], merge(cur->_laz, f));
                }
            };
            dfs(node, id());
        }
        static vector<val_type> dump(node_ptr node) {
            vector<val_type> res;
            dump(node, std::back_inserter(res));
            return res;
        }
    };
    PersisLazySegTree() : _n(0), _root(nullptr) {}
    explicit PersisLazySegTree(int n) : PersisLazySegTree(std::vector<val_type>(n, e())) {}
    PersisLazySegTree(const vector<val_type>& dat) : _n(dat.size()), _root(node_type::build(dat)) {}
    static void init_pool(int siz) { node_type::_pool = ObjPool<node_type>(siz);}
    static void clear_pool() { node_type::_pool.clear();}
    val_type get_all() { return node_type::get_all(_root);}
    val_type get(int l, int r) { assert(0 <= l and l <= r and r <= _n); return node_type::get(_root, 0, _n, l, r);}
    val_type operator()(int l, int r) { return get(l, r);}
    PersisLazySegTree apply_all(const op_type &f) { return PersisLazySegTree(_n, node_type::apply_all(_root, f));}
    PersisLazySegTree apply(int l, int r, const op_type &f) {
        return PersisLazySegTree(_n, node_type::apply(_root, 0, _n, l, r, f));
    }
    val_type get(int i) { assert(0 <= i and i < _n); return node_type::get(_root, _n, i);}
    val_type operator[](int i) { return get(i);}
    template <typename Func>
    PersisLazySegTree apply(int i, Func&& f) {
        assert(0 <= i and i < _n);
        return PersisLazySegTree(_n, node_type::apply(_root, _n, i, std::forward<F>(f)));
    }
    PersisLazySegTree set(int i, const val_type& v) {
        assert(0 <= i and i < _n);
        return PersisLazySegTree(_n, node_type::set(_root, _n, i, v));
    }
    template <typename G>
    int max_right(int l, G&& g) {
        assert(0 <= l and l <= _n);
        return node_type::max_right(_root, _n, l, std::forward<G>(g));
    }
    template <bool(*g)(val_type)> static int max_right(int l) { return max_right(l, g);}
    template <typename G>
    int min_left(int r, G&& g) {
        assert(0 <= r and r <= _n);
        return node_type::min_left(_root, _n, r, std::forward<G>(g));
    }
    template <bool(*g)(val_type)> static int min_left(int r) { return min_left(r, g);}
    template <typename OutputIter>
    void dump(OutputIter it) { node_type::dump(_root, it);} 
    vector<val_type> dump() { return node_type::dump(_root);}
private:
    int _n;
    node_ptr _root;
    PersisLazySegTree(int n, node_ptr root) : _n(n), _root(root) {}
};
using S = long long;
using F = long long;
S op(S x, S) {
    return x;
}
S e() {
    return 0;
}
S tag(F f, S x) {
    return f + x;
}
F merge(F f, F g) {
    return f + g;
}
S id() {
    return 0;
}
using Seg = PersisLazySegTree<S, op, e, F, tag, merge, id>;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, q;
    std::cin >> n >> m >> q;
 
    vector<std::pair<int, int>> last(n);
 
    Seg::init_pool(15000000);
 
    std::vector<Seg> segs(q + 1);
    segs[0] = Seg(m + 1);
 
    for (int t = 1; t <= q; ++t) {
        int query_type;
        std::cin >> query_type;
        segs[t] = segs[t - 1];
        if (query_type == 1) {
            int l, r, x;
            std::cin >> l >> r >> x;
            --l;
            segs[t] = segs[t].apply(l, r, x);
        } else if (query_type == 2) {
            int i, x;
            std::cin >> i >> x;
            --i;
            last[i] = { t - 1, x };
        } else {
            int i, j;
            std::cin >> i >> j;
            --i, --j;
            auto [tl, x] = last[i];
            std::cout << x + segs[t - 1].get(j) - segs[tl].get(j) << '\n';
        }
    }
    
    return 0;
}