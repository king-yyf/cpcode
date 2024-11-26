#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}

void solve() {
    int n;
    cin >> n;

    vector<vector<pair<int,int> >> g(n);

    // int mx = 0;
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--,
        v--;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<int> p(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
        for(auto &[v,w] : g[u]) if (v != fa) {
            p[v] = p[u] ^ w;
            dfs(v, u);
        }
    };
    dfs(0, -1);

    map<int, pair<int,int> > mp;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int x = p[i] ^ p[j];
            if (mp.count(x)) {
                cout << i + 1 << ' ' << j + 1 << ' ' << mp[x].first << ' ' << mp[x].second << '\n';
                return;
            }
            mp[x] = {i + 1, j + 1};
        }
    }

    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}