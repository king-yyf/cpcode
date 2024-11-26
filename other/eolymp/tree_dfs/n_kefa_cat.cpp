#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351167

/*
一个由n个顶点组成的树，根节点是1，其中有若干个个顶点上有猫，每个叶节点有个餐厅，
如果从根节点到叶节点到路径上存在一条连续m只猫的路径，则无法到达叶节点，计算能到达的叶节点数目

2 ≤ n ≤ 2 * 1e5, 	1<=m<=n
*/

void wt(vector<int> &a) {
	for(int x : a) cout << x << " ";
		cout << "\n";
}

const int mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}

	vector<vector<int>> g(n);
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}


	vector<int> vis(n), p(n);
	function<void(int, int)> dfs = [&](int u, int fa) {
		if (g[u].size() == 1 && fa != -1) vis[u] = 1;
		for (int v : g[u]) if (v != fa) {
			if (a[v]) a[v] = a[u] + 1;
			p[v] = max({p[v], a[v], p[u]});
			dfs(v, u);
		}
 	};
	dfs(0, -1);

	int res = 0;

	for (int i = 0; i < n; ++i) {
		if (vis[i] && p[i] <= m) res++;
	}

	cout << res << "\n";
	return 0;
}

