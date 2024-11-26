#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351155

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, root = 0;
	cin >> n;
	vector<vector<int>> g(n);
	vector<int> color(n);
	for (int i = 0, p, c; i < n; ++i) {
		cin >> p >> c;
		p--;
		if (p == -1) root = i;
		else {
			g[p].push_back(i);
		}
		color[i] = c;
	}

	vector<int> ans(n);
	vector<set<int>> s(n);
	function<void(int)> dfs = [&](int u) {
		s[u].insert(color[u]);
		for (auto &v : g[u]) {
			dfs(v);
			if (s[u].size() < s[v].size()) {
				s[u].swap(s[v]);
			}
			s[u].insert(s[v].begin(), s[v].end());
			s[v].clear();
		}
		ans[u] = s[u].size();
	};
	dfs(root);
	for (int i = 0; i < n; ++i) {
		cout << ans[i] << " \n"[i == n - 1];
	}
}

