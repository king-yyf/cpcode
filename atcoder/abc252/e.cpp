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

int bct(long long x){return __builtin_popcountll(x);}
int lg2(int x){return x==0?0:31-__builtin_clz(x);} //x>=0, floor(log2(x)) 
long long fbs(function<bool(long long)> f, long long& lb, long long rb) {  // first true binary search
    while(lb<rb) {
        long long mb=(lb+rb)/2;
        f(mb)?rb=mb:lb=mb+1; 
    } 
    return lb;
}
long long lbs(function<bool(long long)> f, long long& lb, long long rb) {  // last true binary search
    while(lb<rb) {
        long long mb=(lb+rb+1)/2;
        f(mb)?lb=mb:rb=mb-1; 
    } 
    return lb;
}

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) { cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    for (int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];
}
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

vector<int> shortestPathTree(int n, vector<vector<int>> &edges, int u) {
    vector<vector<int>> g(n);
    vector<int> ans(n);
    for (int i = 0; i < edges.size(); ++i) {
        g[edges[i][0]].push_back(i);
        g[edges[i][1]].push_back(i);
    }
    vector<long long> dis(n, 1e18);
    vector<bool> vis(n); 
    priority_queue<pair<long long, int> > pq;
    dis[u] = 0;
    pq.push({0, u});
    while (pq.size()) {
        int t = pq.top().second; pq.pop();
        if (vis[t]) continue;
        vis[t] = true;
        for (auto &v : g[t]) {
            int x = edges[v][0] + edges[v][1] - t, cost = edges[v][2];
            if (dis[t] + cost < dis[x]) {
                dis[x] = dis[t] + cost;
                ans[x] = v;
                pq.push({-dis[x], x});
            } else if (dis[t] + cost == dis[x] && edges[ans[x]][2] > edges[v][2]) {
                ans[x] = v;
            } 
        }
    }
    return ans;
}

int n,m,x,y,k,q;
void solve(){
    cin>>n>>m;
    vector<vector<int>> e;
    f0(m){
        cin>>x>>y>>k;
        e.push_back({x-1,y-1,k});
    }
    long long c;
    auto a=shortestPathTree(n,e,0);
    for(int i=1;i<n;++i) cout<<a[i]+1<<" ";
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
