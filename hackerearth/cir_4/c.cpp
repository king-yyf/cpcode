#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.hackerearth.com/challenges/competitive/april-circuits-23/algorithm/path-value-2-54ac4ca3/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m, s, e;
    cin >> n >> m >> s >> e;
    s--, e--;

    vector<vector<int>> g(n);

    for (int i = 0; i < m; ++i) {
    	int u, v;
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }
    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    auto chk = [&](int x) {
    	queue<int> q;
    	q.push(s);
    	vector<int> vis(n);
    	vis[s] = 1;
    	while(q.size()) {
    		auto u = q.front();
    		if (u == e) return 1;
    		q.pop();
    		for (int v : g[u]) if (!vis[v] && abs(a[v] - a[u]) <= x) {
    			q.push(v);
    			vis[v] = 1;
    		}
    	}
    	return 0;
    };

    int l = 0, r = 1e6, ans = r;

    while (l <= r) {
    	int md = (l + r) / 2;
    	if (chk(md)) {
    		ans = md;
    		r = md - 1;
    	}else l = md + 1;
    }

    cout << ans << '\n';
    return 0;
}
