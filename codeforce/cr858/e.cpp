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

void ac_yyf(int tt) {
    rd(n,q);
    vector<int> a(n);
    rd(a);
    vector<int> p(n,-1);
    f1(n-1){
    	rd(x);x--;
    	p[i]=x;
    }	
    MoTree mo(n, q);
    int l,r;
    for (int i = 0; i < q; ++i) {
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
