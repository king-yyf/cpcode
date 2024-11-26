#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
        in.assign(cnt, 0);
        for (auto& x : ids) {
            x = cnt - 1 - x;
            in[x]++;
        }
    }

    vector<vector<int>> scc(bool cal_degree = false) {
        scc_ids();
        vector<vector<int>> groups(cnt);
        for (int i = 0; i < cnt; ++i) groups[i].reserve(in[i]);
        for (int i = 0; i < n; i++) groups[ids[i]].push_back(i);
        if (cal_degree) {
            in.assign(cnt, 0), out.assign(cnt, 0);
            for (auto &[from, to]: edges) {
                int x = ids[from], y = ids[to];
                if (x != y) in[y]++, out[x]++;
            }
        }
        return groups;
    }
};

void solve() {
	int n, m;
    cin >> n >> m;
    SCC s(n);

    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
    	int u, v;
    	cin >> u >> v;
    	u--, v--;
    	s.add_edge(u, v);
    	g[u].push_back(v);
    }

    auto dag = s.scc();
    int k = dag.size();

    // 构建新的拓扑图
    vector<vector<int>> h(k);
    vector<char> has_loop(k, false);
    for (int i = 0; i < n; ++i) {
        for (int j : g[i]) {
            if (s.ids[i] == s.ids[j]) {
                has_loop[s.ids[i]] = true;
            } else {
                h[s.ids[i]].push_back(s.ids[j]);
            }
        }
    }
    int src = s.ids[0];
    vector<int> ans(k, 0);
    ans[src] = 1;
    for (int u = s.ids[0]; u < k; ++u) {
    	if (has_loop[u]) {
            ans[u] = 3;
        }
        for (int v : h[u]) {
            if (ans[u] == 1 and ans[v] == 1) {
                ans[v] = 2;
            } else {
            	ans[v] = max(ans[v], ans[u]);
            }
        }
    }
    replace(ans.begin(), ans.end(), 3, -1);
    vector<int> ans2(n);
    for (int i = 0; i < n; ++i) {
        ans2[i] = ans[s.ids[i]];
    }
    for (int i = 0; i < n; ++i) {
    	cout << ans2[i] << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	solve();
    }
    
    return 0;
}
