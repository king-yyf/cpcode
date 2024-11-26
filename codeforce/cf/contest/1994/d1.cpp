#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Union-Find data structure with path compression and union by rank
class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void union_sets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

void solve() {
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        
        UnionFind uf(n);
        vector<pair<int, int>> edges;
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (abs(a[i] - a[j]) % (j - i) == 0) {
                    if (uf.find(i) != uf.find(j)) {
                        uf.union_sets(i, j);
                        edges.emplace_back(i + 1, j + 1);
                    }
                }
            }
        }
        
        // Check if all vertices are connected
        bool connected = true;
        int root = uf.find(0);
        for (int i = 1; i < n; ++i) {
            if (uf.find(i) != root) {
                connected = false;
                break;
            }
        }
        
        if (connected) {
            cout << "YES" << endl;
            for (auto& edge : edges)
                cout << edge.first << " " << edge.second << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();
    
    return 0;
}