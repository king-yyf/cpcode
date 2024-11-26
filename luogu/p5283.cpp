#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T, int bit_len = numeric_limits<make_unsigned_t<T>>::digits>
class XorTrie {
    using U = make_unsigned_t<T>;
    struct Node {
        int siz;
        Node *ch[2] {nullptr, nullptr};
        Node() : siz(0) {}
        ~Node() { delete ch[0]; delete ch[1];}
        inline Node* get_or_new(bool b) noexcept { if (is_absent(b)) ch[b] = new Node(); return ch[b];}
        inline Node* operator[](bool b) const noexcept { return ch[b]; }
        inline bool is_absent (bool b) const noexcept { return ch[b] == nullptr; }
        inline bool is_present(bool b) const noexcept { return ch[b] != nullptr; }
        static inline int size(const Node *const node) noexcept { return node == nullptr ? 0 : node->siz; }
        inline void update_size() noexcept { siz = size(ch[0]) + size(ch[1]); }
    };
    public:
        XorTrie() : root(new Node) {}
        ~XorTrie() { delete root; }

        inline int size() const noexcept { return Node::size(root); }
        inline bool empty() const noexcept { return size() == 0; }

        int add(const U val, const int num = 1) noexcept {
            if (num == 0) return 0;
            Node *cur = root;
            cur->siz += num;
            for (int i = bit_len; i --> 0;) {
                cur = cur->get_or_new(bit(val, i));
                cur->siz += num;
            }
            return cur->siz;
        }
        int del(const U val, const int num = 1) noexcept {
            if (num == 0) return 0;
            return del(root, bit_len - 1, val, num);
        }
        int clear(const U val) noexcept { return del(val, numeric_limits<int>::max());}
        int prefix_count(const U val, const unsigned int l) const noexcept {
            Node *cur = root;
            for (int i = bit_len; i --> l;) {
                if (cur == nullptr) return 0;
                cur = (*cur)[bit(val, i)];
            }
            return Node::size(cur);
        }
        inline int count(const U val) const noexcept { return prefix_count(val, 0); }
        inline bool contains(const U val) const noexcept { return count(val) > 0; }

        inline U xor_kth_min(const U x, const int k) const {
            assert(0 <= k and k < size());
            return xor_kth_ele<false>(x, k);
        }
        inline U xor_kth_max(const U x, const int k) const {
            assert(0 <= k and k < size());
            return xor_kth_ele<true>(x, k);
        }
        inline U xor_min(const U x) const { return xor_kth_min(x, 0);  }
        inline U xor_max(const U x) const { return xor_kth_max(x, 0); }
        int xor_count_lt(const U x, const U val) const noexcept {
            int res = 0;
            Node *cur = root;
            for (int i = bit_len - 1; i >= 0; --i) {
                if (cur == nullptr) break;
                bool bx = bit(x, i);
                bool bv = bit(x ^ val, i);
                if (bx != bv) {
                    res += Node::size((*cur)[bx]);
                }
                cur = (*cur)[bv];
            }
            return res;
        }
        inline int xor_count_leq(const U x, const U val) const noexcept { return xor_count_lt(x, val) + count(val); }
        inline int xor_count_gt (const U x, const U val) const noexcept { return size() - xor_count_leq(x, val);    }
        inline int xor_count_geq(const U x, const U val) const noexcept { return size() - xor_count_lt(x, val);     }
        inline U xor_lower(const U x, const U val, const U default_value = ~U(0)) const noexcept {
            int k = size() - xor_count_geq(x, val) - 1;
            return k < 0 ? default_value : xor_kth_ele(x, k);
        }
        inline U xor_floor(const U x, const U val, const U default_value = ~U(0)) const noexcept {
            int k = size() - xor_count_gt(x, val) - 1;
            return k < 0 ? default_value : xor_kth_ele(x, k);
        }
        inline U xor_higher(const U x, const U val, const U default_value = ~U(0)) const noexcept {
            int k = xor_count_leq(x, val);
            return k == size() ? default_value : xor_kth_ele(x, k);
        }
        inline U xor_ceil(const U x, const U val, const U default_value = ~U(0)) const noexcept {
            int k = xor_count_lt(x, val);
            return k == size() ? default_value : xor_kth_ele(x, k);
        }

        inline U kth_min(const int k) const { return xor_kth_min(0, k); }
        inline U min() const { return xor_kth_min(0, 0); }
        inline U max() const { return xor_kth_min(~U(0), 0); }
        inline int count_lt (const U val) const noexcept { return xor_count_lt(0, val);  }
        inline int count_leq(const U val) const noexcept { return xor_count_leq(0, val); }
        inline int count_gt (const U val) const noexcept { return xor_count_gt(0, val);  }
        inline int count_geq(const U val) const noexcept { return xor_count_geq(0, val); }
        inline U lower (const U val, const U default_value = ~U(0)) const noexcept { return xor_lower (0, val, default_value); }
        inline U floor (const U val, const U default_value = ~U(0)) const noexcept { return xor_floor (0, val, default_value); }
        inline U higher(const U val, const U default_value = ~U(0)) const noexcept { return xor_higher(0, val, default_value); }
        inline U ceil  (const U val, const U default_value = ~U(0)) const noexcept { return xor_ceil  (0, val, default_value); }
    private:
        Node *const root;
        static constexpr bool bit(const U x, const int i) noexcept { return (x >> i) & 1;}
        int del(Node *cur, const int k, const U val, const int num) {
            if (k == -1) {
                int removed = std::min(cur->siz, num);
                cur->siz -= removed;
                return removed;
            }
            bool b = bit(val, k);
            if (cur->is_absent(b)) return 0;
            int removed = del((*cur)[b], k - 1, val, num);
            cur->update_size();
            return removed;
        }
        template <bool is_max_query = false>
        U xor_kth_ele(const U x, const int k) const noexcept {
            U res = 0;
            int rest = k;
            Node *cur = root;
            for (int i = bit_len - 1; i >= 0; --i) {
                bool b = is_max_query ^ bit(x, i);
                int sz = Node::size((*cur)[b]);
                if (sz <= rest) rest -= sz, b = not b;
                res |= U(b) << i;
                cur = (*cur)[b];
            }
            return x ^ res;
        }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    XorTrie<long long, 34> t;
    for (int i = 0; i < n; ++i) {
    	long long x;
    	cin >> x;
    	t.add(x);
    }
    long long ans = 0;
    for (int i = 0; i < k; ++i) {
    	ans += t.xor_kth_max(i);
    }
    return 0;
}
