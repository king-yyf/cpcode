#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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

// dp[v]=g( op(f(dp[c1], v1),  f(dp[c2], v2) , ... f(dp[c2], v2)), v)
using S = pair<int,int>;
vector<int> a;
const int inf=2e9;
using E = nullptr_t;
S op(S x, S y) {
    return S{max(x.first,y.first),max(x.second,y.second)};
}
S e() {
    return {-inf,-inf};
}
S G(S x, int u, int fa) {
    return x;
}
S F(S x, int u, int fa, E w) {
    return x;
}
// ReRooting<S, op, e, G, E, F> g(n);


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    
    ReRooting<S, op, e, G, E, F> g(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        u--, v--;
        g.add_edge(u, v, nullptr);
    }

    for (auto &p : g.get()) {
        cout << p << ' ';
    }

    cout << '\n';

    return 0;
}
