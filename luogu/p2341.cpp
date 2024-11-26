#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a) {
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " \n"[i == n - 1];    
    }
}

struct SCC {
    int n, cnt = 0;
    vector<pair<int, int>> edges;
    vector<int> low, dfn, ids, in, out;
    explicit SCC(int n) : n(n), low(n), dfn(n, -1), ids(n){}
    void add_edge(int from, int to) { edges.push_back({from, to}); }

    void scc_ids() {
        vector<int> start(n + 1), elist(edges.size()), visited;
        for (auto &e : edges) 
            start[e.first + 1]++;
        for (int i = 1; i <= n; ++i) 
            start[i] += start[i - 1];
        auto counter = start;
        for (auto &e : edges)
            elist[counter[e.first]++] = e.second;
        int now_dfn = 0;
        visited.reserve(n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = dfn[v] = now_dfn++;
            visited.push_back(v);
            for (int i = start[v]; i < start[v + 1]; i++) {
                auto to = elist[i];
                if (dfn[to] == -1) {
                    self(self, to);
                    low[v] = min(low[v], low[to]);
                } else {
                    low[v] = min(low[v], dfn[to]);
                }
            }
            if (low[v] == dfn[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    dfn[u] = n, ids[u] = cnt;
                    if (u == v) break;
                }
                cnt++;
            }
        };
        for (int i = 0; i < n; i++) if (dfn[i] == -1) dfs(dfs, i);
        for (auto& x : ids) x = cnt - 1 - x;
    }

    vector<vector<int>> scc() {
        scc_ids();
        vector<vector<int>> groups(cnt);
        for (int i = 0; i < n; i++) {
            groups[ids[i]].push_back(i);
        }
        in.assign(cnt, 0), out.assign(cnt, 0);
        for (auto &[from, to]: edges) {
            int x = ids[from], y = ids[to];
            if (x != y) in[y]++, out[x]++;
        }
        return groups;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    SCC g(n);
    for(int i = 0, u, v; i < m; ++i) {
       cin >> u >> v;
       u--,v--;
       g.add_edge(u, v);
    }
    auto a = g.scc();
    int p = 0, q = 0;
    for (int i = 0; i < g.cnt; ++i) {
        if (g.out[i] == 0) p++, q += a[i].size();
    }
    cout << (p > 1 ? 0 : q) << "\n";
    return 0;
}
