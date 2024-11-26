// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("avx2")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct EulerTour {
	int n, m;
    vector<int> in, out, dep, seg;
    template <typename G>
    EulerTour(const G g, int n, int root = 0) : n(n), m(ceil_pow(2 * n)), in(n), out(n), dep(n + 1) {
        seg.assign(2 * m, n);
        dfs(g, root);
        for (int k = m - 1; k > 0; --k) seg[k] = argmin(seg[(k << 1) | 0], seg[(k << 1) | 1]);
    }
    template <typename E, typename EdgeToNode>
    EulerTour(const vector<vector<E>> &g, const EdgeToNode e2n, int root = 0) :
        EulerTour([&](int u, auto f) { for (const E &e : g[u]) f(e2n(e)); }, g.size(), root) {}
    EulerTour(const vector<vector<int>> &g, int root = 0) :
        EulerTour([&](int u, auto f) { for (int v : g[u]) f(v); }, g.size(), root) {}
    int lca(int u, int v) const {
        if (in[u] > in[v]) return lca(v, u);
        int res = n;
        for (int l = m + in[u], r = m + in[v] + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = argmin(res, seg[l++]);
            if (r & 1) res = argmin(res, seg[--r]);
        }
        return res;
    }
    inline int dis(int u, int v) const { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
    inline int parent(int u) const {
        int p = seg[m + out[u]];
        return p == n ? -1 : p;
    }
    template <typename F>
    void node_query(int u, int v, F &&f) {
    	int l = lca(u, v);
    	f(in[l], in[u]);
    	f(in[l] + 1, in[v]);
    }
    template <typename F>
    void edge_query(int u, int v, F &&f) {
    	int l = lca(u, v);
    	f(in[l] + 1, in[u]);
    	f(in[l] + 1, in[v]);
    }
    template <typename G>
    void dfs(G g, int root) {
        dep[root] = 0, dep[n] = numeric_limits<int>::max();
        int k = 0;
        auto f = [&](auto self, int u, int p) -> void {
            in[u] = k, seg[m + k++] = u;
            g(u, [&](int v){ if (v != p) dep[v] = dep[u] + 1, self(self, v, u); });
            out[u] = k, seg[m + k++] = p;
        };
        f(f, root, n);
    }
    inline int argmin(int u, int v) const { return dep[u] < dep[v] ? u : v; }
    static int ceil_pow(const int n) {
        return 1 << (n <= 1 ? 0 : 32 - __builtin_clz(n - 1));
    }
};

template <typename T>
struct FenwickTree {
    int n;
    vector<T> a;
    static int lg(unsigned x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
    FenwickTree(int n) : n(n), a(n) {}
    FenwickTree(vector<T> &A) : FenwickTree((int)A.size()) {
        for (int i = 0; i < n; ++i) add(i, A[i]);
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    T sum(int x) {
        T ans{};
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T sum(int l, int r) { //sum[l..r]
        return l <= r ? sum(r) - sum(l - 1) : T{}; 
    }
    T get(int x) const {   // 0 <= x < n, get a[x] in O(1), Equivalent to sum(x, x).
        T s = a[x];
        int y = x + 1;
        y -= y & -y;
        while (x != y) s -= a[x - 1], x -= x & -x;
        return s;
    }
    void set(int x, T v) {  // 0 <= x < n, set a[x] = v
        add(x, v - get(x));
    }
    int kth(T k) const {
        if (k < T()) return -1;
        int x = 0;
        for (int i = 1 << lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i, k -= a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i) {
    	int u, v;
    	cin >> u >> v;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }

    EulerTour et(g);
    FenwickTree<long long> f(2 * n);
    for (int i = 0; i < n; ++i) {
    	f.set(et.in[i], a[i]);
    	f.set(et.out[i],-a[i]);
    }

    for (int i = 0, t; i < q; ++i) {
    	cin >> t;
    	if (t == 0) {
    		int p, x;
    		cin >> p >> x;
    		f.add(et.in[p], x);
    		f.add(et.out[p], -x);
    	} else {
    		int u, v;
    		cin >> u >> v;
    		long long s = 0;
    		et.node_query(u, v, [&](int x, int y){
    			s += f.sum(x, y);
    		});
    		cout << s << '\n';
    	}
    }

    return 0;
}
