#include <bits/stdc++.h>
using namespace std;

using ll = long long;

long long minTime(vector<int> a, vector<vector<int>>& edges){
    int n = a.size(), cnt = 0;
    vector<vector<int>> g(n);
    vector<int> deg(n);
    vector<long long> dp(n);
    for (auto & e : edges) {
        g[e[0]].push_back(e[1]);
        deg[e[1]]++;
    }
    queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (deg[i] == 0) {
            q.push(i);
            dp[i] = a[i];
            cnt++;
        }
    }

    while(q.size()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (--deg[v] == 0) {
                q.push(v);
                cnt++;
            }
            dp[v] = max(dp[v], dp[u] + a[v]);
        }
    }
    long long mx = (*max_element(dp.begin(), dp.end()));
    return cnt < n ? -1 : mx;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    vector<vector<int>> edges(m);
    for (int i = 0; i < m; ++i) {
    	int u, v;
    	cin >> u >> v;
    	edges[i] = {u, v};
    }

    int ans = minTime(a, edges);
    cout << ans << '\n';

    return 0;
}
