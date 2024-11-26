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
template <typename T, int lg_ary = 4>
struct PersistentArr {
    struct Node;
    using node_type = Node;
    using node_ptr = node_type*;
    using val_type = T;
    using pool_type = ObjPool<node_type>;
    struct Node {
        static inline pool_type pool{};
        static const int mask = (1 << lg_ary) - 1;
        node_ptr _ch[1 << lg_ary]{};
        val_type _val;
        Node(const val_type& val = val_type{}) : _val(val) {}
        static node_ptr clone(node_ptr node) { return &(*pool.alloc() = *node);}
        static node_ptr new_node(const val_type& val) { return &(*pool.alloc() = node_type(val));}
        static val_type& get(node_ptr node, int id) {
            for (; id; --id >>= lg_ary) node = node->_ch[id & mask];
            return node->_val;
        }
        static node_ptr set(node_ptr node, int id, const val_type& val) {
            node_ptr res = clone(node), cur = res;
            for (; id; --id >>= lg_ary) cur = cur->_ch[id & mask] = clone(cur->_ch[id & mask]);
            cur->_val = val;
            return res;
        }
        static val_type mut_set(node_ptr node, int id, const val_type& val) {
            return exchange(get(node, id), val);
        }
        static node_ptr build(const vector<val_type>& init) {
            const int n = init.size();
            if (n == 0) return nullptr;
            function<void(node_ptr, int, int)> dfs = [&](node_ptr cur, int id, int p) {
                int np = p << lg_ary, nid = id + p;
                for (int d = 1; d < 1 << lg_ary; ++d, nid += p) {
                    if (nid < n) dfs(cur->_ch[d] = new_node(init[nid]), nid, np);
                    else return;
                }
                if (nid < n) dfs(cur->_ch[0] = new_node(init[nid]), nid, np);
            };
            node_ptr root = new_node(init[0]);
            dfs(root, 0, 1);
            return root;
        }
        static vector<val_type> dump(node_ptr node) {
            if (not node) return {};
            vector<val_type> res;
            function<void(node_ptr, int, int)> dfs = [&](node_ptr cur, int id, int p) {
                if (int(res.size()) <= id) res.resize(id + 1);
                res[id] = node->_val;
                int np = p << lg_ary, nid = id + p;
                for (int d = 1; d < 1 << lg_ary; ++d, nid += p) {
                    if (cur->_ch[d]) dfs(cur->_ch[d], nid, np);
                    else return;
                }
                if (cur->_ch[0]) dfs(cur->_ch[0], nid, np);
            };
            dfs(node, 0, 1);
            return res;
        }
    };
    static void init_pool(int capacity) { node_type::pool = pool_type(capacity);}
    PersistentArr() = default;
    explicit PersistentArr(int n, const val_type& val = val_type{}) : PersistentArr(vector<val_type>(n, val)) {}
    PersistentArr(const vector<val_type>& init) : _n(init.size()), _root(node_type::build(init)) {}

    int size() const { return _n; }
    const val_type& get(int id) { return node_type::get(_root, id); }
    PersistentArr set(int id, const val_type& new_val) { return PersistentArr{ _n, node_type::set(_root, id, new_val) }; }
    val_type mut_set(int id, const val_type& new_val) { return node_type::mut_set(_root, id, new_val);}
    PersistentArr clone() {
        if (not _root) return PersistentArr { _n, _root };
        return PersistentArr{ _n, node_type::clone(_root) };
    }
    vector<val_type> dump() { return node_type::dump(_root);}
private:
    int _n;
    node_ptr _root;
    explicit PersistentArr(int n, node_ptr root) : _n(n), _root(root) {}
};
using Arr = PersistentArr<int, 1>;

int main() {
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Arr::init_pool(20000000);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];    
    }
    vector<Arr> segs(m + 1);
    segs[0] = Arr(a);

    for (int i = 1; i <= m; ++i) {
        int v, t, pos, x;
        cin >> v >> t >> pos;
        pos--;
        if (t == 1) {
            cin >> x;
            segs[i] = segs[v].set(pos, x);
        } else {
            segs[i] = segs[v];
            cout << segs[v].get(pos) << '\n';
        }
       
    }
    return 0;
}