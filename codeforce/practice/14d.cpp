#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/contest/14/problem/D

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
    
    int n;
    cin >> n;
    
    vector<array<int, 2>> es(n - 1);
    for (auto &[x, y] : es) {
    	cin >> x >> y;
    	x--, y--;
    }
    

    auto get_diag = [&](auto &g, int x) {
    	auto d = g.bfs(x);
    	int p = max_element(d.begin(), d.end()) - d.begin();
    	d = g.bfs(p);
    	return *max_element(d.begin(), d.end());
    };

    int ans = 0;
    
    for (int i = 0; i < n - 1; ++i) {
    	BFS g(n);
    	for (int j = 0; j < n - 1; ++j) {
    		if (i != j) g.add_edge(es[j][0], es[j][1]);
    	}
    	auto x = get_diag(g, es[i][0]);
    	auto y = get_diag(g, es[i][1]);
    	ans = max(ans, x * y);
    }

    cout << ans << '\n';

    return 0;
}
