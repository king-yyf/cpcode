#ifdef LOCAL
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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

template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) {cout << x << " ";}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void wt(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void wt(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

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




template<typename T, bool maximum_mode = false>
struct RMQ {
    static int highest_bit(unsigned x) {
        return x == 0 ? -1 : 31 - __builtin_clz(x);
    }
 
    int n = 0;
    vector<T> values;
    vector<vector<int>> range_low;
 
    RMQ(const vector<T> &_values = {}) {
        if (!_values.empty())
            build(_values);
    }
 
    // Note: when `values[a] == values[b]`, returns b.
    int better_index(int a, int b) const {
        return (maximum_mode ? values[b] < values[a] : values[a] < values[b]) ? a : b;
    }
 
    void build(const vector<T> &_values) {
        values = _values;
        n = int(values.size());
        int levels = highest_bit(n) + 1;
        range_low.resize(levels);
 
        for (int k = 0; k < levels; k++)
            range_low[k].resize(n - (1 << k) + 1);
 
        for (int i = 0; i < n; i++)
            range_low[0][i] = i;
 
        for (int k = 1; k < levels; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                range_low[k][i] = better_index(range_low[k - 1][i], range_low[k - 1][i + (1 << (k - 1))]);
    }
 
    // Note: breaks ties by choosing the largest index.
    int query_index(int a, int b) const {
        assert(0 <= a && a < b && b <= n);
        int level = highest_bit(b - a);
        return better_index(range_low[level][a], range_low[level][b - (1 << level)]);
    }
 
    T query_value(int a, int b) const {
        return values[query_index(a, b)];
    }
};
 
struct LCA {
    int n = 0;
    vector<vector<int>> adj;
    vector<int> parent, depth, subtree_size;
    vector<int> euler, first_occurrence;
    vector<int> tour_start, tour_end, postorder;
    vector<int> tour_list, rev_tour_list;
    vector<int> heavy_root;
    RMQ<int> rmq;
    bool built;
 
    LCA(int _n = 0) {
        init(_n);
    }
 
    // Warning: this does not call build().
    LCA(const vector<vector<int>> &_adj) {
        init(_adj);
    }
 
    void init(int _n) {
        n = _n;
        adj.assign(n, {});
        parent.resize(n);
        depth.resize(n);
        subtree_size.resize(n);
        first_occurrence.resize(n);
        tour_start.resize(n);
        tour_end.resize(n);
        postorder.resize(n);
        tour_list.resize(n);
        heavy_root.resize(n);
        built = false;
    }
 
    // Warning: this does not call build().
    void init(const vector<vector<int>> &_adj) {
        init(int(_adj.size()));
        adj = _adj;
    }
 
    void add_edge(int a, int b) {
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
 
    int degree(int v) const {
        return int(adj[v].size()) + (built && parent[v] >= 0);
    }
 
    void dfs(int node, int par) {
        parent[node] = par;
        depth[node] = par < 0 ? 0 : depth[par] + 1;
        subtree_size[node] = 1;
 
        // Erase the edge to parent.
        adj[node].erase(remove(adj[node].begin(), adj[node].end(), par), adj[node].end());
 
        for (int child : adj[node]) {
            dfs(child, node);
            subtree_size[node] += subtree_size[child];
        }
 
        // Heavy-light subtree reordering.
        sort(adj[node].begin(), adj[node].end(), [&](int a, int b) {
            return subtree_size[a] > subtree_size[b];
        });
    }
 
    int tour, post_tour;
 
    void tour_dfs(int node, bool heavy) {
        heavy_root[node] = heavy ? heavy_root[parent[node]] : node;
        first_occurrence[node] = int(euler.size());
        euler.push_back(node);
        tour_list[tour] = node;
        tour_start[node] = tour++;
        bool heavy_child = true;
 
        for (int child : adj[node]) {
            tour_dfs(child, heavy_child);
            euler.push_back(node);
            heavy_child = false;
        }
 
        tour_end[node] = tour;
        postorder[node] = post_tour++;
    }
 
    void build(int root = -1, bool build_rmq = true) {
        parent.assign(n, -1);
 
        if (0 <= root && root < n)
            dfs(root, -1);
 
        for (int i = 0; i < n; i++)
            if (i != root && parent[i] < 0)
                dfs(i, -1);
 
        tour = post_tour = 0;
        euler.clear();
        euler.reserve(2 * n);
 
        for (int i = 0; i < n; i++)
            if (parent[i] < 0) {
                tour_dfs(i, false);
                // Add a -1 in between connected components to help us detect when nodes aren't connected.
                euler.push_back(-1);
            }
 
        rev_tour_list = tour_list;
        reverse(rev_tour_list.begin(), rev_tour_list.end());
        assert(int(euler.size()) == 2 * n);
        vector<int> euler_depths;
        euler_depths.reserve(euler.size());
 
        for (int node : euler)
            euler_depths.push_back(node < 0 ? node : depth[node]);
 
        if (build_rmq)
            rmq.build(euler_depths);
 
        built = true;
    }
 
    pair<int, array<int, 2>> get_diameter() const {
        assert(built);
 
        // We find the maximum of depth[u] - 2 * depth[x] + depth[v] where u, x, v occur in order in the Euler tour.
        pair<int, int> u_max = {-1, -1};
        pair<int, int> ux_max = {-1, -1};
        pair<int, array<int, 2>> uxv_max = {-1, {-1, -1}};
 
        for (int node : euler) {
            if (node < 0) break;
            u_max = max(u_max, {depth[node], node});
            ux_max = max(ux_max, {u_max.first - 2 * depth[node], u_max.second});
            uxv_max = max(uxv_max, {ux_max.first + depth[node], {ux_max.second, node}});
        }
 
        return uxv_max;
    }
 
    // Returns the center(s) of the tree (the midpoint(s) of the diameter).
    array<int, 2> get_center() const {
        pair<int, array<int, 2>> diam = get_diameter();
        int length = diam.first, a = diam.second[0], b = diam.second[1];
        return {get_kth_node_on_path(a, b, length / 2), get_kth_node_on_path(a, b, (length + 1) / 2)};
    }
 
    // Note: returns -1 if `a` and `b` aren't connected.
    int get_lca(int a, int b) const {
        a = first_occurrence[a];
        b = first_occurrence[b];
 
        if (a > b)
            swap(a, b);
 
        return euler[rmq.query_index(a, b + 1)];
    }
 
    bool is_ancestor(int a, int b) const {
        return tour_start[a] <= tour_start[b] && tour_start[b] < tour_end[a];
    }
 
    bool on_path(int x, int a, int b) const {
        return (is_ancestor(x, a) || is_ancestor(x, b)) && is_ancestor(get_lca(a, b), x);
    }
 
    int get_dist(int a, int b) const {
        return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
    }
 
    // Returns the child of `a` that is an ancestor of `b`. Assumes `a` is a strict ancestor of `b`.
    int child_ancestor(int a, int b) const {
        assert(a != b);
        assert(is_ancestor(a, b));
 
        // Note: this depends on RMQ breaking ties by latest index.
        int child = euler[rmq.query_index(first_occurrence[a], first_occurrence[b] + 1) + 1];
        assert(parent[child] == a);
        assert(is_ancestor(child, b));
        return child;
    }
 
    int get_kth_ancestor(int a, int k) const {
        while (a >= 0) {
            int root = heavy_root[a];
 
            if (depth[root] <= depth[a] - k)
                return tour_list[tour_start[a] - k];
 
            k -= depth[a] - depth[root] + 1;
            a = parent[root];
        }
 
        return a;
    }
 
    int get_kth_node_on_path(int a, int b, int k) const {
        int anc = get_lca(a, b);
        int first_half = depth[a] - depth[anc];
        int second_half = depth[b] - depth[anc];
        assert(0 <= k && k <= first_half + second_half);
 
        if (k < first_half)
            return get_kth_ancestor(a, k);
        else
            return get_kth_ancestor(b, first_half + second_half - k);
    }
 
    // Note: this is the LCA of any two nodes out of three when the third node is the root.
    // It is also the node with the minimum sum of distances to all three nodes (the centroid of the three nodes).
    int get_common_node(int a, int b, int c) const {
        // Return the deepest node among lca(a, b), lca(b, c), and lca(c, a).
        int x = get_lca(a, b);
        int y = get_lca(b, c);
        int z = get_lca(c, a);
        return x ^ y ^ z;
    }
 
    // Given a subset of k tree nodes, computes the minimal subtree that contains all the nodes (at most 2k - 1 nodes).
    // Returns a list of {node, parent} for every node in the subtree. Runs in O(k log k).
    vector<pair<int, int>> compress_tree(vector<int> nodes) const {
        if (nodes.empty())
            return {};
 
        auto &&compare_tour = [&](int a, int b) { return tour_start[a] < tour_start[b]; };
        sort(nodes.begin(), nodes.end(), compare_tour);
        int k = int(nodes.size());
 
        for (int i = 0; i < k - 1; i++)
            nodes.push_back(get_lca(nodes[i], nodes[i + 1]));
 
        sort(nodes.begin() + k, nodes.end(), compare_tour);
        inplace_merge(nodes.begin(), nodes.begin() + k, nodes.end(), compare_tour);
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
        vector<pair<int, int>> result = ;
 
        for (int i = 1; i < int(nodes.size()); i++)
            result.emplace_back(nodes[i], get_lca(nodes[i], nodes[i - 1]));
 
        return result;
    }
};



class Solution {
public:
    int minimumScore(vector<int>& a, vector<vector<int>>& es) {
        int n=sz(a);
        LCA g(n)
        vector<int> sum(n),dis(n);
        each(e,es){
            g.add_edge(e[0],e[1]);
        }
        g.build();
        function<void(int,int)> dfs=[&](int u, int fa){

            sum[u]=a[u];
            if(fa==-1)dis[u]=0;
            else dis[u]=dis[fa]+1;
            for (auto v : g.adj[u]) {
                if (v != fa) {
                    dfs(v, u);
                    sum[u]=sum[u]^sum[v];
                }
            }
        };
        dfs(0,-1);
        int x,y=0,z,yy;
        each(cc,a)y=y^cc;

        int m=sz(es);
        int mn=1e9;
        for(int i=0;i<m;++i){
            for(int j=i+1;j<m;++j){
                int x1=es[i][0],y1=es[i][1];
                int x2=es[j][0],y2=es[j][1];
                if(dis[x1]>dis[y1]){
                    x=sum[x1];
                    x3=x1;
                }else{
                    x=sum[y1];
                    x3=y1;
                }

                if(dis[x2]>dis[y2]){
                    z=sum[x2];
                    x4=x2;
                }else{
                    z=sum[y2];
                    x4=y2;
                }

                if(dis[x3]>dis[x4]){
                    if(g.is_ancestor(x4, x3)){
                        yy=y^z;
                        z=z^x;
                        
                    }else{
                        yy=y^x^z;
                    }
                }else{
                    if(g.is_ancestor(x3, x4)){
                        yy=y^x;
                        x=z^x;
                        
                    }else{
                        yy=y^x^z;
                    }
                }
                mn=min(mn,max({x,yy,z})-min({x,yy,z}));                

            }
        }
        return mn;

    }
};

#ifdef LOCAL
int main(){
    Solution so;
    int n,k=3,m,x;
    long long l,r;
    string s,t;
    vector<int> v,a,b; 
    vector<string> sv;
    vector<vector<int>> vv;
    ListNode* head = nullptr, *l1,*l2;
    TreeNode* root = nullptr,*p,*q;
    cout<<"\n";
    while(1){
        try{
            // 测试leetcode时，需要修改rd中的参数，
            // 比如 fun(vector<int>&a,int k),写为 rd(v);rd(k);
            rd(root);
            // auto ans = so.;
            // wt(ans);wt("\n");
        } catch (std::exception& e){ break;}
    }
    return 0;
}
#endif


