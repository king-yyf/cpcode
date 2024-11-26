#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    
    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u;
    	u--;
    	g[u].push_back(i);
    }

    vector<int> sz(n);

    function<void(int)> dfs = [&](int u) {
    	sz[u] = 1;
    	for (int v: g[u]) {
    		dfs(v);
    		sz[u] += sz[v];
    	}
    };
    dfs(0);

    for (int i = 0; i < n; ++i) {
        cout << sz[i] - 1<< " \n"[i == n - 1];	
    }
    return 0;
}
