#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,m;
    cin>>n>>m;
    vector<array<int,2>> edges(m);

    for (int i = 0; i < m; ++i) {
    	int u, v;
    	cin >> u >> v;
    	u--, v--;
    	edges[i] = {u, v};
    }

    int l = 1, r = m, ans = -1;

    auto chk = [&](int x) -> bool {
    	vector<int> deg(n);
    	vector<vector<int>> g(n);
    	for (int i = 0; i < x; ++i) {
    		deg[edges[i][1]]++;
    		g[edges[i][0]].push_back(edges[i][1]);
    	}
    	queue<int> q;
    	for (int i = 0; i < n; ++i) {
    		if (deg[i] == 0) {
    			q.push(i);
    		}
    	}

    	while (q.size()) {
    		if (q.size() > 1) return false;
    		int u = q.front();
    		q.pop();
    		for (int v : g[u]) {
    			deg[v]--;
    			if (deg[v] == 0) q.push(v);
    		}
    	}
    	return true;
    };

    while (l <= r) {
    	int md = (l + r) / 2;
    	if (chk(md)) {
    		ans = md;
    		r = md - 1;
    	} else l = md + 1;
    }

    cout << ans << '\n';

    return 0;
}
