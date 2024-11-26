#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 200005;
vector<int> graph[MAXN];
int dp[MAXN], depth[MAXN], sz[MAXN];
int count[MAXN];

// Calculate depth and subtree size of each node using DFS
void dfs(int u, int p) {
    depth[u] = 0;
    sz[u] = 1;

    for (int v : graph[u]) {
        if (v == p) continue;
        dfs(v, u);
        depth[u] = max(depth[u], depth[v] + 1);
        sz[u] += sz[v];
    }
}

// Calculate dp values
void calculateDP(int u, int p, int d) {
    dp[u] = d;
    count[d]++;

    for (int v : graph[u]) {
        if (v == p) continue;
        int child_depth = d + 1 + max(0, depth[u] - 1 - sz[v]);
        calculateDP(v, u, child_depth);
    }
}

int main() {
    int T;
    cin >> T;

    while (T--) {
        int n;
        cin >> n;

        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            count[i] = 0;
        }

        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
        }

        // Calculate depth and subtree size
        dfs(1, 0);

        // Calculate dp values
        calculateDP(1, 0, 0);

        for (int i = 0; i < n; i++) {
            cout << count[i] << " ";
        }
        cout << endl;
    }

    return 0;
}



Count Possibilities 🔴🔴Not correct code just try🔴🔴