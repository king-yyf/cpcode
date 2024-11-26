#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

ll inverse(ll a, ll m) { 
    a %= m; if (a == 0) return 0; if (a < 0) a += m;
    ll u = 0, v = 1;
    while (a) { ll t = m / a;  m -= t * a; swap(a, m); u -= t * v; swap(u, v); }
    return u;
}
struct barrett {
    unsigned int _m;
    ull im;
    explicit barrett(unsigned int m) : _m(m), im((ull)(-1) / m + 1) {} // 1 <= m < 2^31
    unsigned int umod() const { return _m; }
    unsigned int mul(unsigned int a, unsigned int b) const { // 0 <= a, b < m, return a * b % m
        ull z = a; z *= b;
        ull x = (ull)(((unsigned __int128)(z)*im) >> 64);
        unsigned int v = (unsigned int)(z - x * _m);
        if (_m <= v) v += _m;
        return v;
    }
};
template <int id> struct dynamic_mod {
    using mint = dynamic_mod;
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) { assert(1 <= m); bt = barrett(m);}
    static mint raw(int v) { mint x; x._v = v; return x;}
    dynamic_mod() : _v(0) {}
    template <class T>
    dynamic_mod(T v) { ll x = (ll)(v % (ll)(mod())); if (x < 0) x += mod(); _v = (unsigned int)(x);}
    dynamic_mod(unsigned int v) { _v = (unsigned int)(v % mod());}
    unsigned int val() const { return _v; }
    mint& operator++() { _v++; if (_v == umod()) _v = 0; return *this;}
    mint& operator--() { if (_v == 0) _v = umod(); _v--; return *this;}
    mint operator++(int) { mint result = *this; ++*this; return result;}
    mint operator--(int) { mint result = *this; --*this; return result;}
    mint& operator+=(const mint& rhs) { _v += rhs._v; if (_v >= umod()) _v -= umod(); return *this;}
    mint& operator-=(const mint& rhs) { _v += mod() - rhs._v; if (_v >= umod()) _v -= umod(); return *this;}
    mint& operator*=(const mint& rhs) { _v = bt.mul(_v, rhs._v); return *this;}
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(ll n) const { assert(0 <= n); mint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1;}return r;}
    mint inv() const { return inverse(_v, mod()); }
    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs;}
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs;}
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs;}
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v;}
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v;}
private:
    unsigned int _v;
    static barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id> barrett dynamic_mod<id>::bt(998244353);
using modint = dynamic_mod<998244353>;


using mint = dynamic_mod<998244353>;

template <class T,   // dp值的类型，如ll，int等。
        T(*op)(T, T), // 合并运算，需要满足交换律 op(dp[i], dp[j])
        T(*e)(),    // op 运算单位元，op(x, e()) = x
        T(*G)(T, int, int), // 根节点累积信息 G(dp[child], child, fa)
        class E,  // 边上 weight 的类型
        T(*F)(T, int, int, E)> // 子节点信息转移为父节点 F(dp[child], child, fa, weight(child, fa))
struct ReRooting : public vector<vector<pair<int, E>>> {
    using base_type = vector<vector<pair<int, E>>>;
    public:
        static constexpr int NIL = -1;
        using base_type::base_type;

        void add_edge(int u, int v, const E& w) {
            (*this)[u].emplace_back(v, w);
            (*this)[v].emplace_back(u, w);
        }

        const vector<T>& get(int root = 0) {
            const int n = this->size();
            dp.resize(n), to_par.resize(n);
            dfs_subtree(root, NIL);
            dfs(root, NIL, e());
            return dp;
        }

    private:
        vector<T> dp, to_par;

        void dfs_subtree(int u, int p) {
            dp[u] = e();
            for (auto [v, w] : (*this)[u]) {
                if (v == p) continue;
                dfs_subtree(v, u);
                dp[u] = op(dp[u], to_par[v] = F(G(dp[v], v, u), v, u, w));
            }
        }
        void dfs(int u, int p, T from_p) {
            dp[u] = G(dp[u], u, NIL);
            const int sz = (*this)[u].size();
            vector<T> cum_l { e() };
            cum_l.reserve(sz + 1);
            for (const auto& [v, _] : (*this)[u]) cum_l.push_back(op(cum_l.back(), v == p ? from_p : to_par[v]));
            T cum_r = e();
            for (int i = sz - 1; i >= 0; --i) {
                const auto& [v, w] = (*this)[u][i];
                if (v == p) {
                    cum_r = op(from_p, cum_r);
                } else {
                    T from_u = F(G(op(cum_l[i], cum_r), u, v), u, v, w);
                    dp[v] = op(dp[v], from_u);
                    dfs(v, u, from_u);
                    cum_r = op(to_par[v], cum_r);
                }
            }
        }
};
using S = mint;
using E = nullptr_t;
S op(S x, S y) {
    return x * y;
}
S e() {
    return 1;
}
S G(S x, int u, int fa) {
    return x;
}
S F(S x, int u, int fa, E w) {
    return x + 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;

    mint::set_mod(m);

    ReRooting<mint, op, e, G, E, F> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        g.add_edge(x, y, nullptr);
    }

    for (mint e : g.get()) {
        std::cout << e.val() << '\n';
    }

    return 0;
}
