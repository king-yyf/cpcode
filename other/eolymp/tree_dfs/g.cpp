#include<bits/stdc++.h>
using namespace std;

// https://www.eolymp.com/en/contests/30114/problems/351160

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<vector<int>> g(n);
	vector<int> c(n);
	for (int i = 0; i < n; ++i) {
		cin>>c[i];
	}

	for(int i = 0, u, v; i < n - 1; ++i){
		cin>>u>>v;u--,v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	map<int,int> mp;
	set<int> s;
	function<void(int, int)> dfs = [&](int u, int fa) {
		if (!mp.count(c[u])) {
			s.insert(u);
		}
		mp[c[u]]++;
		for(auto&v:g[u])if(v!=fa){
			dfs(v,u);
		}
		mp[c[u]]--;
		if(mp[c[u]]==0) mp.erase(c[u]);
	};
	
	dfs(0,-1);
	for (auto x : s) {
		cout << x + 1<< "\n";
	}
}

