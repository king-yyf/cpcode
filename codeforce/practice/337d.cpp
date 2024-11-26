#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
    for(int x:a)cout<<x<<' ';cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m, d;
    const int inf = 1e9;
    cin >> n >> m >> d;
    vector<int> d1(n, -inf), d2(n, -inf), up(n, -inf), p(n);
    for (int i = 0, x; i < m; ++i) {
        cin >> x;
        x--;
        d1[x] = 0, up[x] = 0;
    }
    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    function<void(int, int)> dfs = [&](int u, int fa) {
        for (auto & v : g[u]) if (v != fa) {
            dfs(v, u);
            int d = d1[v]+1;
            if(d>=d1[u]){
                d2[u]=d1[u],d1[u]=d,p[u]=v;
            }else if(d>d2[u]){
                d2[u]=d;
            }
        }
    };
    dfs(0, -1);

    function<void(int, int)> dfs2 = [&](int u, int fa) {
        for (auto & v : g[u]) if (v != fa) {
            int d = p[u] == v ? d2[u] : d1[u];
            up[v] = max(up[u], d) + 1;
            dfs2(v, u);
        }
    };
    dfs2(0, -1);

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (max(d1[i], up[i]) <= d) ans++;    
    }
    cout << ans << '\n';

    return 0;
}
