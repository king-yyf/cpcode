#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.codechef.com/problems/EXUND?tab=statement

void solve() {
	int n, k;
	cin >> n >> k;
	vector<vector<int>> g(n);

	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vector<int> d(n), cnt(n);
	function<void(int, int)> dfs = [&](int u, int fa) {
		for (int v : g[u]) if (v != fa) {
			dfs(v, u);
			d[u] = max(d[u], d[v] + 1);
		}
		cnt[d[u]]++;
	};
	dfs(0, -1);
	int ans = 0;
	for (int i = 0; i < k; ++i) {
		ans += cnt[i];
	}
	cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	solve();
    }

    return 0;
}
