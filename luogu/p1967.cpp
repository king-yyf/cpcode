#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

struct DSU {
    vector<int> p, siz;
    DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) { return siz[get(x)]; }
    vector<vector<int>> groups() {
        vector<vector<int>> res(p.size());
        for (int i = 0; i < p.size(); i++) res[get(i)].push_back(i);
        res.erase(
            remove_if(res.begin(), res.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
};

template <typename T, typename Comp>
struct KruscalMST {
    KruscalMST() : KruscalMST(0) {}
    explicit KruscalMST(const int n) : _n(n) {}

    void add_edge(const int u, const int v, const T& cost) { _built = false; es.emplace_back(u, v, cost);}
    void add_edge(const tuple<int, int, T>& e) { _built = false; es.push_back(e);}
    bool build() {
        _built = true, _weight_sum = 0;
        if (_n == 0) return true;
        DSU uf(_n);
        sort(es.begin(), es.end(), [this](const auto& u, const auto& v) { return _comp(std::get<2>(u), std::get<2>(v));});
        for (auto& [u, v, w] : es) {
            if (uf.same(u, v)) u = v = _n;
            else { uf.merge(u, v); _weight_sum += w;}
        }
        es.erase(std::remove_if(es.begin(), es.end(), [this](auto& e) { return std::get<0>(e) == _n; }), es.end());
        return int(es.size()) == _n - 1;
    }
    T get_weight() const { assert(_built); return _weight_sum;}
    const vector<tuple<int, int, T>>& get_mst() const { assert(_built); return es;}
    vector<tuple<int, int, T>> es;
private:
    int _n;
    T _weight_sum;
    Comp _comp{};
    bool _built = false;
};
template <typename T> using minMst = KruscalMST<T, less<T>>;
template <typename T> using maxMst = KruscalMST<T, greater<T>>;

#include <bits/stdc++.h>
using namespace std;

struct HLD {
    int n, cur = 0;
    vector<int> siz, top, dep, fa, in, out, seq;
    vector<vector<int>> g;
    HLD(){}
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
        if(u != v) f(in[v] + 1, in[u] + 1);
    }
    template<typename F> 
    void tree(int u, F &&f) { // 处理以u为根的子树
        f(in[u], out[u]);
    }
};


template <class T, T (*op)(T, T)>
class ST {
 public:
  int n;
  vector<vector<T>> mat;

  ST(){}

  void build(const vector<T> &a) {
  	n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = op(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
 
  ST(const vector<T>& a) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = op(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
 
  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return op(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};
int op(int x,int y) {return min(x,y);}
// 


void ac_yyf(int tt) {
    rd(n,m);

    vector<vector<int>> adj(n);
    vector<array<int, 3>> es(m); 

    for (int i = 0, u, v, w; i < m; ++i) {
    	cin >> u >> v >> w;
    	u--, v--;
    	es[i] = {u, v, w};
    	adj[u].push_back(v);
    	adj[v].push_back(u);
    }

    vector<int> vis(n), id(n), p(n), siz(n);
    int cnt = 0, idx = 0;

    auto bfs = [&](int x){
    	vis[x] = 1;
    	id[x] = cnt;
    	p[x] = idx++;
    	queue<int> q;
    	q.push(x);
    	while(q.size()) {
    		auto u = q.front();
    		q.pop();
    		for (int v : adj[u]) if (!vis[v]) {
    			vis[v] = 1;
    			id[v] = cnt;
    			p[v] = idx++;
    			q.push(v);
    		}
    	}
    };
 
    for (int i = 0; i < n; ++i) {
    	if (!vis[i]) {
    		idx = 0;
    		bfs(i);
    		siz[cnt] = idx;
    		cnt++;
    	}
    }

    vector<maxMst<int>> t(cnt);
    vector<HLD> g(cnt);

    for (int i = 0; i < cnt; ++i) {
    	t[i] = maxMst<int>(siz[i]);
    	g[i] = HLD(siz[i]);
    }

    for (auto e: es) {
    	int u = e[0], v = e[1], w = e[2];
    	int k = id[u];
    	t[k].add_edge(p[u], p[v], w);
    }

    for (int i = 0; i < cnt; ++i) {
    	t[i].build();
    	for (auto &[u, v, w] : t[i].es) {
    		g[i].add_edge(u, v);
    	}
    	g[i].build();
    }

    vector<ST<int, op>> s(cnt);

    for (int i = 0; i < cnt; ++i) {
    	vector<int> a(siz[i]);
    	for (auto &[u, v, w] : t[i].es) {
    		if (g[i].dep[u] > g[i].dep[v]) {
    			swap(u, v);
    		}
    		a[g[i].in[v]] = w;
     	}
     	s[i].build(a);
    } 

    cin >> q;
    for (int i = 0, u, v; i < q; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	int k1 = id[u], k2 = id[v]; 
    	if (k1 != k2) {
    		cout << "-1\n";
    		continue;
    	}
    	u = p[u], v = p[v];
    	int ans = 1e9;
    	g[k1].path(u, v, [&](int x, int y){
    		ans = min(ans, s[k1].get(x, y - 1));
    	});
    	cout << ans << '\n';
    }
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
