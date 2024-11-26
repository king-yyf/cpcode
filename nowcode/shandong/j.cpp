#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ar(x) array<int,x> 
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
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
#ifdef sigma-yyf
#define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    cerr << s << ": " << h, ((cerr << ", " << t), ..., (cerr << "\n"));
}
#else
#define dbg(...) void(0)
#endif
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;
constexpr char nl = '\n';
constexpr int inf = 1'061'109'567;
constexpr ll infll = 2'000'000'000'000'000'000;
constexpr int N = 2e5 + 5;
int n, m, q;
int x, y, k;
string s, t;

long long cal1(vector<long long> &a) {
    long long  s1 = 0, s2 = 0;
    for (auto v : a) s1 += v, s2 += v * v;
    return (s1 * s1 - s2) / 2;
}
long long cal2(vector<long long>&a) {
    long long  s1 = 0, s2 = 0, s3 = 0;
    for (auto v : a) s3 += v;
    for (auto v : a) s1 += 1ll * v * v * v, s2 += 3ll * v * v * (s3 - v);

    return (s3 * s3 * s3 - s1 - s2) / 6;
}

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

void ac_yyf(int tt){
    cin>>n;
    vector<vector<int>> g(n);
    HLD h(n);
    f0(n-1){
        rd(x,y);
        x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
        h.add_edge(x,y);
    }
    h.build();
    vector<long long> s(n);
    vector<long long> c(n);
    function<void(int,int)> dfs=[&](int u,int fa){
        s[u]=1;
        vector<long long> a;
        for(auto&v:g[u]){
            if(v!=fa){
                dfs(v,u);
                a.push_back(s[v]);
                s[u]+=s[v];
            }
        }
        int m=a.size();
        for(auto&v:g[u]){
            if(v!=fa){
                c[u]+=c[v];
                c[u]+=s[v]-1;
                // dfs(v,u);
                // a.push_back(s[v]);
                // s[u]+=s[v];
            }
        }
        // c+=(s[u]-1)*1ll*(h.dep[u]);
        // if(m>=2) c+=cal1(a) * (n-s[u]);
        // if(m>=3) c+=cal2(a);
    };
    dfs(0,-1);
    ll p=n*1ll*(n-1)/2*(n-2)/3;
    f0(n)p-=c[i];
    wt(p,'\n');
}

int main() {
    int T = 1, fun_type = 0;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << (ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << (ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
