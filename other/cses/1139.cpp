#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];	
    }

    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }

    vector<set<int>> p(n); 
    vector<int> ans(n);

    function<void(int, int)> dfs = [&](int u, int fa) {
    	p[u].insert(c[u]);
    	for (int v : g[u]) if (v != fa) {
    		dfs(v, u);
    		if(p[u].size() < p[v].size()) swap(p[u], p[v]);
    		p[u].insert(p[v].begin(), p[v].end());
    	}
    	ans[u] = p[u].size();
    };
    dfs(0, -1);

    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " \n"[i == n - 1];	
    }

    return 0;
}
