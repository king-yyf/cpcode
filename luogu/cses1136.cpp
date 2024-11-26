#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct HLD {
    int n, cur = 0, _root;
    vector<int> siz, top, dep, fa, in, out, seq;
    vector<vector<int>> g;
    HLD(int n) : n(n), siz(n), top(n), dep(n), fa(n, -1), in(n), out(n), seq(n), g(n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    void build(int root = 0) {
    	_root = root;
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
    int lca(int u, int v) const {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) u = fa[top[u]];
            else v = fa[top[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) const {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    bool is_anc(int u, int v) const {
        return in[u] <= in[v] && in[v] < out[u];
    }
    int kth_anc(int u, int k) const {
        if (k > dep[u]) return -1;
        int d = dep[u] - k;
        while (dep[top[u]] > d) u = fa[top[u]];
        return seq[in[u] - dep[u] + d];
    }
    bool on_path(int x, int a, int b) const {
        return (is_anc(x, a) || is_anc(x, b)) && is_anc(lca(a, b), x);
    }
    int kth_node_on_path(int a, int b, int k) const {
        int anc = lca(a, b), ls = dep[a] - dep[anc], rs = dep[b] - dep[anc];
        if (k < 0 || k > ls + rs) return -1;
        return k < ls ? kth_anc(a, k) : kth_anc(b, ls + rs - k);
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
    // 树上点差分，从u(0<=u<n)到v路径上的点权都加w。res为点权数组
    template<typename T>
    void node_diff(vector<T> &res, int u, int v, T w) {
    	int p = lca(u, v);
    	res[u] += w; res[v] += w; res[p] -= w;
    	if (fa[p] != -1) res[fa[p]] -= w;
    }
    // 树上边差分，从u(0<=u<n)到v路径上的边权都加w, 边权会下移给节点，res为边权数组
    template<typename T>
    void edge_diff(vector<T> &res, int u, int v, T w) {
    	res[u] += w; res[v] += w; res[lca(u, v)] -= 2 * w;
    }
    // 差分数组还原每个位置的值, 构造完差分数组都需要执行。
    template<typename T>
    void build_diff(vector<T> &res) {
    	function<void(int, int)> dfs = [&](int u, int fa) {
    		for (int v : g[u]) if (v != fa) {
    			dfs(v, u);
    			res[u] += res[v];
    		}
    	};
    	dfs(_root, -1);
    }
 };


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    HLD g(n);

    for (int i = 0; i < n - 1; i++) {
    	int u, v;
    	cin >> u >> v;
        u--, v--;
    	g.add_edge(u, v);
    }
    g.build();

    vector<int> a(n);
    for (int i = 0; i < m; ++i) {
    	int u, v;
    	cin >> u >> v;
    	u--, v--;
    	g.node_diff(a, u, v, 1);
    }
    g.build_diff(a);

    for (int i = 0; i < n; ++i) {
        cout << a[i] << " \n"[i == n - 1];    
    }

    return 0;
}
