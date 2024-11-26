#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, u, v, c;
    cin >> n;

    vector<vector<pair<int, int> >> g(n);
    
    for (int i = 1; i < n ; ++i) {
        cin >> u >> v >> c;
        u--,v--;
        g[u].emplace_back(v,c);
        g[v].emplace_back(u,c);
    }
    vector<long long> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i];
    }

    vector<long long> d1(n), d2(n), p(n), up(n);

    function<void(int, int)> dfs = [&](int u, int fa) {
        for (auto &[v, c] : g[u]) if (v != fa) {
            dfs(v, u);
            long long d = max(w[v], d1[v]) + c;
            if (d >= d1[u]) {
                d2[u] = d1[u], d1[u] = d, p[u] = v;
            } else if (d >= d2[u]) {
                d2[u] = d;
            }
        }
    };

    function<void(int, int)> dfs2 = [&](int u, int fa) {
        for (auto &[v, c]: g[u]) if (v != fa) {
            long long d = p[u] == v ? d2[u] : d1[u];
            up[v] = max({w[u], d, up[u]}) + c;
            dfs2(v, u);
        }
    };

    dfs(0,-1);
    dfs2(0,-1);
  
    for(int i=0;i<n;++i){
        cout<<max(d1[i],up[i])<<"\n";
    }
    return 0;
}
