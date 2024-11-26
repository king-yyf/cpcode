#include <bits/stdc++.h>
using namespace std;

using ll = long long;

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
    

    vector<int> dp(n), t(n);

    vector<set<int>> s(n);

    function<void(int, int)> dfs = [&](int u, int fa) {
    	map<int, int> cnt;
    	if (g[u].size() == 1 && fa != -1) {
    		s[u].insert(0);
    		dp[u] = 1;
    	} 

    	for (int v : g[u]) if (v != fa) {
    		dfs(v, u);
    		dp[u] += dp[v] + 1;
    		if (s[u].size() < s[v].size()) {
    			swap(s[u], s[v]);
    			swap(t[u], t[v]);
    		}
    		for (auto x : s[v]) {
    			x ^= t[u] ^ t[v];
    			if (s[u].count(x)) {
    				cnt[x ^ t[u]]++;
    			} else {
    				s[u].insert(x);
    			}
    		}
    	}
    	if (!cnt.empty()) {
			int mx = 0;
			for (auto [_, x] : cnt) {
				mx = max(mx, x);
			}
			dp[u] -= mx + 1;
			s[u].clear();
			t[u] = a[u];
			for (auto [t, x] : cnt) {
				if (x == mx) {
					s[u].insert(t);
				}
			} 
		} else {
			dp[u] -= 1;
			t[u] ^= a[u];
		}

    };
    dfs(0, -1);

    int ans = dp[0] + !s[0].count(t[0]);

    cout << ans << '\n';

    return 0;
}
