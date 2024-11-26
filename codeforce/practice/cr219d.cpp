#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin>>n;
    set<pair<int,int>> s;
    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    	s.insert({v, u});
    }
    
    vector<int> p(n);
    int cnt = 0, mn = 1e9;
    function<void(int, int)> dfs = [&](int u, int fa) {
    	for (auto &v: g[u]) if (v != fa){
    		if (s.count({u, v})) cnt++;
    		dfs(v,u);
    	}
    };
    dfs(0, -1);

    function<void(int, int)> dfs2 = [&](int u, int fa) {
    	p[u] = cnt;
    	mn = min(mn, cnt);
    	for (auto &v: g[u]) if (v != fa){
    		if (s.count({u, v})) cnt--;
    		if (s.count({v, u})) cnt++;
    		dfs2(v,u);
    		if (s.count({u, v})) cnt++;
    		if (s.count({v, u})) cnt--;
    	}
    };
    dfs2(0, -1);

    cout << mn << "\n";
    for (int i = 0; i < n; ++i) {
    	if (p[i] == mn) cout << i + 1 << ' ';
    }

    return 0;
}
