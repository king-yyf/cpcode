#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.eolymp.com/en/contests/26719/problems/306684


template<typename T>
struct BFS01 {
    using E = pair<T, int>;
    int n;
    vector<vector<E>> g;    // cost, to
    BFS01(int N) : n(N), g(N){}

    void add_edge(int u, int v, T cost) {
        g[u].emplace_back(cost, v);
    }

    void add_bidir_edge(int u, int v, T cost) {
        add_edge(u, v, cost);
        add_edge(v, u, cost);
    }

    vector<T> bfs(int s) {  // unreachable : -1
        vector<T> d(n, T(-1));
        vector<int> vis(n, 0);
        deque<int> q;
        q.push_back(s);
        d[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop_front();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto &[c, v] : g[u]) {
                if (d[v] != T(-1) and d[v] <= d[u] + c) continue;
                d[v] = d[u] + c;
                if (c == 0) q.push_front(v);
                else q.push_back(v);
            }
        }
        return d;
    }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, a,b;
    cin >> n >> a>>b;
    
    BFS01<int> g(n);

    for (int i = 0, k; i < n; ++i) {
        cin >> k;
        for (int j = 0, x; j < k; ++j) {
            cin >> x;
            x--;
            g.add_edge(i,x,(j!=0));
        }
    }


    auto d = g.bfs(a-1);

    cout << d[b-1] << '\n';

    return 0;
}
