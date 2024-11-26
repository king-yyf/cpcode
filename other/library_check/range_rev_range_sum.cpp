// https://judge.yosupo.jp/problem/range_reverse_range_sum
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

namespace suisen {
    template <typename Object>
    struct ptr32 {
        static constexpr int null = -1;

        using object_type = Object;
        using pool_type = std::vector<object_type>;

        constexpr ptr32() : ptr(null) {}
        explicit constexpr ptr32(int ptr) : ptr(ptr) {}

        object_type& operator*() const { return pool[ptr]; }
        object_type* operator->() const { return &pool[ptr]; }

        constexpr operator bool() const { return ptr != null; }
        constexpr operator int() const { return ptr; }

        constexpr bool is_not_null() const { return bool(*this); }
        constexpr bool is_null() const { return not bool(*this); }

        friend constexpr bool operator==(const ptr32& l, const ptr32& r) { return l.ptr == r.ptr; }
        friend constexpr bool operator!=(const ptr32& l, const ptr32& r) { return l.ptr != r.ptr; }
        friend constexpr bool operator<(const ptr32& l, const ptr32& r) { return l.ptr < r.ptr; }
        friend constexpr bool operator<=(const ptr32& l, const ptr32& r) { return l.ptr <= r.ptr; }
        friend constexpr bool operator>(const ptr32& l, const ptr32& r) { return l.ptr > r.ptr; }
        friend constexpr bool operator>=(const ptr32& l, const ptr32& r) { return l.ptr >= r.ptr; }

        template <typename ...Args>
        static ptr32 alloc(Args &&...args) {
            if (del.size()) {
                ptr32 ptr(del.back());
                del.pop_back();
                *ptr = object_type(std::forward<Args>(args)...);
                return ptr;
            } else {
                ptr32 ptr(pool.size());
                pool.emplace_back(std::forward<Args>(args)...);
                return ptr;
            }
        }
        static void dealloc(ptr32 p) {
            del.push_back(p);
        }
        static void dealloc_all(bool shrink) {
            pool.clear(), del.clear();
            if (shrink) pool.shrink_to_fit(), del.shrink_to_fit();
        }
        static void reserve(size_t capacity) {
            pool.reserve(capacity);
        }
    private:
        static inline pool_type pool{};
        static inline std::vector<ptr32> del{};

        int ptr;
    };
} // namespace suisen

namespace suisen::internal::implicit_treap {
    template <typename T, typename Derived>
    struct ReversibleNode {
        using random_engine = std::mt19937;
        static inline random_engine rng{ std::random_device{}() };

        using priority_type = uint32_t;

        static priority_type random_priority() {
            return rng();
        }

        using node_type = Derived;
        using node_pointer = ptr32<node_type>;

        using size_type = uint32_t;

        using difference_type = int32_t;
        using value_type = T;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using reference = value_type&;
        using const_reference = const value_type&;

        node_pointer _ch[2]{ node_pointer{}, node_pointer{} };
        value_type _val;
        size_type _size;
        priority_type _priority;

        bool _rev = false;

        ReversibleNode(const value_type val = {}): _val(val), _size(1), _priority(random_priority()) {}

        static void reserve(size_type capacity) { node_pointer::reserve(capacity); }

        static value_type& value(node_pointer t) { return t->_val; }
        static value_type set_value(node_pointer t, const value_type& new_val) { return std::exchange(value(t), new_val); }

        static constexpr bool empty(node_pointer t) { return not t; }
        static size_type& size(node_pointer t) { return t->_size; }
        static size_type safe_size(node_pointer t) { return t ? t->_size : 0; }

        static priority_type& priority(node_pointer t) { return t->_priority; }
        static void set_priority(node_pointer t, priority_type new_priority) { priority(t) = new_priority; }

        static node_pointer& child0(node_pointer t) { return t->_ch[0]; }
        static node_pointer& child1(node_pointer t) { return t->_ch[1]; }
        static node_pointer& child(node_pointer t, bool b) { return t->_ch[b]; }
        static node_pointer set_child0(node_pointer t, node_pointer cid) { return std::exchange(child0(t), cid); }
        static node_pointer set_child1(node_pointer t, node_pointer cid) { return std::exchange(child1(t), cid); }
        static node_pointer set_child(node_pointer t, bool b, node_pointer cid) { return std::exchange(child(t, b), cid); }

        static bool& reversed(node_pointer t) { return t->_rev; }

        static node_pointer update(node_pointer t) { // t : not null
            size(t) = safe_size(child0(t)) + safe_size(child1(t)) + 1;
            return t;
        }
        static void push(node_pointer t) { // t : not null
            if (std::exchange(reversed(t), false)) {
                reverse_all(child0(t));
                reverse_all(child1(t));
            }
        }

        static constexpr node_pointer empty_node() { return node_pointer{}; }
        static void delete_tree(node_pointer t) {
            if (not t) return;
            delete_tree(child0(t));
            delete_tree(child1(t));
            node_pointer::dealloc(t);
        }

        template <typename ...Args>
        static node_pointer build(Args &&... args) {
            std::vector<value_type> dat(std::forward<Args>(args)...);

            const size_t n = dat.size();

            if (n == 0) return empty_node();

            std::vector<priority_type> priorities(n);
            std::generate(priorities.begin(), priorities.end(), random_priority);
            std::make_heap(priorities.begin(), priorities.end());

            std::vector<node_pointer> nodes(n);

            size_t fpow2 = 1;
            while ((fpow2 << 1) <= n) fpow2 <<= 1;

            for (size_t bbst_index = 1, skipped = 0; bbst_index < 2 * fpow2; ++bbst_index) {
                size_t heap_index = (fpow2 | ((bbst_index - 1) >> 1)) >> __builtin_ctz(bbst_index);
                if (heap_index <= n) {
                    size_t index = bbst_index - skipped;
                    nodes[heap_index - 1] = node_pointer::alloc(std::move(dat[index - 1]));
                    set_priority(nodes[heap_index - 1], priorities[heap_index - 1]);
                } else {
                    ++skipped;
                }
            }
            for (size_t i = fpow2 - 1; i >= 1; --i) {
                size_t li = 2 * i, ri = 2 * i + 1;
                if (li <= n) set_child0(nodes[i - 1], nodes[li - 1]);
                if (ri <= n) set_child1(nodes[i - 1], nodes[ri - 1]);
                node_type::update(nodes[i - 1]);
            }
            return nodes[0];
        }

        static std::pair<node_pointer, node_pointer> split(node_pointer t, size_type k) {
            if (k == 0) return { empty_node(), t };
            if (k == size(t)) return { t, empty_node() };

            static std::vector<node_pointer> lp{}, rp{};

            while (true) {
                node_type::push(t);
                if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                    if (rp.size()) set_child0(rp.back(), t);
                    rp.push_back(t);
                    if (k == lsiz) {
                        node_pointer& lch = child0(t);
                        if (lp.size()) set_child1(lp.back(), lch);

                        node_pointer lt = std::exchange(lch, empty_node()), rt = empty_node();
                        while (lp.size()) node_type::update(lt = lp.back()), lp.pop_back();
                        while (rp.size()) node_type::update(rt = rp.back()), rp.pop_back();
                        return { lt, rt };
                    }
                    t = child0(t);
                } else {
                    if (lp.size()) set_child1(lp.back(), t);
                    lp.push_back(t);
                    t = child1(t);
                    k -= lsiz + 1;
                }
            }
        }
        static std::tuple<node_pointer, node_pointer, node_pointer> split(node_pointer t, size_type l, size_type r) {
            auto [tlm, tr] = split(t, r);
            auto [tl, tm] = split(tlm, l);
            return { tl, tm, tr };
        }
        // Split immediately before the first element that satisfies the condition.
        template <typename Predicate>
        static std::pair<node_pointer, node_pointer> split_binary_search(node_pointer t, const Predicate& f) {
            if (not t) {
                return { empty_node(), empty_node() };
            }
            node_type::push(t);
            if (f(value(t))) {
                auto [ll, lr] = split_binary_search(child0(t), f);
                set_child0(t, lr);
                return { ll, node_type::update(t) };
            } else {
                auto [rl, rr] = split_binary_search(child1(t), f);
                set_child1(t, rl);
                return { node_type::update(t), rr };
            }
        }

        template <typename Compare = std::less<>>
        static std::pair<node_pointer, node_pointer> split_lower_bound(node_pointer t, const value_type& target, const Compare& comp) {
            return split_binary_search(t, [&](const value_type& v) { return not comp(v, target); });
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, node_pointer> split_upper_bound(node_pointer t, const value_type& target, const Compare& comp) {
            return split_binary_search(t, [&](const value_type& v) { return comp(target, v); });
        }

        static node_pointer merge(node_pointer tl, node_pointer tr) {
            if (not (tl and tr)) {
                return tl ? tl : tr;
            }
            if (priority(tl) < priority(tr)) {
                node_type::push(tr);
                set_child0(tr, merge(tl, child0(tr)));
                return node_type::update(tr);
            } else {
                node_type::push(tl);
                set_child1(tl, merge(child1(tl), tr));
                return node_type::update(tl);
            }
        }
        static node_pointer merge(node_pointer tl, node_pointer tm, node_pointer tr) {
            return merge(merge(tl, tm), tr);
        }
        static node_pointer insert_impl(node_pointer t, size_type k, node_pointer new_node) {
            if (not t) {
                return new_node;
            }
            static std::vector<node_pointer> st;

            node_pointer* p = nullptr;

            while (true) {
                if ((not t) or priority(new_node) > priority(t)) {
                    if (t) {
                        auto [tl, tr] = split(t, k);
                        set_child0(new_node, tl);
                        set_child1(new_node, tr);
                        t = node_type::update(new_node);
                    } else {
                        t = new_node;
                    }
                    if (p) *p = t;
                    while (st.size()) {
                        t = node_type::update(st.back()), st.pop_back();
                    }
                    return t;
                } else {
                    node_type::push(t);
                    st.push_back(t);
                    if (const size_type lsiz = safe_size(child0(t)); k <= lsiz) {
                        t = *(p = &child0(t));
                    } else {
                        t = *(p = &child1(t));
                        k -= lsiz + 1;
                    }
                }
            }
        }
        template <typename ...Args>
        static node_pointer insert(node_pointer t, size_type k, Args &&...args) {
            return insert_impl(t, k, node_pointer::alloc(std::forward<Args>(args)...));
        }
        template <typename ...Args>
        static node_pointer push_front(node_pointer t, Args &&...args) {
            return insert(t, 0, std::forward<Args>(args)...);
        }
        template <typename ...Args>
        static node_pointer push_back(node_pointer t, Args &&...args) {
            return insert(t, safe_size(t), std::forward<Args>(args)...);
        }

        // Insert a new node immediately before the first element that satisfies the condition.
        // Returns { node, position to insert }
        template <typename Predicate>
        static std::pair<node_pointer, size_type> insert_binary_search_impl(node_pointer t, const Predicate& f, node_pointer new_node) {
            if (not t) {
                return { new_node, 0 };
            }
            if (priority(new_node) > priority(t)) {
                auto [tl, tr] = split_binary_search(t, f);
                set_child0(new_node, tl);
                set_child1(new_node, tr);
                return { node_type::update(new_node), safe_size(tl) };
            } else {
                node_type::push(t);
                if (f(value(t))) {
                    auto [c0, pos] = insert_binary_search_impl(child0(t), f, new_node);
                    set_child0(t, c0);
                    return { node_type::update(t), pos };
                } else {
                    auto [c1, pos] = insert_binary_search_impl(child1(t), f, new_node);
                    set_child1(t, c1);
                    return { node_type::update(t), pos + safe_size(child0(t)) + 1 };
                }
            }
        }
        template <typename Predicate, typename ...Args>
        static std::pair<node_pointer, size_type> insert_binary_search(node_pointer t, const Predicate& f, Args &&...args) {
            return insert_binary_search_impl(t, f, node_pointer::alloc(std::forward<Args>(args)...));
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, size_type> insert_lower_bound(node_pointer t, const value_type& v, Compare comp) {
            return insert_binary_search(t, [&](const value_type& x) { return not comp(x, v); }, v);
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, size_type> insert_upper_bound(node_pointer t, const value_type& v, Compare comp) {
            return insert_binary_search(t, [&](const value_type& x) { return comp(v, x); }, v);
        }

        static std::pair<node_pointer, value_type> erase(node_pointer t, size_type k) {
            node_type::push(t);
            if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {
                node_pointer::dealloc(t);
                return { merge(child0(t), child1(t)), std::move(value(t)) };
            } else if (k < lsiz) {
                auto [c0, v] = erase(child0(t), k);
                set_child0(t, c0);
                return { node_type::update(t), std::move(v) };
            } else {
                auto [c1, v] = erase(child1(t), k - (lsiz + 1));
                set_child1(t, c1);
                return { node_type::update(t), std::move(v) };
            }
        }
        static std::pair<node_pointer, value_type> pop_front(node_pointer t) { return erase(t, 0); }
        static std::pair<node_pointer, value_type> pop_back(node_pointer t) { return erase(t, safe_size(t) - 1); }

        // Erase the first element that satisfies the condition f if it also satisfies the condition g.
        // returns { node, optional(position, value) }
        template <typename Predicate, typename RemovePredicate>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_binary_search(node_pointer t, const Predicate& f, const RemovePredicate& g) {
            if (not t) return { empty_node(), std::nullopt };
            node_type::push(t);
            if (f(value(t))) {
                auto [c0, erased] = erase_binary_search(child0(t), f, g);
                if (erased) {
                    set_child0(t, c0);
                    return { node_type::update(t), std::move(erased) };
                } else if (g(value(t))) {
                    node_pointer::dealloc(t);
                    std::pair<size_type, value_type> erased_entry{ safe_size(child0(t)), std::move(value(t)) };
                    return { merge(child0(t), child1(t)), std::move(erased_entry) };
                } else {
                    return { t, std::nullopt };
                }
            } else {
                auto [c1, erased] = erase_binary_search(child1(t), f, g);
                if (erased) {
                    set_child1(t, c1);
                    size_type& pos = erased->first;
                    pos += safe_size(child0(t)) + 1;
                    return { node_type::update(t), std::move(erased) };
                } else {
                    return { t, std::nullopt };
                }
            }
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_lower_bound(node_pointer t, const value_type& v, Compare comp) {
            return erase_binary_search(
                t,
                [&](const value_type& x) { return not comp(x, v); },
                [] { return true; }
            );
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_upper_bound(node_pointer t, const value_type& v, Compare comp) {
            return erase_binary_search(
                t,
                [&](const value_type& x) { return comp(v, x); },
                [] { return true; }
            );
        }
        template <typename Compare = std::less<>>
        static std::pair<node_pointer, std::optional<std::pair<size_type, value_type>>> erase_if_exists(node_pointer t, const value_type& v, Compare comp) {
            return erase_binary_search(
                t,
                [&](const value_type& x) { return not comp(x, v); },
                [&](const value_type& x) { return not comp(v, x); }
            );
        }

        static node_pointer rotate(node_pointer t, size_type k) {
            auto [tl, tr] = split(t, k);
            return merge(tr, tl);
        }
        static node_pointer rotate(node_pointer t, size_type l, size_type m, size_type r) {
            auto [tl, tm, tr] = split(t, l, r);
            return merge(tl, rotate(tm, m - l), tr);
        }

        static value_type& get(node_pointer t, size_type k) {
            while (true) {
                node_type::push(t);
                if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {
                    return value(t);
                } else if (k < lsiz) {
                    t = child0(t);
                } else {
                    k -= lsiz + 1;
                    t = child1(t);
                }
            }
        }

        template <typename Func>
        static node_pointer set_update(node_pointer t, size_type k, const Func& f) {
            node_type::push(t);
            if (const size_type lsiz = safe_size(child0(t)); k == lsiz) {
                value_type& val = value(t);
                val = f(const_cast<const value_type&>(val));
            } else if (k < lsiz) {
                set_child0(t, set_update(child0(t), k, f));
            } else {
                set_child1(t, set_update(child1(t), k - (lsiz + 1), f));
            }
            return node_type::update(t);
        }

        static node_pointer reverse_all(node_pointer t) {
            if (t) {
                reversed(t) ^= true;
                std::swap(child0(t), child1(t));
            }
            return t;
        }
        static node_pointer reverse(node_pointer t, size_type l, size_type r) {
            auto [tl, tm, tr] = split(t, l, r);
            return merge(tl, Derived::reverse_all(tm), tr);
        }

        static std::vector<value_type> dump(node_pointer t) {
            std::vector<value_type> res;
            res.reserve(safe_size(t));
            auto rec = [&](auto rec, node_pointer t) -> void {
                if (not t) return;
                node_type::push(t);
                rec(rec, child0(t));
                res.push_back(value(t));
                rec(rec, child1(t));
            };
            rec(rec, t);
            return res;
        }

        // Find the first element that satisfies the condition f : (value, index) -> { false, true }.
        // Returns { optional(value), position }
        template <typename Predicate>
        static std::pair<size_type, std::optional<value_type>> binary_search(node_pointer t, const Predicate& f) {
            node_pointer res = empty_node();
            int ng = -1, ok = safe_size(t);
            while (ok - ng > 1) {
                node_type::push(t);
                if (const int root = ng + safe_size(child0(t)) + 1; f(value(t), root)) {
                    res = t;
                    ok = root, t = child0(t);
                } else {
                    ng = root, t = child1(t);
                }
            }
            if (not res) {
                return { ok, std::nullopt };
            } else {
                return { ok, value(res) };
            }
        }

        // for debug
        static void check_heap(node_pointer t) {
            if (node_pointer lch = child0(t)) {
                check_heap(lch);
                assert(priority(t) >= priority(lch));
            }
            if (node_pointer rch = child1(t)) {
                check_heap(rch);
                assert(priority(t) >= priority(rch));
            }
        }

        // comp(T t, U u) = (t < u)
        template <typename U, typename Compare = std::less<>>
        static std::pair<size_type, std::optional<value_type>> lower_bound(node_pointer t, const U& target, Compare comp) {
            return binary_search(t, [&](const value_type& v, int) { return not comp(v, target); });
        }
        // comp(T u, U t) = (u < t)
        template <typename U, typename Compare = std::less<>>
        static std::pair<size_type, std::optional<value_type>> upper_bound(node_pointer t, const U& target, Compare comp) {
            return binary_search(t, [&](const value_type& v, int) { return comp(target, v); });
        }

        template <bool reversed_, bool constant_>
        struct NodeIterator {
            static constexpr bool constant = constant_;
            static constexpr bool reversed = reversed_;

            using difference_type = ReversibleNode::difference_type;
            using value_type = ReversibleNode::value_type;
            using pointer = std::conditional_t<constant, ReversibleNode::const_pointer, ReversibleNode::pointer>;
            using reference = std::conditional_t<constant, ReversibleNode::const_reference, ReversibleNode::reference>;
            using iterator_cateogory = std::random_access_iterator_tag;

            NodeIterator(): root(empty_node()), index(0) {}

            reference operator*() {
                if (stk.empty() and index != safe_size(root)) down(root, index, not reversed);
                return value(stk.back());
            }
            reference operator[](difference_type k) const { return *((*this) + k); }

            NodeIterator& operator++() { return *this += 1; }
            NodeIterator& operator--() { return *this -= 1; }
            NodeIterator& operator+=(difference_type k) { return suc(+k), * this; }
            NodeIterator& operator-=(difference_type k) { return suc(-k), * this; }
            NodeIterator operator++(int) { NodeIterator res = *this; ++(*this); return res; }
            NodeIterator operator--(int) { NodeIterator res = *this; --(*this); return res; }
            friend NodeIterator operator+(NodeIterator it, difference_type k) { return it += k; }
            friend NodeIterator operator+(difference_type k, NodeIterator it) { return it += k; }
            friend NodeIterator operator-(NodeIterator it, difference_type k) { return it -= k; }

            friend difference_type operator-(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index - rhs.index; }

            friend bool operator==(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index == rhs.index; }
            friend bool operator!=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index != rhs.index; }
            friend bool operator<(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index < rhs.index; }
            friend bool operator>(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index > rhs.index; }
            friend bool operator<=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index <= rhs.index; }
            friend bool operator>=(const NodeIterator& lhs, const NodeIterator& rhs) { return lhs.index >= rhs.index; }

            static NodeIterator begin(node_pointer root) { return NodeIterator(root, 0); }
            static NodeIterator end(node_pointer root) { return NodeIterator(root, safe_size(root)); }
        private:
            node_pointer root;
            size_type index;
            std::vector<node_pointer> stk;

            NodeIterator(node_pointer root, size_type index): root(root), index(index) {}

            void up(const bool positive) {
                node_pointer t = stk.back();
                while (true) {
                    stk.pop_back();
                    if (t == child(stk.back(), not positive)) return;
                    t = stk.back();
                }
            }
            void down(node_pointer t, size_type k, const bool positive) {
                while (true) {
                    node_type::push(t);
                    stk.push_back(t);

                    if (size_type siz = safe_size(child(t, not positive)); k == siz) {
                        break;
                    } else if (k < siz) {
                        t = child(t, not positive);
                    } else {
                        k -= siz + 1;
                        t = child(t, positive);
                    }
                }
            }
            void suc(difference_type k) {
                index += k;
                if (index == safe_size(root)) stk.clear();
                if (stk.empty()) return;

                const bool positive = k < 0 ? (k = -k, reversed) : not reversed;
                while (k) {
                    node_pointer t = child(stk.back(), positive);
                    if (difference_type siz = safe_size(t); k > siz) {
                        up(positive);
                        k -= siz + 1;
                    } else {
                        down(t, k - 1, positive);
                        break;
                    }
                }
            }
        };
        using iterator = NodeIterator<false, false>;
        using reverse_iterator = NodeIterator<true, false>;
        using const_iterator = NodeIterator<false, true>;
        using const_reverse_iterator = NodeIterator<true, true>;

        static iterator begin(node_pointer t) { return iterator::begin(t); }
        static iterator end(node_pointer t) { return iterator::end(t); }
        static reverse_iterator rbegin(node_pointer t) { return reverse_iterator::begin(t); }
        static reverse_iterator rend(node_pointer t) { return reverse_iterator::end(t); }
        static const_iterator cbegin(node_pointer t) { return const_iterator::begin(t); }
        static const_iterator cend(node_pointer t) { return const_iterator::end(t); }
        static const_reverse_iterator crbegin(node_pointer t) { return const_reverse_iterator::begin(t); }
        static const_reverse_iterator crend(node_pointer t) { return const_reverse_iterator::end(t); }
    };
} // namespace suisen::internal::implicit_treap

namespace suisen {
    namespace internal::implicit_treap {
        template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>
        struct ReversibleRangeProductNode: ReversibleNode<T, ReversibleRangeProductNode<T, op, e, toggle>> {
            using base = ReversibleNode<T, ReversibleRangeProductNode<T, op, e, toggle>>;
            using node_pointer = typename base::node_pointer;
            using value_type = typename base::value_type;

            value_type _sum;
            ReversibleRangeProductNode(const value_type& val): base(val), _sum(val) {}

            // ----- override ----- //
            static node_pointer update(node_pointer t) {
                base::update(t);
                prod_all(t) = op(op(safe_prod(base::child0(t)), base::value(t)), safe_prod(base::child1(t)));
                return t;
            }
            static node_pointer reverse_all(node_pointer t) {
                if (t) {
                    base::reversed(t) ^= true;
                    std::swap(base::child0(t), base::child1(t));
                    value_type& sum = prod_all(t);
                    sum = toggle(sum);
                }
                return t;
            }

            // ----- new features ----- //
            static value_type& prod_all(node_pointer t) {
                return t->_sum;
            }
            static value_type safe_prod(node_pointer t) {
                return t ? prod_all(t) : e();
            }
            static std::pair<node_pointer, value_type> prod(node_pointer t, size_t l, size_t r) {
                auto [tl, tm, tr] = base::split(t, l, r);
                value_type res = safe_prod(tm);
                return { base::merge(tl, tm, tr), res };
            }
            template <typename Func>
            static node_pointer set(node_pointer t, size_t k, const Func& f) {
                return base::set_update(t, k, f);
            }

            template <typename Predicate>
            static uint32_t max_right(node_pointer t, const Predicate& f) {
                value_type sum = e();
                assert(f(sum));

                uint32_t r = 0;
                while (t) {
                    base::push(t);

                    node_pointer lch = base::child0(t);

                    value_type nxt_sum = op(sum, safe_prod(lch));
                    if (f(nxt_sum)) {
                        r += base::safe_size(lch);
                        sum = op(nxt_sum, base::value(t));
                        if (f(sum)) {
                            ++r;
                            t = base::child1(t);
                        } else {
                            break;
                        }
                    } else {
                        t = lch;
                    }
                }
                return r;
            }
            template <typename Predicate>
            static std::pair<node_pointer, uint32_t> max_right(node_pointer t, uint32_t l, const Predicate& f) {
                auto [tl, tr] = base::split(t, l);
                size_t w = max_right(tr, f);
                t = base::merge(tl, tr);
                return { t, l + w };
            }
            template <typename Predicate>
            static uint32_t min_left(node_pointer t, const Predicate& f) {
                value_type sum = e();
                assert(f(sum));

                uint32_t l = base::safe_size(t);
                while (t) {
                    base::push(t);

                    node_pointer rch = base::child1(t);

                    value_type nxt_sum = op(safe_prod(rch), sum);
                    if (f(nxt_sum)) {
                        l -= base::safe_size(rch);
                        sum = op(base::value(t), nxt_sum);
                        if (f(sum)) {
                            --l;
                            t = base::child0(t);
                        } else {
                            break;
                        }
                    } else {
                        t = rch;
                    }
                }
                return l;
            }
            template <typename Predicate>
            static std::pair<node_pointer, uint32_t> min_left(node_pointer t, uint32_t r, const Predicate& f) {
                auto [tl, tr] = base::split(t, r);
                size_t l = min_left(tl, f);
                t = base::merge(tl, tr);
                return { t, l };
            }
        };
    }

    template <typename T, T(*op)(T, T), T(*e)(), T(*toggle)(T)>
    class ReversibleDynamicSegmentTree {
        using node_type = internal::implicit_treap::ReversibleRangeProductNode<T, op, e, toggle>;
        using node_pointer = typename node_type::node_pointer;

        node_pointer _root;

        struct node_pointer_construct {};
        ReversibleDynamicSegmentTree(node_pointer root, node_pointer_construct): _root(root) {}

    public:
        using value_type = typename node_type::value_type;

        ReversibleDynamicSegmentTree(): _root(node_type::empty_node()) {}
        explicit ReversibleDynamicSegmentTree(size_t n, const value_type& fill_value = {}): _root(node_type::build(n, fill_value)) {}
        template <typename U>
        ReversibleDynamicSegmentTree(const std::vector<U>& dat) : _root(node_type::build(dat.begin(), dat.end())) {}

        void free() {
            node_type::delete_tree(_root);
            _root = node_type::empty_node();
        }
        void clear() { free(); }

        static void reserve(size_t capacity) { node_type::reserve(capacity); }

        bool empty() const { return node_type::empty(_root); }
        int size() const { return node_type::safe_size(_root); }

        const value_type& operator[](size_t k) const { return get(k); }
        const value_type& get(size_t k) const {
            assert(k < size_t(size()));
            return node_type::get(_root, k);
        }
        const value_type& front() const { return get(0); }
        const value_type& back() const { return get(size() - 1); }

        void set(size_t k, const value_type& val) {
            assert(k < size_t(size()));
            _root = node_type::set(_root, k, [&](const value_type&) { return val; });
        }
        template <typename Func>
        void apply(size_t k, const Func& f) {
            assert(k < size_t(size()));
            _root = node_type::set(_root, k, [&](const value_type& val) { return f(val); });
        }

        value_type prod_all() const { return node_type::safe_prod(_root); }
        value_type prod(size_t l, size_t r) {
            value_type res;
            std::tie(_root, res) = node_type::prod(_root, l, r);
            return res;
        }

        void insert(size_t k, const value_type& val) {
            assert(k <= size_t(size()));
            _root = node_type::insert(_root, k, val);
        }
        void push_front(const value_type& val) { _root = node_type::push_front(_root, val); }
        void push_back(const value_type& val) { _root = node_type::push_back(_root, val); }

        // Insert a new value immediately before the first element that satisfies the condition f.
        // Returns: the inserted position
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        int insert_binary_search(const value_type& val, const Predicate &f) {
            int pos;
            std::tie(_root, pos) = node_type::insert_binary_search(_root, f, val);
            return pos;
        }
        // Insert a new value immediately before the first element that is greater than or equal to the new value.
        // Returns: the inserted position
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        int insert_lower_bound(const value_type& val, const Compare &comp = {}) {
            int pos;
            std::tie(_root, pos) = node_type::insert_lower_bound(_root, val, comp);
            return pos;
        }
        // Insert a new value immediately before the first element that is greater than the new value.
        // Returns: the inserted position
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        int insert_upper_bound(const value_type& val, const Compare &comp = {}) {
            int pos;
            std::tie(_root, pos) = node_type::insert_upper_bound(_root, val, comp);
            return pos;
        }

        value_type erase(size_t k) {
            assert(k <= size_t(size()));
            value_type v;
            std::tie(_root, v) = node_type::erase(_root, k);
            return v;
        }
        value_type pop_front() { return erase(0); }
        value_type pop_back() { return erase(size() - 1); }

        // Erase the first element that satisfies the condition f if it also satisfies the condition g.
        // returns optional(position, value)
        // Requirements: sequence is sorted
        template <typename Predicate, typename RemovePredicate>
        std::optional<std::pair<int, value_type>> erase_binary_search(const Predicate &f, const RemovePredicate& g) {
            auto [root, erased] = node_type::erase_binary_search(_root, f, g);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }
        // Erase the first element that is greater than or equal to val.
        // returns optional(position, value)
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        std::optional<std::pair<int, value_type>> erase_lower_bound(const value_type &val, const Compare &comp = {}) {
            auto [root, erased] = node_type::erase_lower_bound(_root, val, comp);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }
        // Erase the first element that is greater than val.
        // returns optional(position, value)
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        std::optional<std::pair<int, value_type>> erase_upper_bound(const value_type &val, const Compare &comp = {}) {
            auto [root, erased] = node_type::erase_upper_bound(_root, val, comp);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }
        // Erase the first element that is equal to val.
        // returns optional(position, value)
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        std::optional<std::pair<int, value_type>> erase_if_exists(const value_type &val, const Compare &comp = {}) {
            auto [root, erased] = node_type::erase_if_exists(_root, val, comp);
            _root = root;
            if (erased) {
                return std::pair<int, value_type>{ erased->first, erased->second };
            } else {
                return std::nullopt;
            }
        }

        // Split immediately before the k-th element.
        ReversibleDynamicSegmentTree split(size_t k) {
            assert(k <= size_t(size()));
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split(_root, k);
            return ReversibleDynamicSegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that satisfies the condition.
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        ReversibleDynamicSegmentTree split_binary_search(const Predicate &f) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_binary_search(_root, f);
            return ReversibleDynamicSegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that is greater than or equal to val.
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        ReversibleDynamicSegmentTree split_lower_bound(const value_type &val, const Compare &comp = {}) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_lower_bound(_root, val, comp);
            return ReversibleDynamicSegmentTree(root_r, node_pointer_construct{});
        }
        // Split immediately before the first element that is greater than val.
        // Requirements: sequence is sorted
        template <typename Compare = std::less<>>
        ReversibleDynamicSegmentTree split_upper_bound(const value_type &val, const Compare &comp = {}) {
            node_pointer root_r;
            std::tie(_root, root_r) = node_type::split_upper_bound(_root, val, comp);
            return ReversibleDynamicSegmentTree(root_r, node_pointer_construct{});
        }

        void merge(ReversibleDynamicSegmentTree r) { _root = node_type::merge(_root, r._root); }

        void rotate(size_t k) {
            assert(k <= size_t(size()));
            _root = node_type::rotate(_root, k);
        }
        void rotate(size_t l, size_t m, size_t r) {
            assert(l <= m and m <= r and r <= size_t(size()));
            _root = node_type::rotate(_root, l, m, r);
        }

        void reverse(size_t l, size_t r) {
            assert(l <= r and r <= size_t(size()));
            if (r - l >= 2) _root = node_type::reverse(_root, l, r);
        }
        void reverse_all() { _root = node_type::reverse_all(_root); }

        std::vector<value_type> dump() const { return node_type::dump(_root); }

        // Find the first element that satisfies the condition f.
        // Returns { position, optional(value) }
        // Requirements: f(A[i]) must be monotonic
        template <typename Predicate>
        std::pair<int, std::optional<value_type>> binary_search(const Predicate& f) const {
            auto [pos, val] = node_type::binary_search(_root, f);
            return { pos, std::move(val) };
        }
        // comp(T t, U u) = (t < u)
        // Requirements: sequence is sorted
        template <typename U, typename Compare = std::less<>>
        std::pair<int, std::optional<value_type>> lower_bound(const U& target, Compare comp = {}) const {
            auto [pos, val] = node_type::lower_bound(_root, target, comp);
            return { pos, std::move(val) };
        }
        // comp(T u, U t) = (u < t)
        // Requirements: sequence is sorted
        template <typename U, typename Compare = std::less<>>
        std::pair<int, std::optional<value_type>> upper_bound(const U& target, Compare comp = {}) const {
            auto [pos, val] = node_type::upper_bound(_root, target, comp);
            return { pos, std::move(val) };
        }

        // Returns max{ r | f(op(A[l], ..., A[r-1])) = true }
        template <typename Predicate>
        int max_right(size_t l, const Predicate& f) {
            size_t res;
            std::tie(_root, res) = node_type::max_right(_root, l, f);
            return res;
        }
        // Returns min{ l | f(op(A[l], ..., A[r-1])) = true }
        template <typename Predicate>
        int min_left(size_t r, const Predicate& f) {
            size_t res;
            std::tie(_root, res) = node_type::min_left(_root, r, f);
            return res;
        }

        using iterator = typename node_type::const_iterator;
        using reverse_iterator = typename node_type::const_reverse_iterator;
        using const_iterator = typename node_type::const_iterator;
        using const_reverse_iterator = typename node_type::const_reverse_iterator;

        iterator begin() const { return cbegin(); }
        iterator end() const { return cend(); }
        reverse_iterator rbegin() const { return crbegin(); }
        reverse_iterator rend() const { return crend(); }
        const_iterator cbegin() const { return node_type::cbegin(_root); }
        const_iterator cend() const { return node_type::cend(_root); }
        const_reverse_iterator crbegin() const { return node_type::crbegin(_root); }
        const_reverse_iterator crend() const { return node_type::crend(_root); }

        // handling internal nodes
        using internal_node = node_type;
        using internal_node_pointer = node_pointer;

        internal_node_pointer& root_node() { return _root; }
        const internal_node_pointer& root_node() const { return _root; }
        void set_root_node(internal_node_pointer new_root) { root_node() = new_root; }
    };
} // namespace suisen

long long op(long long x, long long y) {
    return x + y;
}
long long e() {
    return 0;
}
long long toggle(long long x) {
    return x;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    
    std::vector<long long> a(n);
    for (auto &e : a) std::cin >> e;

    suisen::ReversibleDynamicSegmentTree<long long, op, e, toggle> seg(a);
    for (int query_id = 0; query_id < q; ++query_id) {
        int t, l, r;
        std::cin >> t >> l >> r;
        if (t == 0) {
            seg.reverse(l, r);
        } else {
            std::cout << seg.prod(l, r) << '\n';
        }
    }
    return 0;
}

