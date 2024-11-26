#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351162

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<vector<int>> g(n);

	for(int i=1, u, v;i<n;++i){
		cin >> u >> v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vector<int> p, dis(n), pa(n);

	function<void(int, int)> dfs = [&](int u, int fa) {
		pa[u] = fa;
		for (int v : g[u]) if (v != fa) {
			dis[v] = dis[u] + 1;
			dfs(v, u);
		}
		if (dis[u] > 2) p.push_back(u);
	};

	dfs(0,-1);

	int ans = 0;

	for (auto u : p) {
		if (dis[u] <= 2) continue;
		ans++;
		dis[pa[u]] = 1;
		for (int v : g[pa[u]]) {
			dis[v] = 2;
		}
	}

	cout << ans << "\n";
}