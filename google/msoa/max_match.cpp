#include<bits/stdc++.h>
using namespace std;

int maxMatch(vector<vector<int>> &g,int n1) {
    int n = g.size(), ans = 0;
    vector<int> vis(n), f(n, -1);

    function<bool(int)> dfs = [&](int u) {
        for(auto& v: g[u]) {
            if(vis[v]) continue;
            vis[v] = 1;
            if (f[v] == -1 || dfs(f[v])) {
                f[v] = u;
                return true;
            }
        }
        return false;
    };

    for (int i = 0; i < n1; ++i) {
        vis.assign(n, 0);
        if (dfs(i)) ans++;
    }
    return ans;
}

int main() {

}