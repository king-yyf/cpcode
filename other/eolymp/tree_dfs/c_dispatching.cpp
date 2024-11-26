#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351156

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> g(n);

	vector<int> c(n), le(n);

	for(int i=0, u ;i<n;++i){
		cin >> u >> c[i] >> le[i];
		u--;
		if(u>=0)g[u].push_back(i);
	}

	vector<long long> sum(n);
	vector<priority_queue<int>>  q(n); 
	long long ans = 0;

	function<void(int)> dfs = [&](int u) { 
		q[u].push(c[u]);
		sum[u] += c[u];
		for(int v : g[u]) {
			dfs(v);
			if (q[u].size()<q[v].size()){ 
				q[u].swap(q[v]);
			}
			while(q[v].size()){
				q[u].push(q[v].top());
				q[v].pop();
			}
			sum[u]+=sum[v];
		}
		while(sum[u] > m) {
			sum[u] -= q[u].top();
			q[u].pop();
		}
		if (le[u] * 1ll * q[u].size() > ans) {
			ans=le[u] * 1ll * q[u].size();
		}
	};

	dfs(0);


	cout << ans << "\n";
}