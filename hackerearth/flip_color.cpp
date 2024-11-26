#include <bits/stdc++.h>
using namespace std;

/*

https://www.hackerearth.com/challenges/competitive/dsa-coding-contest-february-23/algorithm/flip-color-16c8a423/

*/

void wt(vector<int> &a){
	for(int x:a)cout<<x<<" ";cout<<"\n";
}

struct HLD {
    int n, cur = 0;
    vector<int> siz, top, dep, fa, in, out, seq;
    vector<vector<int>> g;
    HLD(int n) : n(n), siz(n), top(n), dep(n), fa(n, -1), in(n), out(n), seq(n), g(n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(int root = 0) {
        top[root] = root;
        dfs1(root);
        dfs2(root);
    }
    void dfs1(int u) {
        if (fa[u] != -1)
            g[u].erase(find(g[u].begin(), g[u].end(), fa[u]));

        siz[u] = 1;
        for (auto &v : g[u]) {
            fa[v] = u, dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[g[u][0]]) {
                swap(v, g[u][0]);  // g[u][0] 存储u节点的重儿子
            }
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : g[u]) {
            top[v] = v == g[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = fa[top[u]];
            } else {
                v = fa[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    template<typename F> 
    void path(int u, int v, F &&f) { // 处理从u到v的路径
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            f(in[top[u]], in[u] + 1);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) swap(u, v);
        f(in[v], in[u] + 1);
    }
    template<typename F> 
    void tree(int u, F &&f) { // 处理以u为根的子树
        f(in[u], out[u]);
    }
};

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    HLD h(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	h.add_edge(u,v);
    }
    h.build(0);

    vector<int> d(n + 1);

    for (int i = 0, u; i < q; ++i) {
    	cin >> u;
    	u--;
    	h.path(u, 0, [&](int x, int y){
    		d[x]++, d[y]--;
    	});
    }
    for (int i = 1;i <= n; ++i) {
    	d[i] += d[i - 1];
    }

    int ans = 0;

    for (int i = 0; i < n; ++i) {
        ans += a[h.seq[i]] ^ (d[i] & 1);
    }
    cout << ans << "\n";

    return 0;
}
