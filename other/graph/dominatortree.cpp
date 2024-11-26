#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://judge.yosupo.jp/problem/dominatortree

struct dominator_tree {
    explicit dominator_tree(int n)
        : n(n), fa(n), idom(n, -1), sdom(n, -1), dsu(n), label(n), g(n), gr(n) {
        order_.reserve(n);
        iota(dsu.begin(), dsu.end(), 0);
        iota(label.begin(), label.end(), 0);
    }
    void add_edge(int from, int to) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        g[from].push_back(to);
        gr[to].push_back(from);
    }
    void get(int root) {
        assert(0 <= root && root < n);
        dfs(root);
        vector<vector<int>> bucket(n);
        vector<int> x(n);
        for (auto i = static_cast<int>(order_.size()) - 1; i >= 0; --i) {
            auto u = order_[i];
            for (auto v : gr[u]) {
                if (~sdom[v]) sdom[u] = std::min(sdom[u], sdom[eval(v)]);
            }
            bucket[order_[sdom[u]]].push_back(u);
            for (auto v : bucket[fa[u]]) 
            	x[v] = eval(v);
            bucket[fa[u]].clear();
            link(fa[u], u);
        }
        for (auto i = 1; i < static_cast<int>(order_.size()); ++i) {
            auto u = order_[i], v = x[u];
            idom[u] = (sdom[u] == sdom[v] ? sdom[u] : idom[v]);
        }
        for (auto i = 1; i < static_cast<int>(order_.size()); ++i) {
            auto u = order_[i];
            idom[u] = order_[idom[u]];
        }
        idom[root] = root;
    }
    int operator[](int u) const {
        assert(0 <= u && u < n);
        return idom[u];
    }

private:
    void dfs(int u) {
        sdom[u] = static_cast<int>(order_.size());
        order_.push_back(u);
        for (auto v : g[u]) if (!~sdom[v]) {
            fa[v] = u;
            dfs(v);
        }
    }
    int find(int u) {
        if (dsu[u] == u) return u;
        auto root = find(dsu[u]);
        if (sdom[label[u]] > sdom[label[dsu[u]]]) label[u] = label[dsu[u]];
        return dsu[u] = root;
    }
    int eval(int u) {
        find(u);
        return label[u];
    }
    void link(int u, int v) { dsu[v] = u; }
    int n;
    vector<int> order_, fa, idom, sdom, dsu, label;
    vector<vector<int>> g, gr;
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    std::cin.tie(0)->sync_with_stdio(0);
    int N, M, S;
    std::cin >> N >> M >> S;
    dominator_tree dt(N);
    for (auto i = 0; i < M; ++i) {
        int a, b;
        std::cin >> a >> b;
        dt.add_edge(a, b);
    }
    dt.get(S);
    for (auto i = 0; i < N; ++i) {
        std::cout << dt[i] << ' ';
    }

    return 0;
}
