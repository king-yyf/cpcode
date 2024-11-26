#include<bits/stdc++.h>
using namespace std;

// problem : https://www.luogu.com.cn/problem/P4779

template<typename T>
struct BiDirDijkstra {
    using E = pair<T, int>;
    int n;
    vector<vector<E>> g, gr;
    BiDirDijkstra(int N) : n(N), g(N), gr(n) {}

    void add_edge(int u, int v, T cost) {
        g[u].emplace_back(cost, v);
        gr[v].emplace_back(cost, u);
    }

    T get(int s, int t) {
        priority_queue<E, vector<E>, greater<E>> q, qr;
        vector<T> d(n, T(-1)), dr(n, T(-1)); 
        vector<bool> vis(n), visr(n);
        d[s] = 0, dr[t] = 0;
        q.emplace(0, s); qr.emplace(0, t);
        bool ok = false;
        while (!q.empty() && !qr.empty()) {
            {
                auto [cost, u] = q.top();
                q.pop();
                if (visr[u]) {ok = true; break;}
                if (vis[u]) continue;
                vis[u] = true;
                for (auto &[c, v] : g[u]) {
                    if (d[v] == T(-1) || d[u] + c < d[v]) {
                        d[v] = d[u] + c;
                        q.emplace(d[v], v);
                    }
                }
            }
            {
                auto [cost, u] = qr.top();
                qr.pop();
                if (vis[u]) {ok = true; break;}
                if (visr[u]) continue;
                visr[u] = true;
                for (auto &[c, v] : gr[u]) {
                    if (dr[v] == T(-1) || dr[u] + c < dr[v]) {
                        dr[v] = dr[u] + c;
                        qr.emplace(dr[v], v);
                    }
                }
            }
        }
        if (!ok) return T(-1);
        T ans = T(-1);
        for (int i = 0; i < n; ++i) {
            if (d[i] == T(-1) || dr[i] == T(-1)) continue;
            if (ans == T(-1) || ans > d[i] + dr[i]) {
                ans = d[i] + dr[i];
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int n, m, s;
    cin >> n >> m >> s;
    BiDirDijkstra<int> d(n);
    for (int i = 0, u, v, c; i < m; ++i) {
        cin >> u >> v >> c;
        u--, v--;
        d.add_edge(u, v, c);
    }
    auto ans = d.get(s - 1);
    for (int i = 0; i < n; ++i) 
        cout << ans[i] << " \n"[i == n - 1];
    return 0;
}
