#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351154

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	cout << fixed << setprecision(10);

	int n;
	cin >> n;
	vector<vector<pair<int,int>>> g(n);
	for (int i = 0, u,v,w; i < n - 1; ++i) {
		cin>>u>>v>>w;
		u--;v--;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}

	int p = 1e9;

	vector<int> siz(n);
	long long ans = 0;
	
	function<void(int, int)> dfs = [&](int u, int fa) {
		siz[u]=1;
		for (auto &[v,w]:g[u]) if(v!=fa){
			dfs(v, u);
			siz[u] += siz[v];
			ans += siz[v] * 1ll *(n - siz[v]) * w;
			ans %= p;
		}
	};

	dfs(0,-1);

	cout << ans << "\n";
}
