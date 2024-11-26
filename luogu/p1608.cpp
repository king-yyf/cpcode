#include<bits/stdc++.h>

using namespace std;

template<typename T>
struct Dijkstra {
    using E = pair<T, int>;
    int n;
    vector<vector<E>> g;    // cost, to
    Dijkstra(int N) : n(N), g(N){}

    void add_edge(int u, int v, T cost) {
        g[u].emplace_back(cost, v);
    }

    void add_bidir_edge(int u, int v, T cost) {
        add_edge(u, v, cost);
        add_edge(v, u, cost);
    }

    E dijkstra(int s) {  // unreachable : -1
        vector<T> d(n, T(-1)); 
        vector<int> ans(n);
        priority_queue<E, vector<E>, greater<E>> q;
        d[s] = 0, ans[s] = 1;
        q.emplace(0, s);
        while (!q.empty()) {
            auto [cost, u] = q.top();
            q.pop();
            if (d[u] < cost) continue;
            for (auto &[c, v] : g[u]) {
                if (d[v] == T(-1) || d[u] + c < d[v]) {
                    d[v] = d[u] + c;
                    ans[v] = d[v];
                    q.emplace(d[v], v);
                } else if ( d[u] + c == d[v]) {
                	ans[v] += ans[u];
                }
            }
        } 
        return {d[n - 1], ans[n - 1]};
    }
};

int main() {
	int n, m;
	cin >> n >> m;
	Dijkstra<int> d(n);
	for (int i = 0, u, v, w; i < m; ++i) {
		cin >> u >> v >> w;
		u--, v--;
		d.add_edge(u, v, w);
	}
	auto [dis, cnt] = d.dijkstra(0);
	cout << dis << " " << cnt << "\n";
}