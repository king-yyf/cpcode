#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*
题意：n个节点的树，1是根，给每个节点赋值。使其满足：
1. 根结点值为x
2. 每个节点的直接儿子的权值两两两不同
3. 每个节点的所有儿子节点的gcd等于该节点的值
4. 求所有节点权值和的最小值，模 1e9+7

link: https://www.codechef.com/problems/THOUSES
rating: 2023
*/

void solve() {
	int n, x;
	cin >> n >> x;
	vector<vector<int>> g(n);

	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	vector<long long> res(n, 1);
	function<void(int, int)> dfs = [&](int u, int fa) {
		vector<long long> tmp;
		for (int v : g[u]) if (v != fa) {
			dfs(v, u);
			tmp.push_back(res[v]);
		}
		sort(tmp.rbegin(), tmp.rend());
		for (int i = 0; i < tmp.size(); ++i) {
			res[u] += tmp[i] * (i + 1);
		}
	};
	dfs(0, -1);
	for (int i = 0; i < n; ++i) {
		cout << res[i] << " \n"[i == n - 1];
	}
	long long ans = (res[0] % 1000000007) * 1ll * x % 1000000007;
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
