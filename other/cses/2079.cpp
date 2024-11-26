#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
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
	int mn = n, ans = -1;
	for (int i = 0; i <n; ++i){
		int x = max(mx[i], n - a[i]);
	    if (x < mn) {
	    	ans = i + 1, mn = x;
	    }
	}
    
    cout << ans << "\n";

    return 0;
}
