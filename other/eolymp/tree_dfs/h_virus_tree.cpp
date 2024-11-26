#include<bits/stdc++.h>
using namespace std;

/*
给你一棵树，它有n个顶点和n−1条边。顶点编号为1到n.

有k种颜色，对于树中的每个顶点，您将从k种颜色中选择一种来染色，以便满足以下条件：

如果两个不同顶点x和y之间的距离小于或等于2，则x和y具有不同的颜色。

有多少种方法可以画这棵树？求取模1e9+7的计数

*/

// https://www.eolymp.com/en/contests/30114/problems/351161

const int mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	vector<vector<int>> g(n);

	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vector<long long> c(n);
	function<long long(int, int, int)> dfs = [&](int u, int c, int p) {
		long long res = c;
		int used = 1;
		if (p >= 0) used++;
		for (int v : g[u]) if (v != p) {
			res = (res * dfs(v, k - used, u)) % mod;
			used++;
		}
		return res;
	};

	cout << dfs(0, k, -1) << "\n";

}