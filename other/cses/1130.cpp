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
    int ans = 0;
    vector<int> vis(n);

    function<void(int, int)> dfs = [&](int u, int fa) {
    	for (int v : g[u]) if (v != fa) {
    		dfs(v, u);
    		if (!vis[v] && !vis[u]) {
    			ans++;
    			vis[v] = 1, vis[u] = 1;
    		}
    	}
    };
    dfs(0, -1);
    
    cout << ans << '\n';

    return 0;
}
