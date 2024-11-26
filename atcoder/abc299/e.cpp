#include <bits/stdc++.h>

using i64 = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int N, M;
    std::cin >> N >> M;
    
    std::vector<std::vector<int>> adj(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        std::cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    std::vector<bool> black(N, true);
    int K;
    std::cin >> K;
    
    std::vector<int> p(K), d(K);
    for (int i = 0; i < K; i++) {
        std::cin >> p[i] >> d[i];
        p[i]--;
        
        std::vector<int> dis(N, -1);
        std::queue<int> q;
        dis[p[i]] = 0;
        q.push(p[i]);
        
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            
            if (dis[x] < d[i]) {
                black[x] = false;
            }
            for (auto y : adj[x]) {
                if (dis[y] == -1) {
                    dis[y] = dis[x] + 1;
                    q.push(y);
                }
            }
        }
    }
    
    std::queue<int> q;
    std::vector<int> dis(N, -1);
    for (int i = 0; i < N; i++) {
        if (black[i]) {
            q.push(i);
            dis[i] = 0;
        }
    }
    
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        
        for (auto y : adj[x]) {
            if (dis[y] == -1) {
                dis[y] = dis[x] + 1;
                q.push(y);
            }
        }
    }
    
    for (int i = 0; i < K; i++) {
        if (dis[p[i]] != d[i]) {
            std::cout << "No\n";
            return 0;
        }
    }
    
    std::cout << "Yes\n";
    for (int i = 0; i < N; i++) {
        std::cout << black[i];
    }
    std::cout << "\n";
    
    return 0;
}