#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

// https://codeforces.com/gym/100962 F

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
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
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
template<class A> void dbg(A x) { cout<<x<<' ';}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;


template <class T>
struct MoTree {
    int n, K, cur_ord;
    vector<vector<pair<int, T>>> g;
    vector<vector<int>> fa;
    vector<int> a;
    vector<int> dep, ent, out, dfs_ord;
    vector<array<int, 4>> qs;
 
    MoTree(int N, int Q) :n(N), cur_ord(-1){
        K = 32 - __builtin_clz(n);
        g.resize(n), fa.resize(n, vector<int>(K)), dep.resize(n);
        a.resize(n), ent.resize(n), out.resize(n);
        dfs_ord.resize(n * 2);
    }
 
    void add_edge(int u, int v, T w) {
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
 
    void dfs(int id, int pa) {
        fa[id][0] = pa;
        ent[id] = ++cur_ord;
        dfs_ord[cur_ord] = id;
        for(auto& [to, w]: g[id]) if (to != pa){
            dep[to] = dep[id] + 1;
            a[to] = w;
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

void ac_yyf(int tt) {
    int n, q;
    cin >> n >> q;
    MoTree<int> mo(n, q);
    for (int i = 0, u, v, x; i < n - 1; i++) {
    	cin >> u >> v >> x;
    	u--, v--;
    	x = min(x, n + 1); // for n - 1 edges, mex <= n
    	mo.add_edge(u, v, x);
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

    vector<int> ans(q), vis(n);

    int blk = sqrt(n * 2);


    auto check = [&](int x) {
        int c = mo.a[x];
        if (c < n + 1) {
        	
        }
    };
    auto rem = [&](int x) { 
        auto mx = *s.find_by_order(0);
        auto mn = *s.find_by_order(s.size() - 1);
        auto mid = *s.find_by_order((s.size() - 1) / 2);
        ans[x] = mx.first +mn.first+mid.first;
    };

    mo.run(rem, check);

    for (int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
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
