#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Edcc {
    int n, m = 0, dcc_cnt = 0, init = 0;
    vector<vector<pair<int,int>>> g;
    vector<array<int, 2>> elist;
    vector<int> dfn, low, ids, deg;
    vector<bool> is_bridge;

    Edcc(int n = 0): n(n), dfn(n, -1), low(n), g(n), ids(n){}

    void add_edge(int a, int b) {
        g[a].emplace_back(b, m);
        g[b].emplace_back(a, m);
        elist.push_back({a, b});
        m++;
    }

    void get_ids() {
        init = 1;
        vector<bool> visited(n, false);
        is_bridge.assign(m, false);
        vector<int> stk;
        int now_dfn = 0;

        function<void(int, int)> dfs = [&](int u, int fa) {
            visited[u] = true;
            stk.push_back(u);
            low[u] = dfn[u] = now_dfn++;
            int pa_cnt = 0;
            for (auto &[v, id]: g[u]) {
                if (v == fa && pa_cnt++ == 0) continue;
                if (visited[v]) {
                    low[u] = min(low[u], dfn[v]);
                } else {
                    dfs(v, u);
                    is_bridge[id] = low[v] > dfn[u];
                    low[u] = min(low[u], low[v]);
                }
            }
            if (dfn[u] == low[u]) {
                while (true) {
                    int v = stk.back();
                    stk.pop_back();
                    ids[v] = dcc_cnt;
                    if (u == v) break;
                }
                dcc_cnt ++;
            }
        };
        
        for (int i = 0; i < n; i++)
            if (!~dfn[i])
                dfs(i, -1);
    }

    vector<vector<int>> edcc() {
        if (!init) get_ids();
        vector<vector<int>> groups(dcc_cnt);
        for (int i = 0; i < n; ++i) {
            groups[ids[i]].push_back(i);
        }
        deg.assign(dcc_cnt, 0);
        for (int i = 0; i < m; ++i) {
            if (is_bridge[i]) {
                deg[ids[elist[i][0]]]++;
                deg[ids[elist[i][1]]]++;
            }
        }
        return groups;
    }

    vector<vector<int>> bridge_tree() {
        if (!init) get_ids();
        vector<vector<int>> tr(dcc_cnt);
        for (int i = 0; i < m; ++i) {
            if (is_bridge[i]) {
                int x = ids[elist[i][0]], y = ids[elist[i][1]];
                tr[x].push_back(y);
                tr[y].push_back(x);
            }
        }
        return tr;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Edcc g(n);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v;
        g.add_edge(--u, --v);
    }

    auto dcc = g.edcc();
    cout << dcc.size() << '\n';
    for (auto &v : dcc) {
    	cout << v.size();
    	for (auto &x : v) {
    		cout << ' ' << x + 1;
    	}
    	cout << '\n';
    }

    return 0;
}
