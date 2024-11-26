#include <bits/stdc++.h>
using namespace std;
 
int N, M, K;

struct MoTree {
	int n, K, cur_ord, width;
    vector<vector<int>> g, fa;
    vector<int> dep, ent, out, dfs_ord;
    vector<int> left, right, order, lcas;

    MoTree(int N, int Q) : order(Q), n(N), cur_ord(-1){
    	width = max<int>(1, 1.0 * N / max<double>(1.0, sqrt(Q * 2.0 / 3.0)));
	    iota(begin(order), end(order), 0);
	    K = 32 - __builtin_clz(n);
    	g.resize(n), fa.resize(n, vector<int>(K)), dep.resize(n);
    	ent.resize(n), out.resize(n), dfs_ord.resize(n * 2);
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

    void build(int root = 0) {  //根节点编号
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

    void insert(int l, int r, int u) { /* [l, r)  lca */
	    left.emplace_back(l);
	    right.emplace_back(r);
	    lcas.emplace_back(u);
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
			while (nl > left[idx]) add_left(dfs_ord[--nl]);
			while (nr < right[idx]) add_right(dfs_ord[nr++]);
			while (nl < left[idx]) delete_left(dfs_ord[nl++]);
			while (nr > right[idx]) delete_right(dfs_ord[--nr]);
			int u = dfs_ord[nl], v = dfs_ord[nr], p = lcas[idx];
			if (p != u && p != v) {
				add_left(p);
			}
		    rem(idx);
		    if (p != u && p != v) {
				delete_left(p);
			}
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

/*

int VAL[MAXN], ANS[MAXM];
bool VIS[MAXN];
int BL[MAXN << 1];

*/

int main(){
 
	int u, v, x;
	scanf("%d %d", &N, &M);
	MoTree mo(N,M);
	

	vector<int> a(N);
	for (int i = 0; i < N; ++i) {
		scanf("%d", &a[i]);
	}
	Discretization<int> vv(a);
	for (int i = 0; i < N; ++i) {
		a[i]=vv(a[i]);	
	}

	// Inputting Tree
	for (int i = 1; i < N; i++){
		scanf("%d %d", &u, &v);
		u--,v--;
		mo.add_edge(u,v);
	}

	mo.build();

	int cur = N*2, size = sqrt(cur);
	
	vector<int> BL(cur);
	vector<int> ANS(M),VAL(N),VIS(N);
	
	for (int i = 0; i < cur; i++) {
		BL[i] = i / size + 1;
	}

	vector<array<int,4>> q; 
	int res = 0;

	auto check = [&](int x){
		// If (x) occurs twice, then don't consider it's value 
		if ( (VIS[x]) and (--VAL[a[x]] == 0) ) res--; 
		else if ( (!VIS[x]) and (VAL[a[x]]++ == 0) ) res++;
		VIS[x] ^= 1;
	};

	auto compute = [&]() {
		int curL = q[0][0], curR = curL - 1;
	
		for (int i = 0; i < M; i++){
			
			while (curL < q[i][0]) {
				check(mo.dfs_ord[curL++]);
			}
			while (curL > q[i][0]) {
				check(mo.dfs_ord[--curL]);
			}
			while (curR < q[i][1]) {
				check(mo.dfs_ord[++curR]);
			}
			while (curR > q[i][1]) {
				check(mo.dfs_ord[curR--]);
			}
			
			int u = mo.dfs_ord[curL], v = mo.dfs_ord[curR];
			
			// Case 2
			if (q[i][2] != u and q[i][2] != v) check(q[i][2]);

			// cout<<"i = "<<i<<", "<<curL<<", "<<curR<<", "<<res<<"\n";
			
			ANS[q[i][3]] = res;
			
			if (q[i][2] != u and q[i][2] != v) check(q[i][2]);
		}
	 
		for (int i = 0; i < M; i++) printf("%d\n", ANS[i]);
	};
	
	for (int i = 0; i < M; i++){
		scanf("%d %d", &u, &v);
		u--,v--;
		int pa = mo.lca(u, v);
		if (mo.ent[u]>mo.ent[v]) swap(u, v);
		if (pa == u) q.push_back({mo.ent[u],mo.ent[v],pa,i});
		else q.push_back({mo.out[u],mo.ent[v],pa,i});
	}



	sort(q.begin(), q.end(),[&](auto &x, auto &y){
		return (BL[x[0]] == BL[y[0]]) ? (x[1] < y[1]) : (BL[x[0]] < BL[y[0]]);
	});

	compute();
}
 