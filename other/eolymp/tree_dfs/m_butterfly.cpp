#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351166

/*
一个由n个顶点组成的树

一只蝴蝶从根节点飞向叶节点，可以从任意一个叶节点飞出，你需要在部分叶节点放置k个朋友，当蝴蝶开始出发时，所有朋友从叶节点向根节点行进

如果朋友和蝴蝶相遇，则蝴蝶飞行结束。

求需要的最少朋友数量，使得蝴蝶无论从哪个叶节点都飞不出。

*/

void wt(vector<int> &a) {
	for(int x : a) cout << x << " ";
		cout << "\n";
}

const int mod = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n;
	cin >> n;

	vector<vector<int>> g(n);
	for (int i = 1, u, v; i < n; ++i) {
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	const int inf = 1e9;
	
	vector<int> d(n), h(n, inf), f(n);
	function<void(int, int)> dfs = [&](int u, int fa) {
		if (g[u].size() == 1 && fa != -1) h[u] = 0;
		for (int v : g[u]) if (v != fa) {
			d[v] = d[u] + 1;
			dfs(v, u);
			h[u] = min(h[u], h[v] + 1);
		}
	};
	dfs(0, -1);

	function<void(int, int)> dfs2 = [&](int u, int fa) {
		for (int v : g[u]) if (v != fa) {
			dfs2(v, u);
			f[u] += f[v];
		}
		if (h[u] <= d[u]) f[u] = 1;
 	};
	dfs2(0, -1);

	cout << f[0] << "\n";
	return 0;
}

