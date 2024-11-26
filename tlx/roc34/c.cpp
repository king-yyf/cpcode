#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cstring>
#include <random>
#ifndef __OY_MODULAR__
#define __OY_MODULAR__
namespace OY {
    template <typename _ModType, _ModType _P>
    struct Modular {
        static constexpr _ModType mod() { return _P; }
        static constexpr _ModType mod(uint64_t __a) { return __a % _P; }
        static constexpr _ModType plus(_ModType __a, _ModType __b) {
            if (__a += __b; __a >= _P) __a -= _P;
            return __a;
        }
        static constexpr _ModType minus(_ModType __a, _ModType __b) {
            if (__a += _P - __b; __a >= _P) __a -= _P;
            return __a;
        }
        static constexpr _ModType multiply(uint64_t __a, uint64_t __b) {
            if constexpr (std::is_same_v<_ModType, uint64_t>)
                return multiply_ld(__a, __b);
            else
                return multiply_64(__a, __b);
        }
        static constexpr _ModType multiply_64(uint64_t __a, uint64_t __b) {
            return mod(__a * __b);
        }
        static constexpr _ModType multiply_128(uint64_t __a, uint64_t __b) { return __uint128_t(__a) * __b % _P; }
        static constexpr _ModType multiply_ld(uint64_t __a, uint64_t __b) {
            int64_t res = __a * __b - uint64_t(1.L / _P * __a * __b) * _P;
            if (res < 0)
                res += _P;
            else if (res >= _P)
                res -= _P;
            return res;
        }
        static constexpr _ModType pow(uint64_t __a, uint64_t __n) {
            if constexpr (std::is_same_v<_ModType, uint64_t>)
                return pow_ld(__a, __n);
            else
                return pow_64(__a, __n);
        }
        static constexpr _ModType pow_64(uint64_t __a, uint64_t __n) {
            _ModType res = 1, b = mod(__a);
            while (__n) {
                if (__n & 1) res = multiply_64(res, b);
                b = multiply_64(b, b);
                __n >>= 1;
            }
            return res;
        }
        static constexpr _ModType pow_128(uint64_t __a, uint64_t __n) {
            _ModType res = 1, b = mod(__a);
            while (__n) {
                if (__n & 1) res = multiply_128(res, b);
                b = multiply_128(b, b);
                __n >>= 1;
            }
            return res;
        }
        static constexpr _ModType pow_ld(uint64_t __a, uint64_t __n) {
            _ModType res = 1, b = mod(__a);
            while (__n) {
                if (__n & 1) res = multiply_ld(res, b);
                b = multiply_ld(b, b);
                __n >>= 1;
            }
            return res;
        }
        template <typename _Tp>
        static constexpr _Tp divide(_Tp __a) { return __a / _P; }
        template <typename _Tp>
        static constexpr std::pair<_Tp, _Tp> divmod(_Tp __a) {
            _Tp quo = __a / _P, rem = __a - quo * _P;
            return {quo, rem};
        }
    };
    template <uint32_t _P>
    using Modular32 = Modular<uint32_t, _P>;
    template <uint64_t _P>
    using Modular64 = Modular<uint64_t, _P>;
}
#endif
#ifndef __OY_STATICMODINT__
#define __OY_STATICMODINT__
namespace OY {
    template <typename _ModType, _ModType _P, bool _IsPrime = false>
    struct StaticModInt {
        using mint = StaticModInt<_ModType, _P, _IsPrime>;
        _ModType m_val;
        static_assert(_P > 1 && _P < 1ull << 63);
        constexpr StaticModInt() : m_val(0) {}
        template <typename _Tp, std::enable_if_t<std::is_signed_v<_Tp>, bool> = true>
        constexpr StaticModInt(_Tp __val) : m_val(0) {
            int64_t x = int64_t(__val) % int64_t(mod());
            if (x < 0) x += mod();
            m_val = x;
        }
        template <typename _Tp, std::enable_if_t<std::is_unsigned_v<_Tp>, bool> = true>
        constexpr StaticModInt(_Tp __val) : m_val(__val % mod()) {}
        static constexpr mint raw(_ModType __val) {
            mint res;
            res.m_val = __val;
            return res;
        }
        static constexpr _ModType mod() { return _P; }
        constexpr _ModType val() const { return m_val; }
        constexpr mint pow(uint64_t __n) const { return Modular<_ModType, _P>::pow(m_val, __n); }
        constexpr mint inv() const {
            if constexpr (_IsPrime)
                return inv_Fermat();
            else
                return inv_exgcd();
        }
        constexpr mint inv_exgcd() const {
            _ModType x = mod(), y = m_val, m0 = 0, m1 = 1;
            while (y) {
                _ModType z = x / y;
                x -= y * z;
                m0 -= m1 * z;
                std::swap(x, y);
                std::swap(m0, m1);
            }
            if (m0 >= mod()) m0 += mod() / x;
            return raw(m0);
        }
        constexpr mint inv_Fermat() const { return pow(mod() - 2); }
        constexpr mint &operator++() {
            if (++m_val == mod()) m_val = 0;
            return *this;
        }
        constexpr mint &operator--() {
            if (m_val == 0) m_val = mod();
            m_val--;
            return *this;
        }
        constexpr mint operator++(int) {
            mint old(*this);
            ++*this;
            return old;
        }
        constexpr mint operator--(int) {
            mint old(*this);
            --*this;
            return old;
        }
        constexpr mint &operator+=(const mint &__other) {
            m_val = Modular<_ModType, _P>::plus(m_val, __other.m_val);
            return *this;
        }
        constexpr mint &operator-=(const mint &__other) {
            m_val = Modular<_ModType, _P>::minus(m_val, __other.m_val);
            return *this;
        }
        constexpr mint &operator*=(const mint &__other) {
            m_val = Modular<_ModType, _P>::multiply(m_val, __other.m_val);
            return *this;
        }
        constexpr mint &operator/=(const mint &__other) { return *this *= __other.inv(); }
        constexpr mint operator+() const { return *this; }
        constexpr mint operator-() const { return raw(m_val ? mod() - m_val : 0); }
        constexpr bool operator==(const mint &__other) const { return m_val == __other.m_val; }
        constexpr bool operator!=(const mint &__other) const { return m_val != __other.m_val; }
        constexpr bool operator<(const mint &__other) const { return m_val < __other.m_val; }
        constexpr bool operator>(const mint &__other) const { return m_val > __other.m_val; }
        constexpr bool operator<=(const mint &__other) const { return m_val <= __other.m_val; }
        constexpr bool operator>=(const mint &__other) const { return m_val <= __other.m_val; }
        template <typename _Tp>
        constexpr explicit operator _Tp() const { return _Tp(m_val); }
        constexpr friend mint operator+(const mint &a, const mint &b) { return mint(a) += b; }
        constexpr friend mint operator-(const mint &a, const mint &b) { return mint(a) -= b; }
        constexpr friend mint operator*(const mint &a, const mint &b) { return mint(a) *= b; }
        constexpr friend mint operator/(const mint &a, const mint &b) { return mint(a) /= b; }
        template <typename _Istream>
        friend _Istream &operator>>(_Istream &is, mint &self) { return is >> self.m_val; }
        template <typename _Ostream>
        friend _Ostream &operator<<(_Ostream &os, const mint &self) { return os << self.m_val; }
    };
    template <uint32_t _P, bool _IsPrime>
    using StaticModInt32 = StaticModInt<uint32_t, _P, _IsPrime>;
    template <uint64_t _P, bool _IsPrime>
    using StaticModInt64 = StaticModInt<uint64_t, _P, _IsPrime>;
}
#endif
#ifndef __OY_ZKWTREE2D__
#define __OY_ZKWTREE2D__
namespace OY {
    namespace Zkw2D {
        using size_type = uint32_t;
        struct NoInit {};
        template <typename ValueType>
        struct BaseNode {
            using value_type = ValueType;
            using modify_type = ValueType;
            static value_type op(const value_type &x, const value_type &y) { return x + y; }
            value_type m_val;
            const value_type &get() const { return m_val; }
            void set(const value_type &val) { m_val = val; }
        };
        template <typename ValueType, typename Operation>
        struct CustomNode {
            using value_type = ValueType;
            using modify_type = ValueType;
            static Operation s_op;
            static value_type op(const value_type &x, const value_type &y) { return s_op(x, y); }
            value_type m_val;
            const value_type &get() const { return m_val; }
            void set(const value_type &val) { m_val = val; }
        };
        template <typename ValueType, typename Operation>
        Operation CustomNode<ValueType, Operation>::s_op;
        template <typename Node, size_type MAX_NODE = 1 << 22>
        struct Tree {
            using node = Node;
            using value_type = typename node::value_type;
            using modify_type = typename node::modify_type;
            static node s_buffer[MAX_NODE];
            static size_type s_use_count;
            node *m_sub;
            size_type m_row, m_column, m_row_capacity, m_column_capacity, m_row_depth, m_column_depth;
            value_type _query(node *cur, size_type left, size_type right) const {
                left += m_column_capacity, right += m_column_capacity;
                value_type res = node::op(cur[left].get(), cur[right].get());
                while (left >> 1 < right >> 1) {
                    if (!(left & 1)) res = node::op(res, cur[left ^ 1].get());
                    if (right & 1) res = node::op(res, cur[right ^ 1].get());
                    left >>= 1, right >>= 1;
                }
                return res;
            }
            template <typename InitMapping = NoInit>
            Tree(size_type row = 0, size_type column = 0, InitMapping mapping = InitMapping()) { resize(row, column, mapping); }
            template <typename InitMapping = NoInit>
            void resize(size_type row, size_type column, InitMapping mapping = InitMapping()) {
                if ((m_row = row) && (m_column = column)) {
                    m_row_depth = std::bit_width(m_row - 1), m_row_capacity = 1 << m_row_depth;
                    m_column_depth = std::bit_width(m_column - 1), m_column_capacity = 1 << m_column_depth;
                    m_sub = s_buffer + s_use_count, s_use_count += m_row_capacity << (m_column_depth + 2);
                    if constexpr (!std::is_same<InitMapping, NoInit>::value) {
                        for (size_type i = 0; i < m_row; i++) {
                            node *cur = m_sub + ((m_row_capacity + i) << (m_column_depth + 1));
                            for (size_type j = 0; j < m_column; j++) cur[m_column_capacity + j].set(mapping(i, j));
                            for (size_type j = m_column_capacity; --j;) cur[j].set(node::op(cur[j * 2].get(), cur[j * 2 + 1].get()));
                        }
                        for (size_type i = m_row_capacity; --i;) {
                            node *cur = m_sub + m_column_capacity * 2 * i, *l = m_sub + m_column_capacity * 2 * i * 2, *r = m_sub + m_column_capacity * 2 * (i * 2 + 1);
                            for (size_type j = m_column_capacity; j < m_column_capacity * 2; j++) cur[j].set(node::op(l[j].get(), r[j].get()));
                            for (size_type j = m_column_capacity; --j;) cur[j].set(node::op(cur[j * 2].get(), cur[j * 2 + 1].get()));
                        }
                    }
                }
            }
            void add(size_type i, size_type j, const modify_type &modify) {
                for (i += m_row_capacity; i; i >>= 1) {
                    node *cur = m_sub + (i << (m_column_depth + 1));
                    for (size_type k = m_column_capacity + j; k; k >>= 1) cur[k].set(node::op(cur[k].get(), modify));
                }
            }
            void modify(size_type i, size_type j, const value_type &val) {
                node *cur = m_sub + ((m_row_capacity + i) << (m_column_depth + 1));
                size_type k = m_column_capacity + j;
                cur[k].set(val);
                while (k >>= 1) cur[k].set(node::op(cur[k * 2].get(), cur[k * 2 + 1].get()));
                for (i += m_row_capacity; i >>= 1;) {
                    node *cur = m_sub + (i << (m_column_depth + 1)), *l = m_sub + ((i * 2) << (m_column_depth + 1)), *r = m_sub + ((i * 2 + 1) << (m_column_depth + 1));
                    size_type k = m_column_capacity + j;
                    cur[k].set(node::op(l[k].get(), r[k].get()));
                    while (k >>= 1) cur[k].set(node::op(cur[k * 2].get(), cur[k * 2 + 1].get()));
                }
            }
            value_type query(size_type i, size_type j) const { return m_sub[(((m_row_capacity + i) * 2 + 1) << m_column_depth) + j].get(); }
            value_type query(size_type row1, size_type row2, size_type column1, size_type column2) const {
                if (column1 == column2) {
                    if (row1 == row2) return query(row1, column1);
                    value_type res = node::op(query(row1, column1), query(row2, column1));
                    for (row1 += m_row_capacity, row2 += m_row_capacity; row1 >> 1 != row2 >> 1; row1 >>= 1, row2 >>= 1) {
                        if (!(row1 & 1)) res = node::op(res, m_sub[(((row1 ^ 1) * 2 + 1) << m_column_depth) + column1].get());
                        if (row2 & 1) res = node::op(res, m_sub[(((row2 ^ 1) * 2 + 1) << m_column_depth) + column1].get());
                    }
                    return res;
                }
                if (row1 == row2) return _query(m_sub + ((m_row_capacity + row1) << (m_column_depth + 1)), column1, column2);
                value_type res = node::op(_query(m_sub + ((m_row_capacity + row1) << (m_column_depth + 1)), column1, column2), _query(m_sub + ((m_row_capacity + row2) << (m_column_depth + 1)), column1, column2));
                for (row1 += m_row_capacity, row2 += m_row_capacity; row1 >> 1 != row2 >> 1; row1 >>= 1, row2 >>= 1) {
                    if (!(row1 & 1)) res = node::op(res, _query(m_sub + ((row1 ^ 1) << (m_column_depth + 1)), column1, column2));
                    if (row2 & 1) res = node::op(res, _query(m_sub + ((row2 ^ 1) << (m_column_depth + 1)), column1, column2));
                }
                return res;
            }
            value_type query_all() const { return m_sub[m_column_capacity * 2 + 1]; }
            size_type kth(size_type row1, size_type row2, value_type k) const {
                static node *buffer[128];
                size_type count = 0, i = 1;
                row1 += m_row_capacity, row2 += m_row_capacity;
                buffer[count++] = m_sub + (row1 << (m_column_depth + 1));
                if (row1 != row2) buffer[count++] = m_sub + (row2 << (m_column_depth + 1));
                for (; row1 >> 1 < row2 >> 1; row1 >>= 1, row2 >>= 1) {
                    if (!(row1 & 1)) buffer[count++] = m_sub + ((row1 ^ 1) << (m_column_depth + 1));
                    if (row2 & 1) buffer[count++] = m_sub + ((row2 ^ 1) << (m_column_depth + 1));
                }
                while (i < m_column_capacity) {
                    value_type cnt = 0;
                    for (size_type j = 0; j < count; j++) cnt += buffer[j][i * 2].get();
                    if (cnt <= k)
                        k -= cnt, i = i * 2 + 1;
                    else
                        i *= 2;
                }
                return i - m_column_capacity;
            }
        };
        template <typename Ostream, typename Node, size_type MAX_NODE>
        Ostream &operator<<(Ostream &out, const Tree<Node, MAX_NODE> &x) {
            out << "[";
            for (size_type i = 0; i < x.m_row; i++)
                for (size_type j = 0; j < x.m_column; j++) out << (j ? " " : (i ? ", [" : "[")) << x.query(i, j) << (j == x.m_column - 1 ? ']' : ',');
            return out << "]";
        }
        template <typename Node, size_type MAX_NODE>
        typename Tree<Node, MAX_NODE>::node Tree<Node, MAX_NODE>::s_buffer[MAX_NODE]{};
        template <typename Node, size_type MAX_NODE>
        size_type Tree<Node, MAX_NODE>::s_use_count;
    }
    template <typename Tp, Zkw2D::size_type MAX_NODE = 1 << 22, typename Operation, typename InitMapping = Zkw2D::NoInit, typename TreeType = Zkw2D::Tree<Zkw2D::CustomNode<Tp, Operation>, MAX_NODE>>
    auto make_ZkwTree2D(Zkw2D::size_type row, Zkw2D::size_type column, Operation op, InitMapping mapping = InitMapping()) -> TreeType { return TreeType(row, column, mapping); }
    template <typename Tp, Zkw2D::size_type MAX_NODE = 1 << 22, typename InitMapping = Zkw2D::NoInit, typename TreeType = Zkw2D::Tree<Zkw2D::CustomNode<Tp, const Tp &(*)(const Tp &, const Tp &)>, MAX_NODE>>
    auto make_ZkwTree2D(Zkw2D::size_type row, Zkw2D::size_type column, const Tp &(*op)(const Tp &, const Tp &), InitMapping mapping = InitMapping()) -> TreeType { return TreeType::node::s_op = op, TreeType(row, column, mapping); }
    template <typename Tp, Zkw2D::size_type MAX_NODE = 1 << 22, typename InitMapping = Zkw2D::NoInit, typename TreeType = Zkw2D::Tree<Zkw2D::CustomNode<Tp, Tp (*)(Tp, Tp)>, MAX_NODE>>
    auto make_ZkwTree2D(Zkw2D::size_type row, Zkw2D::size_type column, Tp (*op)(Tp, Tp), InitMapping mapping = InitMapping()) -> TreeType { return TreeType::node::s_op = op, TreeType(row, column, mapping); }
    template <Zkw2D::size_type MAX_NODE = 1 << 22>
    using ZkwSumTree2D = Zkw2D::Tree<Zkw2D::BaseNode<int64_t>, MAX_NODE>;
}
#endif
#ifdef OY_LOCAL
using namespace std;
#endif
template <typename Tp, typename Fp, typename Compare = std::less<void>>
bool chmax(Tp &a, const Fp &b, Compare comp = Compare()) { return comp(a, b) ? a = b, true : false; }
template <typename Tp, typename Fp, typename Compare = std::less<void>>
bool chmin(Tp &a, const Fp &b, Compare comp = Compare()) { return comp(b, a) ? a = b, true : false; }
#define FUNCNAME
using mint = OY::StaticModInt32<12345, false>;
using ValueType = mint;
struct BaseNode {
    using value_type = ValueType;
    using modify_type = ValueType;
    static value_type op(const value_type &x, const value_type &y) { return x * y; }
    value_type m_val;
    const value_type &get() const { return m_val; }
    void set(const value_type &val) { m_val = val; }
};
using Tree = OY::Zkw2D::Tree<BaseNode, 20000000>;
class Solution {
public:
    vector<vector<int>> constructProductMatrix(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        Tree S(m, n, [&](int i, int j) { return grid[i][j]; });
        vector<vector<int>> ans(m, vector<int>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                S.modify(i, j, 1);
                ans[i][j] = S.query(0, m - 1, 0, n - 1).val();
                S.modify(i, j, grid[i][j]);
            }
        }
        return ans;
    }
};