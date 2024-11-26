#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1679

vector<int> findOrder(int n, vector<vector<int>>& pres) {
    vector<int> G[n], degree(n, 0), ans;
    for (auto& e : pres) {
        G[e[1]].push_back(e[0]);
        degree[e[0]]++;
    } 
    queue<int> que;
    for (int i = 0; i < n; ++i) 
        if (!degree[i]) que.push(i);

    while(!que.empty()){
        int tmp = que.front();
        ans.push_back(tmp);
        que.pop();
        for(int x : G[tmp]){
            if(--degree[x] == 0) que.push(x);
        }
    }
    return ans.size() == n ? ans : vector<int>();
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> g(m);

    for (int i = 0, u, v; i < m; ++i) {
    	cin >> u >> v;
    	g[i] = {--v, --u};
    }

    auto p = findOrder(n, g);

    if (p.size() == 0) {
    	cout << "IMPOSSIBLE\n";
    } else {
    	for (int x : p) cout << x + 1 << ' ';
    }

    return 0;
}
