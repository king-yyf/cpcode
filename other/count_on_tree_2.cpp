#include<bits/stdc++.h>
using namespace std;
 
struct Mo {
  int width;
  vector<int> left, right, order;
 
  Mo(int N, int Q) : order(Q) {
    width = max<int>(1, 1.0 * N / max<double>(1.0, sqrt(Q * 2.0 / 3.0)));
    iota(begin(order), end(order), 0);
  }
 
  void insert(int l, int r) { /* [l, r) */
    left.emplace_back(l);
    right.emplace_back(r);
  }
 
  template <typename AL, typename AR, typename DL, typename DR, typename REM>
  void run(const AL &add_left, const AR &add_right, const DL &delete_left,
           const DR &delete_right, const REM &rem) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if (ablock != bblock) return ablock < bblock;
      if (ablock & 1) return right[a] < right[b];
      return right[a] > right[b];
    });
    int nl = 0, nr = 0;
    for (auto idx : order) {
      while (nl > left[idx]) add_left(--nl);
      while (nr < right[idx]) add_right(nr++);
      while (nl < left[idx]) delete_left(nl++);
      while (nr > right[idx]) delete_right(--nr);
      rem(idx);
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
 
struct MoLCA{
    int n, K, cur_ord;
    vector<vector<int>> g, fa;
    vector<int> dep, ent, out, dfs_ord;
 
    MoLCA(int _n = 0) : n(_n), cur_ord(-1) {
    	K = 32 - __builtin_clz(n);
    	g.resize(n), fa.resize(n, vector<int>(K)), dep.resize(n);
    	ent.resize(n), out.resize(n), dfs_ord.resize(n * 2);
    }
 
    MoLCA(const vector<vector<int>> &G) : MoLCA((int)G.size()) {
        g = G;
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
 
    void build(int root = 0) { //æ ¹è��ç�¹ç¼�å�·
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
    
    int dist(int x, int y) {
        int l = lca(x, y);
        return dep[x] + dep[y] - 2 * dep[l];
    }
};
 
int main() {
	ios::sync_with_stdio(false); 
	cin.tie(nullptr);
	cout << fixed << setprecision(10);
 
	int n, q;
 
	cin >> n>> q;
 
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];	
	}
	Discretization<int> v(a);
	vector<int> cnt(v.size()+1);
 
	for (int i = 0; i < n; ++i) {
		a[i] = v(a[i]);
	}
 
	MoLCA g(n);
 
	for(int i=0,u,v;i<n-1;++i){
		cin>>u>>v;
		u--,v--;
		g.add_edge(u,v);
	}
 
	g.build();
	
	vector<pair<int,int> > qs; 
	vector<vector<int>> p(q);
 
	int idx=0;
 
	for (int i = 0, l, r; i < q; ++i) {
	    cin >> l >> r;
	    l--,r--;
	    int u=g.lca(l,r);
	    if(g.ent[l]>g.ent[r]){
	    	swap(l,r);
	    }
	    if(u==l) {
	    	 qs.push_back({g.ent[l], g.ent[r]+1});;
	    	 p[i].push_back(idx);
	    	 idx++;
	    }else{
	    	 p[i].push_back(idx);
	    	 qs.push_back({g.out[l], g.ent[r]+1});
	    	 idx++;
	    	 p[i].push_back(idx);
	    	 qs.push_back({g.ent[u],g.ent[u]+1});
	    	 idx++;
	    }
	    
	} 
 
	Mo mo(n, idx);   
	for(auto&pt:qs){
		mo.insert(pt.first,pt.second);
	}
 
	vector<int> ans(idx+1);
	int cur = 0;
	auto add_l = [&](int x) {
		x=g.dfs_ord[x];
		if (cnt[a[x]] == 0) cur++;
		cnt[a[x]]++;
	};
	auto add_r = [&](int x) {
		x=g.dfs_ord[x];
		if (cnt[a[x]] == 0) cur++;
		cnt[a[x]]++;
	};
	auto del_l = [&](int x) {
		x=g.dfs_ord[x];
		cnt[a[x]]--;
		if (cnt[a[x]] == 0) cur--;
	};
	auto del_r = [&](int x) {
		x=g.dfs_ord[x];
		cnt[a[x]]--;
		if (cnt[a[x]] == 0) cur--;
	};
 
	auto rem = [&](int x) { ans[x] = cur; };
	mo.run(add_l,add_r,del_l,del_r,rem);
 
	for (int i = 0; i < q; ++i) {
		int x=0;
		for(auto&j:p[i])
			x+=ans[j];
		cout<<x<<"\n";
	}
} 