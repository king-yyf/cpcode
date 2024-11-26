#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://codeforces.com/problemset/problem/1092/F

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    
    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }

    vector<long long> p(n), s(n);
    vector<int> d(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
    	s[u] += a[u];
    	for (auto &v : g[u]) if (v != fa) {
    		d[v] = d[u] + 1;
    		dfs(v, u);
    		s[u] += s[v];
    	}
    };
    dfs(0, -1);
    for (int i = 0; i < n; ++i) {
    	p[0] += d[i] * 1ll * a[i];
    }

    long long ans = 0;
    function<void(int, int)> dfs1 = [&](int u, int fa) {
    	ans = max(ans, p[u]);
    	for (auto &v : g[u]) if (v != fa) {
    		p[v] = p[u] - s[v] + (s[0] - s[v]);
    		dfs1(v, u);
    	}
    };
    dfs1(0, -1);

    cout << ans << '\n';

    return 0;
}
