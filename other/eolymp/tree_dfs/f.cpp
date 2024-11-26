#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351159

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<vector<pair<int,int>>> g(n);
	
	int ans = 0;
	for (int i = 0,u,v,w; i < n-1; ++i) {
		cin>>u>>v>>w;
		u--,v--;
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}

	vector<int> p(n);
	function<void(int, int)> dfs = [&](int u, int fa) {
		for(auto&[v,w]:g[u])if(v!=fa){
			p[v]=p[u]^w;
			dfs(v,u);
		}
	};
	

	dfs(0,-1);
	int x=count(p.begin(), p.end(),1);
	cout << x*1ll*(n-x) << "\n";
}