#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	int x, y, w,ans=0;
	vector<vector<pair<int, int>>> g(n);
	for (int i = 0; i < n - 1; ++i) {
		cin >> x >> y >> w;
		x--, y--;
		g[x].emplace_back(y, w);
		g[y].emplace_back(x, w);
	}

	function<int(int, int)> dfs = [&](int u, int fa) {
		int d1 = 0, d2 = 0;
		for (auto [v, c] : g[u]) 
			if (v != fa) {
				int d = dfs(v, u) + c;
				if (d >= d1) {
					d2 = d1, d1 = d;
				}else if(d>d2){
					d2=d;
				}
			}
		ans=max(ans,d1+d2);
		return d1;
	};

	dfs(0, -1);

	
	cout << ans;
}