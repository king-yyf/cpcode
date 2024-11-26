#include<bits/stdc++.h>
using namespace std;
 
struct MoTree {
	int n, K, cur_ord;
    vector<vector<int>> g, fa;
    vector<int> dep, ent, out, dfs_ord;
    vector<array<int, 4>> qs;
 
    MoTree(int N, int Q) :n(N), cur_ord(-1){
	    K = 32 - __builtin_clz(n);
    	g.resize(n), fa.resize(n, vector<int>(K)), dep.resize(n);
    	ent.resize(n), out.resize(n);
    	dfs_ord.resize(n * 2);
	}
 
	void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }
 
    void dfs(int id, int pa) {
        fa[id][0] = pa;
        ent[id] = ++cur_ord;
        dfs_ord[cur_ord] = id;
        for(auto& to: g[id]) if (to != pa){
            dep[to] = dep[id] + 1;
            dfs(to, id);
        }
        out[id] = ++cur_ord;
        dfs_ord[cur_ord] = id;
    }
 
    void build(int root = 0) {  // index of root
        dfs(root, -1);
        for(int j = 0; j < K-1; ++j) for(int i = 0; i < n; ++i) {
             if (fa[i][j] < 0) fa[i][j + 1] = -1;
             else fa[i][j + 1] = fa[fa[i][j]][j];
        }
    }
 
    int lca(int u, int v) {
        if (dep[u] > dep[v]) swap(u, v);
        for (int k = 0; k < K; k++) {
            if ((dep[v] - dep[u]) >> k & 1) {
                v = fa[v][k];
            }
        }
        if (u == v) return u;
        for (int k = K - 1; k >= 0; k--)
            if (fa[u][k] != fa[v][k]) {
                u = fa[u][k];
                v = fa[v][k];
            }
        return fa[u][0];
    }
 
    void insert(int l, int r, int u, int id) {  // [l, r, lca, id]
	    qs.push_back({l, r, u, id});
	}
 
	template <typename REM, typename CHK>
	void run(const REM &rem, const CHK &chk) {
		
		int m = dfs_ord.size(), width = sqrt(m);
		vector<int> bl(m);
		for (int i = 0; i < bl.size(); i++) 
			bl[i] = i / width + 1;
		sort(begin(qs), end(qs), [&](auto &x, auto &y){
			if (bl[x[0]] != bl[y[0]]) return bl[x[0]] < bl[y[0]];
			return (bl[x[0]] & 1) ? x[1] < y[1] : x[1] > y[1];
		});
		int nl = qs[0][0], nr = nl - 1;

		for (auto &[l, r, p, id]: qs) {
			while (nl < l) chk(dfs_ord[nl++]);
			while (nl > l) chk(dfs_ord[--nl]);
			while (nr < r) chk(dfs_ord[++nr]);
			while (nr > r) chk(dfs_ord[nr--]);
			int u = dfs_ord[nl], v = dfs_ord[nr];
			if (p != u && p != v) chk(p);
		    rem(id);
		    if (p != u && p != v) chk(p);
		}
	}
};
 
template <class T>
struct Discretization {
	vector<T> xs;
	Discretization(const vector<T>& v) {
		xs = v;
		sort(xs.begin(), xs.end());
		xs.erase(unique(xs.begin(), xs.end()), xs.end());
	}
	int get(const T& x) const {
		return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
	}
	inline int operator()(const T& x) const { return get(x); }
	T operator[](int i) { return xs[i]; }
	int size() const { return xs.size(); }
};
 
int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
 
	int n, q;
	cin >> n>> q;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];	
	}
	Discretization<int> v(a);
 
	for (int i = 0; i < n; ++i) {
		a[i] = v(a[i]);
	}
 
	MoTree mo(n, q);
 
	for(int i=0,u,v;i<n-1;++i){
		cin >> u >> v;
		u--, v--;
		mo.add_edge(u,v);
	}
	mo.build();
	for (int i = 0, l, r; i < q; ++i) {
	    cin >> l >> r;
	    l--, r--;
	    int u = mo.lca(l, r);
	    if (mo.ent[l] > mo.ent[r]) {
	    	swap(l, r);
	    }
	    if (u == l) {
	    	mo.insert(mo.ent[l], mo.ent[r], u, i);
	    } else {
	    	mo.insert(mo.out[l], mo.ent[r], u, i);
	    }
	}
	vector<int> ans(q), cnt(v.size()), vis(n);
	int cur = 0;
	auto check = [&](int x) {
		if (vis[x]) {
			if (--cnt[a[x]] == 0) cur--;
		} else {
			if (cnt[a[x]]++ == 0) cur++;
		}
		vis[x] ^= 1;
	};
	auto rem = [&](int x) { ans[x] = cur; };
	mo.run(rem, check);
	for (int i = 0; i < q; ++i) {
		cout << ans[i] << "\n";
	}
} 