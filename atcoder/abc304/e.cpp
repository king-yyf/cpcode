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

struct Edcc {
    int n, m = 0, dcc_cnt = 0, init = 0;
    vector<vector<pair<int,int>>> g;
    vector<array<int, 2>> elist;
    vector<int> dfn, low, ids, deg;
    vector<bool> is_bridge;

    Edcc(int n = 0): n(n), dfn(n, -1), low(n), g(n), ids(n){}

    void add_edge(int a, int b) {
        g[a].emplace_back(b, m);
        g[b].emplace_back(a, m);
        elist.push_back({a, b});
        m++;
    }

    void get_ids() {
        init = 1;
        vector<bool> visited(n, false);
        is_bridge.assign(m, false);
        vector<int> stk;
        int now_dfn = 0;

        function<void(int, int)> dfs = [&](int u, int fa) {
            visited[u] = true;
            stk.push_back(u);
            low[u] = dfn[u] = now_dfn++;
            int pa_cnt = 0;
            for (auto &[v, id]: g[u]) {
                if (v == fa && pa_cnt++ == 0) continue;
                if (visited[v]) {
                    low[u] = min(low[u], dfn[v]);
                } else {
                    dfs(v, u);
                    is_bridge[id] = low[v] > dfn[u];
                    low[u] = min(low[u], low[v]);
                }
            }
            if (dfn[u] == low[u]) {
                while (true) {
                    int v = stk.back();
                    stk.pop_back();
                    ids[v] = dcc_cnt;
                    if (u == v) break;
                }
                dcc_cnt ++;
            }
        };
        
        for (int i = 0; i < n; i++)
            if (!~dfn[i])
                dfs(i, -1);
    }

    vector<vector<int>> edcc() {
        if (!init) get_ids();
        vector<vector<int>> groups(dcc_cnt);
        for (int i = 0; i < n; ++i) {
            groups[ids[i]].push_back(i);
        }
        deg.assign(dcc_cnt, 0);
        for (int i = 0; i < m; ++i) {
            if (is_bridge[i]) {
                deg[ids[elist[i][0]]]++;
                deg[ids[elist[i][1]]]++;
            }
        }
        return groups;
    }

    vector<vector<int>> bridge_tree() {
        if (!init) get_ids();
        vector<vector<int>> tr(dcc_cnt);
        for (int i = 0; i < m; ++i) {
            if (is_bridge[i]) {
                int x = ids[elist[i][0]], y = ids[elist[i][1]];
                tr[x].push_back(y);
                tr[y].push_back(x);
            }
        }
        return tr;
    }
};

struct Vdcc {
    int n, m = 0, init = 0;
    vector<vector<pair<int,int>>> g;
    vector<array<int, 2>> elist;
    vector<int> dfn, low, stack;
    vector<bool>  is_cut, is_bridge;
    vector<vector<int>> components;

    Vdcc(int n) : n(n), g(n), dfn(n), low(n){}

    void add_edge(int a, int b) {
        g[a].emplace_back(b, m);
        g[b].emplace_back(a, m);
        elist.push_back({a, b});
        m++;
    }

    void build(int root = -1) {
        init = 1;
        vector<bool> visited(n, false);
        is_cut.assign(n, false);
        is_bridge.assign(m, false);
        int now_dfn = 0;

        function<void(int, int)> dfs = [&](int u, int fa) {
            visited[u] = true;
            low[u] =  dfn[u] = now_dfn++;
            is_cut[u] = false;
            int pa_cnt = 0, child = 0;
            for (auto &[v, id] : g[u]) {
                if (v == fa && pa_cnt++ == 0) continue;
                if (visited[v]) {
                    low[u] = min(low[u], dfn[v]);
                    if (dfn[v] < dfn[u]) stack.push_back(u);
                } else {
                    int size = int(stack.size());
                    dfs(v, u);
                    child++;
                    low[u] = min(low[u], low[v]);
                    if (low[v] > dfn[u]) {
                        is_bridge[id] = true;
                        vector<int> comp = {u, v};
                        if (comp[0] > comp[1]) swap(comp[0], comp[1]);
                        components.push_back(comp);
                    } else if (low[v] == dfn[u]) {
                        stack.push_back(u);
                        vector<int> comp(stack.begin() + size, stack.end());
                        sort(comp.begin(), comp.end());
                        comp.erase(unique(comp.begin(), comp.end()), comp.end());
                        components.push_back(comp);
                        stack.resize(size);
                    } else {
                        stack.push_back(u);
                    }
                    if (low[v] >= dfn[u]) is_cut[u] = true;
                }
            }
            if (fa < 0) is_cut[u] = child > 1;
        };

        if (0 <= root && root < n)
            dfs(root, -1);
        for (int i = 0; i < n; i++)
            if (!visited[i])
                dfs(i, -1);
    }
    
};

// Note: instead of a block-cut tree this is technically a block-vertex tree, which ends up being much easier to use.
struct block_cut_tree {
    Vdcc &bi_comps;

    int n, BC, T;
    vector<vector<int>> g;
    vector<int> fa, dep;

    block_cut_tree(Vdcc &_bi_comps) : bi_comps(_bi_comps) {}

    void build() {
        n = bi_comps.n, BC = int(bi_comps.components.size());
        T = n + BC;
        g.assign(T, {});

        auto add_edge = [&](int a, int b) {
            assert((a < n) ^ (b < n));
            g[a].push_back(b);
            g[b].push_back(a);
        };

        function<void(int, int)> dfs = [&](int u, int pa) {
            fa[u] = pa, dep[u] = pa < 0 ? 0 : dep[pa] + 1;
            for (int v : g[u]) if (v != pa)
                dfs(v, u);
        };

        for (int bc = 0; bc < BC; bc++)
            for (int x : bi_comps.components[bc])
                add_edge(x, n + bc);

        fa.assign(T, -1);
        dep.resize(T);

        for (int root = 0; root < T; root++)
            if (fa[root] < 0)
                dfs(root, -1);
    }

    bool same_component(int a, int b) const {
        if (dep[a] > dep[b])
            swap(a, b);
        return a == b || (dep[b] == dep[a] + 2 && fa[fa[b]] == a) || (fa[a] >= 0 && fa[a] == fa[b]);
    }
};

void ac_yyf(int tt) {
    rd(n,m);
    Edcc g(n);
    set<pair<int,int> > s1;
    f0(m){
    	rd(x,y);
    	if(x==y)continue;
    	if(x>y)swap(x,y);
    	x--,y--;
    	if(s1.count({x,y}))continue;
    	g.add_edge(x,y);
    	s1.insert({x,y});
    }
    auto dcc = g.edcc();
    rd(k);
    set<int> sa,sb;
    f0(k){
    	rd(x,y);
    	x--,y--;
    	int u=g.ids[x],v=g.ids[y];
    	if(u>v)swap(u,v);
    	sa.insert(u);
    	sb.insert(v);
    }
    rd(q);
    f0(q){
    	rd(x,y);
    	x--,y--;
    	int u=g.ids[x],v=g.ids[y];
    	if(u>v)swap(u,v);
    	if(sa.count(u)&&sb.count(v)){
    		wt("No\n");
    	}else wt("Yes\n");
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
