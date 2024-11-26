#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define yn(cond) cout << ((cond) ? "Yes" : "No") << "\n";
#define YN(cond) cout << ((cond) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
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
const double PI = acos(-1.0);
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

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
        T ans = 0;
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T sum(int l, int r) { //sum[l..r]
        return l <= r ? sum(r) - sum(l - 1) : 0; 
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

template <class S, S (*op)(S, S), S (*e)()>
struct SegTree {
    int n, size, log;
    vector<S> d;
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<S>(n, e())) {}
    explicit SegTree(const vector<S> &v) : n(int(v.size())) {
        log = ceil_lg(n), size = 1 << log;
        d = vector<S>(2 * size, e());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) pull(i);
    }
    int ceil_lg(int x) {   // minimum non-neg x s.t. `n <= 2^x`
        return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);
    }
    void set(int p, S x) {  // assert(0 <= p < n)
        p += size, d[p] = x;
        for (int i = 1; i <= log; ++i) pull(p >> i);
    }
    S get(int p) const { return d[p + size];}
    S get(int l, int r) {   // [l, r)
        S sl = e(), sr = e();
        l += size, r += size;
        while (l < r) {
            if (l & 1) sl = op(sl, d[l++]);
            if (r & 1) sr = op(d[--r], sr);
            l >>= 1, r >>= 1;
        }
        return op(sl, sr);
    }
    S get_all() const {return d[1];}

    void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]);}
    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F>     // 0 <= l <= n, f(e()) is true
    int max_right(int l, F f) const { 
        if (l == n) return n;
        l += size;
        S x = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(x, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(x, d[l]))) {
                        x = op(x, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            x = op(x, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }
    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F>  // 0 <= r <= n, f(e()) is true
    int min_left(int r, F f) const {
        if (r == 0) return 0;
        r += size;
        S x = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], x))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], x))) {
                        x = op(d[r], x);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            x = op(d[r], x);
        } while ((r & -r) != r);
        return 0;
    }
};
using S = long long ;
S op(S x, S y) {
    S s=x+y;
    return s;
}
S e() {
    return S();
}



void ac_yyf(int tt) {
    int n,q;
    cin>>n>>q;
    HLD g(n);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin>>a[i];	
    }
    for(int i=1,u,v;i<n;++i){
    	cin>>u>>v;u--;v--;
    	g.add_edge(u,v);
    }
    g.build();
    vector<long long> v(n);
    for (int i = 0; i < n; ++i) {
        v[g.in[i]]=a[i];	
    }
    SegTree<S, op, e> seg(v);
    while(q--){
    	int op;
    	cin>>op;
    	if(op==1){
    		cin>>x>>y;
    		x--;
    		seg.set(g.in[x],y);
    	}else {
    		cin>>x;
    		x--;
    		g.tree(x, [&](int u, int v){
    			cout<<seg.get(u,v)<<'\n';
    		});
    	}
    }
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
