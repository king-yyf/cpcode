#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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
#define yn(o) cout << ((o) ? "Yes" : "No") << "\n";
#define YN(o) cout << ((o) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
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

const int mod = 1e9+7; // 998244353;
const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

// N = 5e5时，空间约 170M，空间紧张时用 https://github.com/nealwu/competitive-programming/blob/master/rmq_lca/block_rmq_mask.cc
template<typename T, bool max_mode = false>
struct ST {
    static int lg(unsigned x) { return x == 0 ? -1 : 31 - __builtin_clz(x);}
    int n = 0;
    vector<T> a;
    vector<vector<int>> mat;
    ST(const vector<T> &A = {}) { if (!A.empty()) build(A);}
    int op(int x, int y) const {
        return (max_mode ? a[y] < a[x] : a[x] < a[y]) ? x : y; // when `a[x] == a[y]`, returns y.
    }
    void build(const vector<T> &A) {
        a = A, n = int(a.size());
        int max_log = lg(n) + 1;
        mat.resize(max_log);
        for (int k = 0; k < max_log; k++) mat[k].resize(n - (1 << k) + 1);
        for (int i = 0; i < n; i++) mat[0][i] = i;
        for (int k = 1; k < max_log; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                mat[k][i] = op(mat[k - 1][i], mat[k - 1][i + (1 << (k - 1))]);
    }
    int get_idx(int x, int y) const {  // 0 <= x < y <= n
        int k = lg(y - x);
        return op(mat[k][x], mat[k][y - (1 << k)]);
    }
    T get_val(int x, int y) const { return a[get_idx(x, y)];}
};
struct LCA {
    int n = 0, now_dfn = 0;
    vector<vector<int>> g;
    vector<int> fa, dep, siz, euler, dfn, ent, out, tour_ls, rev_tour_ls;
    vector<int> hv_rt, hv_rt_dep, hv_rt_fa; // 后两个 vector 仅用于优化 get_kth_anc
    ST<int> rmq;
    bool built = false;

    LCA(int n) : n(n), g(n), fa(n, -1), dep(n), siz(n), dfn(n), ent(n), out(n), tour_ls(n), hv_rt(n){}
    LCA(const vector<vector<int>> &G) : LCA(int(G.size())){g = G;}

    void add_edge(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int degree(int v) const { return int(g[v].size()) + (built && fa[v] >= 0);}
    void dfs(int u, int pa) {
        fa[u] = pa, siz[u] = 1, dep[u] = pa < 0 ? 0 : dep[pa] + 1;
        g[u].erase(remove(g[u].begin(), g[u].end(), pa), g[u].end());
        for (int v : g[u]) {
            dfs(v, u);
            siz[u] += siz[v];
        }
        sort(g[u].begin(), g[u].end(), [&](int a, int b) {
            return siz[a] > siz[b];
        });
    }
    void dfs1(int u, bool hv) {
          hv_rt[u] = hv ? hv_rt[fa[u]] : u;
          dfn[u] = int(euler.size());
          euler.push_back(u);
          tour_ls[now_dfn] = u, ent[u] = now_dfn++;
          bool hv_child = true;
          for (int v : g[u]) {
              dfs1(v, hv_child);
              euler.push_back(u);
              hv_child = false;
          }
          out[u] = now_dfn;
      };

    void build(int root = -1) {
        if (0 <= root && root < n) dfs(root, -1);
        for (int i = 0; i < n; i++) if (i != root && fa[i] < 0)
            dfs(i, -1);
        euler.reserve(2 * n);
        
        for (int i = 0; i < n; i++)
            if (fa[i] < 0) {
                dfs1(i, false);
                euler.push_back(-1);
            }
        assert(int(euler.size()) == 2 * n);
        vector<int> euler_dep;
        euler_dep.reserve(euler.size());
        for (int u : euler) euler_dep.push_back(u < 0 ? u : dep[u]);
        rmq.build(euler_dep);

        hv_rt_dep.resize(n); hv_rt_fa.resize(n);

        for (int i = 0; i < n; i++) {
            hv_rt_dep[i] = dep[hv_rt[i]];
            hv_rt_fa[i] = fa[hv_rt[i]];
        }
        rev_tour_ls = tour_ls;
        reverse(rev_tour_ls.begin(), rev_tour_ls.end());
        built = true;
    }

    // return <直径长度，{端点u, 端点v}>
    pair<int, array<int, 2>> get_diameter() const {
        pair<int, int> u_max = {-1, -1}, ux_max = {-1, -1};
        pair<int, array<int, 2>> uxv_max = {-1, {-1, -1}};

        for (int node : euler) {
            if (node < 0) break;
            u_max = max(u_max, {dep[node], node});
            ux_max = max(ux_max, {u_max.first - 2 * dep[node], u_max.second});
            uxv_max = max(uxv_max, {ux_max.first + dep[node], {ux_max.second, node}});
        }

        return uxv_max;
    }
    array<int, 2> get_center() const { // 树的直径的中点
        pair<int, array<int, 2>> diam = get_diameter();
        int length = diam.first, a = diam.second[0], b = diam.second[1];
        return {get_kth_node_on_path(a, b, length / 2), get_kth_node_on_path(a, b, (length + 1) / 2)};
    }
    int get_lca(int a, int b) const {   // return -1, if a,b不连通
        a = dfn[a], b = dfn[b];
        if (a > b) swap(a, b);
        return euler[rmq.get_idx(a, b + 1)];
    }

    bool is_anc(int a, int b) const { return ent[a] <= ent[b] && ent[b] < out[a];}
    bool on_path(int x, int a, int b) const {
        return (is_anc(x, a) || is_anc(x, b)) && is_anc(get_lca(a, b), x);
    }
    int get_dist(int a, int b) const {return dep[a] + dep[b] - 2 * dep[get_lca(a, b)];}

    // Returns the child of `a` that is an ancestor of `b`. Assumes `a` is a strict ancestor of `b`.
    int child_anc(int a, int b) const {
        assert(a != b && is_anc(a, b));
        int child = euler[rmq.get_idx(dfn[a], dfn[b] + 1) + 1];
        return child;
    }
    int get_kth_anc(int a, int k) const {
        if (k > dep[a]) return -1;
        int goal = dep[a] - k;
        while (hv_rt_dep[a] > goal)
            a = hv_rt_fa[a];
        return tour_ls[ent[a] + goal - dep[a]];
    }
    int get_kth_node_on_path(int a, int b, int k) const {
        int anc = get_lca(a, b), ls = dep[a] - dep[anc], rs = dep[b] - dep[anc];
        if (k < 0 || k > ls + rs) return -1;
        return k < ls ? get_kth_anc(a, k) : get_kth_anc(b, ls + rs - k);
    }
    // 到三个节点距离之和最小的节点(质心)，lca(a, b), lca(b, c)和 lca(c, a)中最深的节点
    int get_common_node(int a, int b, int c) const {
        int x = get_lca(a, b), y = get_lca(b, c), z = get_lca(c, a);
        return x ^ y ^ z;
    }

    // 给定树上k个节点子集，计算包含所有k个节点的最小子树(最多2*k-1节点) res[0].first 是子树的根
    vector<pair<int, int>> compress_tree(vector<int> nodes) const {
        if (nodes.empty()) return {};

        auto &&comp = [&](int a, int b) { return ent[a] < ent[b]; };
        sort(nodes.begin(), nodes.end(), comp);
        int k = int(nodes.size());
        for (int i = 0; i < k - 1; i++)
            nodes.push_back(get_lca(nodes[i], nodes[i + 1]));
        sort(nodes.begin() + k, nodes.end(), comp);
        inplace_merge(nodes.begin(), nodes.begin() + k, nodes.end(), comp);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        vector<pair<int, int>> res = { {nodes[0], -1} };
        for (int i = 1; i < int(nodes.size()); i++)
            res.emplace_back(nodes[i], get_lca(nodes[i], nodes[i - 1]));

        return res;
    }
};

template <class T>
struct Discrete {
    vector<T> xs;
    Discrete(const vector<T>& v) {
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



void ac_yyf(int tt) {
    rd(n,m);
    LCA g(n);
    for(int i=0;i<n-1;++i){
    	rd(x,y);x--,y--;
    	g.add_edge(x,y);
    }
    g.build();
    rd(k);
    vector<int> a(k);
    f0(k){
    	rd(a[i]);
    	a[i]--;
    }
    if(k<=m){
    	wt("0\n");return;
    }

    auto t=g.compress_tree(a);
    vector<int> b;
    for(auto&[k,v]:t)
    	b.push_back(k);
    Discrete<int> v(b);

    n=sz(g);


}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
