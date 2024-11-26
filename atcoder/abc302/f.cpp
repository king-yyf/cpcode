#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
    cin >> n >> m;
    BFS g(n + m);
    for (int i = 0, k; i < n; ++i) {
        cin >> k;
        for (int j = 0, v; j < k; ++j) {
            cin >> v;
            g.add_edge(m + i, --v);
        }
    }
    auto d = g.bfs(0);
    if (d[m - 1] == g.unreachable) cout << "-1";
    else cout << d[m - 1] / 2 - 1;
    return 0;
}
