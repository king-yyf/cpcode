#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define ln "\n";
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<A>& x) {wt(x);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;
struct w {
    int x;  int y;
    bool operator < (const w& o) const {
        return x!=o.x ? x<o.x : y<o.y;
    }
};

vector<int> a;

int sum[N];

struct LCA{
private:
    int n, root, K;
    vector<vector<int>> g, fa;
    vector<int> dep;
    
public:
    LCA(int n) {
        init(n);
    }
    LCA() {}
    void init(int n_) {
        n = n_, K = 32 - __builtin_clz(n);;
        g.resize(n), fa.resize(n, vector<int>(K)), dep.resize(n);
    }
    void add_edge(int a, int b) {
        g[a].push_back(b);
        g[b].push_back(a);
    }
    void dfs(int id, int fr, int d) {
        if(fr!=-1){
            sum[id]=sum[fr]^a[id];
        }else{
            sum[id]=a[id];
        }
        fa[id][0] = fr;
        dep[id] = d;
        for(auto& to: g[id]) {
            if (to == fr) continue;
            dfs(to, id, d + 1);
        }
    }
    void complete(int rt = 0) { //根节点编号
        root = rt;
        dfs(root, -1, 0);
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
    int depth(int x) {
        return dep[x];
    }
    int dist(int x, int y) {
        int l = lca(x, y);
        return dep[x] + dep[y] - 2 * dep[l];
    }
};

int n,m,x,y,k,q;
void solve(){
    rd(n,m);
    a.assign(n,0);
    rd(a);
    LCA g(n);

    f0(n-1){
        cin>>x>>y;
        x--,y--;
        g.add_edge(x,y);
    }
    g.complete();

    while(m--){
        cin>>x>>y;
        x--,y--;
        int t=sum[x]^sum[y]^a[g.lca(x,y)];
        cout<<t<<"\n";
    }
}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout<<fixed<<setprecision(20);
    int T=1;
    // cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve();
    }
    return 0;
}