#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin>>n;
    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }
    vector<long long> p(n), d(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
    	for(int v: g[u])if(v!=fa){
    		dfs(v,u);
    		d[u] += d[v] + p[v];
    		p[u] += p[v];
    	}
    	p[u]++;
    };
    dfs(0, -1);

    function<void(int, int)> dfs2 = [&](int u, int fa) {
    	for (int v : g[u]) if (v != fa) {
    		d[v] = d[u] - p[v] + n - p[v];
    		dfs2(v, u);
    	}
    };
    dfs2(0, -1);
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " \n"[i == n - 1];	
    }
    return 0;
}
