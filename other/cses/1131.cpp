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


    int d = 0, x = 0;
    function<void(int, int, int)> dfs = [&](int u, int fa, int dep) {
        for (auto &v : g[u]) if (v != fa) {
            dfs(v, u, dep + 1);
        }
        if (dep > d) d = dep, x = u;
    };
    dfs(0, -1, 0);

    dfs(x, -1, 0);

    cout << d << "\n";

    return 0;
}
