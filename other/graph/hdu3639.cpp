#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/HDU-3639

void wt(vector<int> &a) {
	for (int x : a) 
		cout << x << ' ';
	cout << '\n';
}

struct SCC {
	int n, cnt = 0;
	vector<pair<int, int>> edges;
	vector<int> low, dfn, ids, in, out;
	explicit SCC(int n) : n(n), low(n), dfn(n, -1), ids(n) {}
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
		for (auto &it : edges) {
			int x = ids[it.first], y = ids[it.second];
			if (x != y) in[y]++, out[x]++;
		}
		return groups;
	}
};


void solve() {
	int n, m;
	cin >> n >> m;
	SCC c(n);
	vector<array<int, 2>> es(m);
	for (int i = 0, u, v; i < m; ++i) {
		cin >> u >> v;
		c.add_edge(u, v);
		es[i] = {u, v};
	}
	auto p = c.scc();
	n = c.cnt;
	vector<vector<int>> g(n);

	vector<int> f(n);
	for (int i = 0; i < n; ++i) {
		f[i] = p[i].size() - 1;
	}

	for (auto &e : es) {
		int u = c.ids[e[0]], v = c.ids[e[1]];
		if (u != v) {
			g[v].push_back(u);
		}
	}
	vector<int> vis(n);

	function<void(int, int)> dfs = [&](int i, int u) {
		vis[u] = 1;
		if (u != i) f[i] += p[u].size();
		for (int v : g[u]) {
			if (!vis[v]) dfs(i, v);
		}
	};
	for (int i = 0; i < n; i++) {
		if (c.in[i] == 0) continue;
		vis.assign(n, 0);
		dfs(i, i);
	}

	int mx = 0;
	for (int i = 0; i < n; ++i) {
	    if (f[i] > mx) mx = f[i];
	}

	cout << mx << '\n';

	vector<int> ans;

	for (int i = 0; i < n; ++i) {
	    if (f[i] == mx) {
	    	for (auto &x : p[i]) 
	    		ans.push_back(x);
	    }	
	}
	sort(ans.begin(), ans.end());
	for (int i = 0, n = ans.size(); i < n; ++i) {
		cout << ans[i] << " \n"[i == n - 1];
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(nullptr);

	int t;
	cin >> t;

	for (int i = 1; i <= t; ++i) {
		cout << "Case " << i << ": ";
		solve();
	}

	return 0;
}
