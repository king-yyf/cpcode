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
        int m=g[u].size();
        for (int i=m-1;i>=0;--i) {
        	int v=g[u][i];
            fa[v] = u, dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
        }
        sort(all(g[u]),[&](auto &x, auto &y){
        	return siz[x]<siz[y]||(siz[x]==siz[y]&&x>y);
        });
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u;
        for (auto v : g[u]) {
            top[v] = v == g[u].back() ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) u = fa[top[u]];
            else v = fa[top[v]];
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    bool is_anc(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
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

struct W{
	int x;
	int siz;
	bool operator < (const W& o) const {
		return siz > o.siz ||(siz==o.siz&&x<o.x);
	}
};

void ac_yyf(int tt) {
    rd(n,m);
    vector<int> a(n);

    vector<vector<int>> g(n);

    rd(a);
    f0(n-1){
    	rd(x,y);x--,y--;
    	g[x].push_back(y);
    	g[y].push_back(x);
    }

    vector<set<W> > q(n);
    
    vector<long long> s(n);
    vector<int> siz(n);

    vector<int> fa(n);

    function<void(int, int)> dfs = [&](int u, int pa) {
    	s[u]+=a[u];
    	siz[u]=1;
    	for(int v:g[u])if(v!=pa){
    		fa[v]=u;
    		dfs(v,u);
    		s[u]+=s[v];
    		siz[u]+=siz[v];
    		q[u].insert(W{v,siz[v]});
    	}
    };
    dfs(0, -1);
    
    int op;
    while(m--){
    	rd(op,x);
    	x--;
    	if(op==1){
    		cout<<s[x]<<'\n';
    	}else{
    		if(sz(q[x])==0) continue;
    		auto w=*q[x].begin();
    		int p=w.x; // x=3,p=6
    		q[x].erase(q[x].begin());

    		int t=fa[x];
    		auto it=q[t].find(W{x,siz[x]});
    		if(it!=q[t].end()) q[t].erase(it);
    		siz[x]-=siz[p];
    		s[x]-=s[p];
    		fa[x]=p;
    		siz[p]+=siz[x];
    		s[p]+=s[x];
    		q[p].insert(W{x,siz[x]});
    		fa[p]=t;
    		q[t].insert(W{p,siz[p]});
    	}
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
