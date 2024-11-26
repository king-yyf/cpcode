#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-2080

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;

    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }

    vector<map<int, int>> d(n);
    long long res = 0;
    function<void(int, int, int)> dfs = [&](int u, int fa, int dep) {
    	d[u].emplace(dep, 1);
    	for (int v : g[u]) if (v != fa) {
    		dfs(v, u, dep + 1);
    		if (d[u].size() < d[v].size()) swap(d[v], d[u]);
    		for (auto &[x, y] : d[v]) {
    			int p = k + dep * 2 - x;
    			if (d[u].count(p)) res += d[u][p] * 1ll * y;
    		}
    		for (auto &[x, y] : d[v]) {
    			if (d[u].count(x)) d[u][x] += y;
    			else d[u].emplace(x, y);
    		}
    		d[v].clear();
    	}
    };
    dfs(0, -1, 1);
    cout << res << '\n';

    return 0;
}
