#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	int x,y;
	vector<vector<int>> g(n);
	for (int i = 0; i < n-1; ++i) {
		cin >> x >> y;
		x--,y--;
		g[x].push_back(y);
		g[y].push_back(x);
	}

	vector<int> a(n), mx(n);

	function<void(int,int)> dfs = [&](int u,int fa) {
		a[u] = 1;
		for (auto v:g[u]) if(v!=fa){
			dfs(v,u);
			a[u]+=a[v];
			mx[u] = max(mx[u], a[v]);
		}
	};

	dfs(0,-1);

	int mn = n;

	for (int i = 0; i <n; ++i){
		int x = mx[i], y = n - a[i];
		mn = min(mn, max(x, y));
	}
	cout<<mn;
}