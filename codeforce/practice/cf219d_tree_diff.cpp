#include <bits/stdc++.h>
using namespace std;

using ll = long long;


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> g(n);
    vector<pair<int,int> > es;
    
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
        es.emplace_back(u, v);
    }

    vector<int> in(n), out(n), pa(n, -1);
    int t = 0;
    
    function<void(int, int)> dfs = [&](int u, int fa) {
        pa[u] = fa;
        in[u] = t++;
        for (int v : g[u]) if (v != fa) {
            dfs(v, u);
        }
        out[u] = t;
    };
    dfs(0, -1);

    vector<int> d(n + 1);

    auto add = [&](int l, int r) {
        d[l]++, d[r]--;
    };

    for (auto & [u, v] : es) {
        if (pa[v] == u) {
            add(in[v], out[v]);
        } else {
            add(0, in[u]);
            add(out[u], n);
        }
    }
    
    for (int i = 0; i < n; ++i) 
        d[i + 1] += d[i];

    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = d[in[i]];    
    }

    int mn = *min_element(d.begin(), prev(d.end()));
    cout << mn << '\n';
    for (int i = 0; i < n; ++i) {
        if (ans[i] == mn) cout << i + 1 << ' ';	
    }
    return 0;
}
