#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct ComplementBFS {
    static constexpr int unreachable = -1;

    ComplementBFS(int n = 0) : n(n), g(n) {}
    template <typename Edges>
    ComplementBFS(int n, const Edges &edges) : ComplementBFS(n) {
        for (const auto &[u, v] : edges) add_edge(u, v);
    }
    ComplementBFS(const std::vector<std::vector<int>>& g) : n(g.size()), g(g) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> distance(const std::vector<int>& src) const {
        std::vector<int> s = [&] {
            std::vector<int8_t> is_src(n);
            for (int v : src) is_src[v] = true;
            std::vector<int> s;
            for (int i = 0; i < n; ++i) if (not is_src[i]) s.push_back(i);
            return s;
        }();

        std::vector<int> dist(n, unreachable);
        for (int v : src) dist[v] = 0;

        std::vector<int8_t> adj(n);
        std::deque<int> dq(src.begin(), src.end());
        while (dq.size()) {
            int u = dq.front();
            dq.pop_front();
            for (int v : g[u]) adj[v] = true;
            std::size_t nsiz = std::partition(s.begin(), s.end(), [&adj](int v) { return adj[v]; }) - s.begin();
            for (; s.size() > nsiz; s.pop_back()) {
                int v = s.back();
                dist[v] = dist[u] + 1, dq.push_back(v);
            }
            for (int v : g[u]) adj[v] = false;
        }
        return dist;
    }
    std::vector<int> distance(int s) const {
        return distance(std::vector<int>{ s });
    }

    std::vector<std::vector<int>> connected_components() const {
        std::vector<std::vector<int>> res;

        std::vector<int8_t> vis(n, false);

        std::vector<int> s(n);
        std::iota(s.begin(), s.end(), 0);

        std::vector<int8_t> adj(n);
        for (int i = 0; i < n; ++i) if (not vis[i]) {
            s.erase(std::find(s.begin(), s.end(), i));
            auto& cmp = res.emplace_back();
            std::deque<int> dq{ i };
            while (dq.size()) {
                int u = dq.front();
                dq.pop_front();
                cmp.push_back(u);
                vis[u] = true;
                for (int v : g[u]) adj[v] = true;
                auto it = std::partition(s.begin(), s.end(), [&adj](int v) { return adj[v]; });
                std::move(it, s.end(), std::back_inserter(dq));
                s.erase(it, s.end());
                for (int v : g[u]) adj[v] = false;
            }
        }
        return res;
    }
private:
    int n;
    std::vector<std::vector<int>> g;
};

struct BFS {
    static constexpr int unreachable = -1;

    BFS(int n = 0) : n(n), g(n) {}
    template <typename Edges>
    BFS(int n, const Edges& edges) : BFS(n) { for (const auto& [u, v] : edges) add_edge(u, v);}
    BFS(const vector<vector<int>>& g) : n(g.size()), g(g) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> bfs(const vector<int>& src) const {
        vector<int> dist(n, unreachable);
        queue<int> q;
        for (int v : src) {
            dist[v] = 0;
            q.push(v);
        }
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) if (dist[v] == unreachable) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return dist;
    }
    vector<int> bfs(int s) const { return bfs(vector<int>{ s });}

    vector<vector<int>> connected_components() const {
        vector<vector<int>> res;
        vector<int8_t> vis(n, false);
        for (int i = 0; i < n; ++i) if (not exchange(vis[i], true)) {
            auto& cmp = res.emplace_back();
            queue<int> q;
            q.push(i);
            while (q.size()) {
                int u = q.front();
                q.pop();
                cmp.push_back(u);
                for (int v : g[u]) if (not exchange(vis[v], true)) {
                    q.push(v);
                }
            }
        }
        return res;
    }
private:
    int n;
    vector<vector<int>> g;
};

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    std::vector<int> res = [rec = [](auto rec, const std::vector<std::vector<int>> &g) -> std::vector<int> {
        const int n = g.size();
        if (n == 1) return { 0, 0 };
        auto cmps = BFS{g}.connected_components();
        if (cmps.size() == 1) {
            auto ccmps = ComplementBFS{g}.connected_components();
            assert(ccmps.size() != 1);
            std::vector<int> pd { 0 };
            std::vector<int8_t> in(n);
            std::vector<int> idx(n);
            for (const auto &cmp : ccmps) {
                const int siz = cmp.size();
                for (int i = 0; i < siz; ++i) {
                    idx[cmp[i]] = i;
                }
                std::vector<std::vector<int>> h(siz);
                for (int v : cmp) in[v] = true;
                for (int u : cmp) for (int v : g[u]) if (in[v]) {
                    h[idx[u]].push_back(idx[v]);
                }
                for (int v : cmp) in[v] = false;
                std::vector<int> val = rec(rec, h);
                const int l = pd.size() - 1, r = val.size() - 1;
                std::vector<int> dp(l + r + 1);
                for (int i = 0; i <= l; ++i) {
                    for (int j = 0; j <= r; ++j) {
                        dp[i + j] = std::max(dp[i + j], pd[i] + val[j] + i * (r - j) + (l - i) * j);
                    }
                }
                pd.swap(dp);
            }
            return pd;
        } else {
            std::vector<int> pd{ 0 };
            std::vector<int> idx(n);
            for (const auto &cmp : cmps) {
                const int siz = cmp.size();
                for (int i = 0; i < siz; ++i) idx[cmp[i]] = i;
                std::vector<std::vector<int>> h(siz);
                for (int u : cmp) for (int v : g[u]) {
                    h[idx[u]].push_back(idx[v]);
                }
                std::vector<int> val = rec(rec, h);
                const int l = pd.size() - 1, r = val.size() - 1;
                std::vector<int> dp(l + r + 1);
                for (int i = 0; i <= l; ++i) {
                    for (int j = 0; j <= r; ++j) {
                        dp[i + j] = std::max(dp[i + j], pd[i] + val[j]);
                    }
                }
                pd.swap(dp);
            }
            return pd;
        }
    }, &g]{ return rec(rec, g); }();

    std::cout << *std::max_element(res.begin(), res.end()) << std::endl;

}