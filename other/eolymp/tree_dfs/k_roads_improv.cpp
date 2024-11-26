#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351164

/*
给你一棵树，它有n个顶点和n−1条边。(2 ≤ n ≤ 2 * 1e5)

初始时，所有边都是坏的，你要改善其中一些边，如果从顶点1到任何其他顶点的路径最多包含一条坏边，则称改善是好的，

求有多少种改善是好的方案，模1e9+7

*/

const int mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<vector<int>> g(n);
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u;
		u--;
		g[u].push_back(i);
	}

	vector<long long> p(n, 1);
	
	function<void(int, int)> dfs = [&](int u, int fa) {
		for (int v : g[u]) {
			dfs(v, u);
			p[u] = (p[u] * (p[v] + 1)) % mod;
		}
	};
	dfs(0, -1);

	cout << p[0] << "\n";

}