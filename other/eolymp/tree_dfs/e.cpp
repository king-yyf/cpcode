#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351157

int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);

	int n, x, y;
	cin >> n >> x >> y;
	x--,y--;

	vector<vector<int>> g(n);

	for(int i=1, u, v;i<n;++i){
		cin >> u >> v;
		u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	vector<int> pa(n);

	function<void(int,int)> dfs = [&](int u, int fa) {
		pa[u]=fa;
		for (int v:g[u]) if (v!=fa){
			dfs(v, u);
		}
	};
	dfs(x,-1);
	int t = pa[y];
	int s=y;
	while(pa[s]!=x)s=pa[s];

	int c1=0;
	function<void(int,int)> dfs1 = [&](int u, int fa) {
		c1++;
		for(int v:g[u]) if(v!=fa){
			dfs1(v,u);
		}
	};

	int c2=0;
	function<void(int,int)> dfs2 = [&](int u, int fa) {
		c2++;
		for(int v:g[u]) if(v!=fa){
			dfs2(v,u);
		}
	};

	dfs1(x,s);

	dfs2(y, t);

	cout << n * (n - 1ll) - c1 * 1ll * c2 << "\n";
}