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

// template <class E> struct csr {
//     std::vector<int> start;
//     std::vector<E> elist;
//     explicit csr(int n, const std::vector<std::pair<int, E>>& edges)
//             : start(n + 1), elist(edges.size()) {
//         for (auto e : edges) {
//             start[e.first + 1]++;
//         }
//         for (int i = 1; i <= n; i++) {
//             start[i] += start[i - 1];
//         }
//         auto counter = start;
//         for (auto e : edges) {
//             elist[counter[e.first]++] = e.second;
//         }
//     }
// };

// struct scc_graph {
// public:
//     explicit scc_graph(int n) : _n(n) {}

//     int num_vertices() { return _n; }

//     void add_edge(int from, int to) { edges.push_back({from, {to}}); }

//     // @return pair of (# of scc, scc id)
//     std::pair<int, std::vector<int>> scc_ids() {
//         auto g = csr<edge>(_n, edges);
//         int now_ord = 0, group_num = 0;
//         std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
//         visited.reserve(_n);
//         auto dfs = [&](auto self, int v) -> void {
//             low[v] = ord[v] = now_ord++;
//             visited.push_back(v);
//             for (int i = g.start[v]; i < g.start[v + 1]; i++) {
//                 auto to = g.elist[i].to;
//                 if (ord[to] == -1) {
//                     self(self, to);
//                     low[v] = std::min(low[v], low[to]);
//                 } else {
//                     low[v] = std::min(low[v], ord[to]);
//                 }
//             }
//             if (low[v] == ord[v]) {
//                 while (true) {
//                     int u = visited.back();
//                     visited.pop_back();
//                     ord[u] = _n;
//                     ids[u] = group_num;
//                     if (u == v) break;
//                 }
//                 group_num++;
//             }
//         };
//         for (int i = 0; i < _n; i++) {
//             if (ord[i] == -1) dfs(dfs, i);
//         }
//         for (auto& x : ids) {
//             x = group_num - 1 - x;
//         }
//         return {group_num, ids};
//     }

//     std::vector<std::vector<int>> scc() {
//         auto ids = scc_ids();
//         int group_num = ids.first;
//         std::vector<int> counts(group_num);
//         for (auto x : ids.second) counts[x]++;
//         std::vector<std::vector<int>> groups(ids.first);
//         for (int i = 0; i < group_num; i++) {
//             groups[i].reserve(counts[i]);
//         }
//         for (int i = 0; i < _n; i++) {
//             groups[ids.second[i]].push_back(i);
//         }
//         return groups;
//     }

// private:
//     int _n;
//     struct edge {
//         int to;
//     };
//     std::vector<std::pair<int, edge>> edges;
// };

void ac_yyf(int tt) {
     rd(n,m);
    vector<vector<int>> g(n);
    f0(m){
        rd(x,y);x--;y--;
        g[x].push_back(y);
    }
    int ans=0;
    for (int x=0;x<n;++x){
        queue<int>q;
        q.push(x);
        vector<int> vis(n);
        vis[x]=1;
        while(sz(q)){
            auto t=q.front();
            ans++;
            q.pop();
            for(auto&v:g[t]){
                if(!vis[v]) {
                    q.push(v);vis[v]=1;
                }
            }
        }
    }
    wt(ans-n-m,'\n');

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
