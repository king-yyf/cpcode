#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.hackerearth.com/practice/algorithms/graphs/depth-first-search/practice-problems/algorithm/xorrrr-40caac1a/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
   	cin >> n;
    vector<vector<int>> g(n);

    vector<array<int,3>> es;
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    	es.push_back({u, v, u + v + 2});
    }

    int ans = 0;

    vector<int> siz(n), dep(n);

    function<void(int, int)> dfs = [&](int u, int fa) {
    	siz[u] = 1;
    	for (int v : g[u]) if (v != fa) {
    		dep[v] = dep[u] + 1;
    		dfs(v, u);
    		siz[u] += siz[v];
    	}
    };
    dfs(0, -1);

    for (auto &e : es) {
    	int u = e[0], v = e[1], x = e[2];
    	if (dep[u] > dep[v]) swap(u, v);

    	if (siz[v] * (n - siz[v]) & 1) {
    		ans ^= x;
    	}
    }

    cout << ans << '\n';

    return 0;
}
