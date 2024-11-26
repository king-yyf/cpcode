#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;

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
};

template<typename F> 
void bitwise_and(vector<int> &a, F &&f) {
	vector<pair<int,int>> p, q;
	for (int n = a.size(), i = 0; i < n; ++i) {
	    q.emplace_back(a[i], i);
	    int k = 0;
	    for (int j = 0; j < p.size(); ++j) {
	        p[j].first &= a[i];
	        if (p[j].first == q[k].first) {
	            q[k].second = p[j].second;
	        } else {
	            q.emplace_back(p[j].first, p[j].second);
	            k++;
	        }
	    }
	    p = q;
	    q.clear();
	    for (int j = k; j >= 0; --j) {
	        // 以[l, r-1]为左端点，i为右端点的所有子数组，按位与的值都为p[j].first
	        int l = p[j].second, r = (j > 0 ? p[j - 1].second : i + 1);
	        f(i, l, r, p[j].first);
	    }
	} 
}

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
	    cin >> a[i];	
	}

	vector<int> s(n + 1), c(n + 1);
	for (int i = 0; i < n; ++i) {
	    s[i + 1] = s[i] ^ a[i];	
	}

	for (int i = 0; i <= n; ++i) {
		if (__builtin_popcount(s[i]) & 1) c[i] ++;
	}
	for (int i = 1; i <= n; ++i) {
		c[i] += c[i - 1];
	}
	
	long long ans = 0;

	bitwise_and(a, [&](int i, int l, int r, int val){
		if (__builtin_popcount(val) & 1) {
			int d = (__builtin_popcount(s[i + 1]) & 1);
			if (d == 1) {
				ans += c[r - 1] - (l > 0 ? c[l - 1] : 0);
			} else {
				ans += r - l - c[r - 1] + (l > 0 ? c[l - 1] : 0);
			}
		}
	});

	cout << ans << '\n';
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	solve();
    }
 
    return 0;
}
