#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://www.eolymp.com/en/contests/26719/problems/306687

template<typename T>
struct DsalBfs {
    using E = pair<T, int>;
    int n;
    vector<vector<E>> g;    // cost, to
    DsalBfs(int N) : n(N), g(N) {}

    void add_edge(int u, int v, T cost) {
        g[u].emplace_back(cost, v);
    }

    void add_bidir_edge(int u, int v, T cost) {
        add_edge(u, v, cost);
        add_edge(v, u, cost);
    }

    vector<T> bfs(int s, int k) {  // unreachable : -1
        vector<T> d(n, T(-1)); 
        queue<int> q[k + 1];
        vector<bool> vis(n);
        d[s] = 0;
        int cnt = 1, p = 0;
        q[0].push(s);
        while (cnt > 0) {
            while (q[p % (k + 1)].empty()) p++;
            if (p > k) p -= (k + 1);
            int u = q[p].front();
            q[p].pop();
            cnt--;
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto &[c, v] : g[u]) {
            	if (d[v] == T(-1) || d[v] > d[u] + c) {
            		d[v] = d[u] + c;
            		q[d[v] % (k + 1)].push(v);
            		cnt++;
            	}
            }
        } 
        return d;
    }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cout << fixed << setprecision(8);
    
    int n, m;
    cin >> n >> m;

    DsalBfs<int> g(n);

    for (int i = 0; i < m; ++i) {
    	int u, v, w;
    	cin >> u >> v >> w;
    	u--,v--;
    	g.add_bidir_edge(u,v,12/w);
    }

    auto d=g.bfs(0, 12);

    for(int i=1;i<n;++i){
    	cout<<d[i]/12.0<<'\n';
    }
    return 0;
}

