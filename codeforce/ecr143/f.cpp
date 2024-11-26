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

const int INF = int(1e9) + 5;
struct edge {
    int node;
    edge(int _node = -INF) : node(_node) {}
};
struct CD {
    int N;
    vector<vector<edge>> g;
    vector<int> dep,sub_sz,cen_pa,nodes;
    vector<vector<pair<int, int>>> cen_dis;
 
    CD(int N = 0):N(N),g(N),dep(N),sub_sz(N),cen_dis(N),cen_pa(N,-1) {}
 
    void add_edge(int u, int v) {
        assert(u != v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
 
    void erase_edge(int from, int to) {
        for (edge &e : g[from])
            if (e.node == to) {
                swap(e, g[from].back());
                g[from].pop_back();
                return;
            }
 
        assert(false);
    }
 
    int dfs(int node, int parent = -1, int subroot = -1) {
        if (parent < 0) {
            subroot = node;
            nodes.clear();
        }
 
        dep[node] = parent < 0 ? 0 : dep[parent] + 1;
        sub_sz[node] = 1;
        nodes.push_back(node);
 
        for (edge &e : g[node])
            if (e.node != parent)
                sub_sz[node] += dfs(e.node, node, parent < 0 ? e.node : subroot);
 
        return sub_sz[node];
    }
 
    int centroid(int root) {
        int n = dfs(root);
        bool found;
 
        // Repeatedly move to the subtree that is at least half of the tree, if such a subtree exists.
        do {
            found = false;
 
            for (edge &e : g[root])
                if (sub_sz[e.node] < sub_sz[root] && 2 * sub_sz[e.node] >= n) {
                    root = e.node;
                    found = true;
                    break;
                }
        } while (found);
 
        return root;
    }
 
    void solve(int root) {
        root = centroid(root);
 
        for (int node : nodes)
            if (node != root)
                cen_pa[node] = root;
 
        dfs(root);
 
        for (int node : nodes)
            cen_dis[root].emplace_back(node, dep[node]);
 
        sort(cen_dis[root].begin(), cen_dis[root].end());
 
        for (edge &e : g[root])
            erase_edge(e.node, root);
 
        // Recurse after solving root, so that edge erasures don't cause incorrect results.
        for (edge &e : g[root])
            solve(e.node);
    }
 
    int get_centroid_dist(int root, int node) const {
        auto it = lower_bound(cen_dis[root].begin(), cen_dis[root].end(), make_pair(node, -INF));
 
        if (it == cen_dis[root].end() || it->first != node)
            return -1;
 
        return it->second;
    }
};

void ac_yyf(int tt) {
	int n,k;
    rd(n);
    CD d(n);
    for(int i=1,u,v;i<n;++i){
    	rd(u,v);u--,v--;
    	d.add_edge(u,v);
    }
    vector<int> dis(n, INF);
    auto get=[&](int e){
    	for (int x = e; x >= 0; x = d.cen_pa[x])
            dis[x] = min(dis[x], d.get_centroid_dist(x, e));
    };
    auto find=[&](int e){
    	int ds = INF;
        for (int x = e; x >= 0; x = d.cen_pa[x])
            ds = min(ds, d.get_centroid_dist(x, e) + dis[x]);
        return ds;
    };

    rd(k);
    vector<int> c(k);
    f0(k) {
    	rd(c[i]);
    	c[i]--;
    	get(c[i]);
    }
    
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
