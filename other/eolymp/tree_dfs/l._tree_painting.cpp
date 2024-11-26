#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351165

/*
一个由n个顶点组成的树

最初，所有顶点都是白色的。在游戏的第一回合，您选择一个顶点并将其绘制为黑色。然后在每个回合中，选择与任何黑色顶点相邻的白色顶点（通过边连接），并将其绘制为黑色。
每次选择顶点时，获得的点数等于仅由包含所选顶点的白色顶点组成的连接组件的大小。当所有顶点都绘制为黑色时，游戏结束。
你的任务是最大化你获得的点数。
2 ≤ n ≤ 2 * 105
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
	vector<int> siz(n);
	function<void(int, int)> dfs = [&](int u, int fa) {
		siz[u] = 1;
		for (auto & v : g[u]) if (v != fa) {
			dfs(v, u);
			siz[u] += siz[v];
		}
	};
	dfs(0, -1);
	long long res = 0;
	vector<long long> s(n);
	s[0] = accumulate(siz.begin(), siz.end() , 0ll);
	function<void(int, int)> dfs2 = [&](int u, int fa) {
		res = max(res, s[u]);
		for (auto v: g[u]) if (v != fa) {
			s[v] = s[u] - siz[v] + n - siz[v];
			dfs2(v, u);
		}
	};
	dfs2(0, -1);

	cout << res << "\n";
	return 0;
}

