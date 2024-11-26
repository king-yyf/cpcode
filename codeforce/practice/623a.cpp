#include <bits/stdc++.h>
using namespace std;

vector<int> isBipartite(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> color(n);
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (!color[i]) {
            q.push(i);
            color[i] = 1;
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &v: g[u]) {
                if (!color[v]) {
                    q.push(v);
                    color[v] = 3 - color[u];
                } else if (color[v] == color[u]) return {};
            }
        }
    }
    return color;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> a(n, vector<int>(n, 1));

    for (int i = 0; i < n; ++i) {
        a[i][i] = 0;	
    }

    for (int i = 0; i < m; ++i) {
    	int u, v;
    	cin >> u >> v;
    	u--, v--;
    	a[u][v] = a[v][u] = 0;
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) 
    	for (int j = i + 1; j < n; ++j) 
    		if (a[i][j]) {
    			g[i].push_back(j);
    		}
    auto color = isBipartite(g);
    if (color.size() == 0) {
    	cout << "No\n";
    	return 0;
    }

    vector<int> deg(n);
    for (int i = 0; i < n; ++i) {
    	for (int j = 0; j < n; ++j) 
    		deg[i] += a[i][j];
    }

    string s(n, 'b');
    for (int i = 0; i < n; ++i) {
    	if (deg[i]) {
    		s[i] = (color[i] == 1 ? 'a' : 'c');
    	}
    }

    for (int i = 0; i < n; ++i) {
    	for (int j = i + 1; j < n; ++j) {
    		if ((abs(s[i] - s[j]) > 1) ^ a[i][j]) {
    			cout << "No\n";
    			return 0;
    		}
    	}
    }

    cout << "Yes\n";
    cout << s << '\n';

    return 0;
}
