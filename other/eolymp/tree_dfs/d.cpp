#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351157

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> g(n);

	for(int i=1;i<n;++i){
		int p;
		cin>>p;
		p--;
		g[p].push_back(i);
	}

	vector<int> c(n);
	for (int i = 0; i < n; ++i) {
		cin >> c[i];
		c[i]--;	
	}

	vector<int> ans(n,-1);
	vector<vector<int>> co(m);
	function<void(int)> dfs = [&](int u) {
		if (co[c[u]].size() > 0)
			ans[u]=co[c[u]].back()+1;
		co[c[u]].push_back(u);
		for (auto &v : g[u]) {
			dfs(v);
		}
		co[c[u]].pop_back();
	};

	dfs(0);

	for (int i = 0; i < n; ++i) {
		cout << ans[i] << " \n"[i == n - 1];	
	}

}