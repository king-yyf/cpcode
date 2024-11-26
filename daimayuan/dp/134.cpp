#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define fr(i,a,b) for (int i=(a);i<(b);i++)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define yn(cond) if (cond) cout<<"Yes\n"; else cout << "No\n";
#define YN(cond) if (cond) cout<<"YES\n"; else cout << "NO\n";
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

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
const double PI = acos(-1.0);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;
const int DN = 1e3+10;
class DIJ {
public:

    struct Edge{
        int t, c; //to,cost
        Edge(int u, int v): t(u), c(v) {}
        bool operator < (const Edge& o) const {
            return c > o.c;
        }
    };

    using T = int;
    T dis[DN];
    bool vis[DN];
    vector<Edge> g[DN];

    DIJ(){}
    //添加边，dir 是否是有向图
    void add(int f, int t, int c, bool dir = 0) {
        g[f].emplace_back(t, c);
        if(dir == 0)
            g[t].emplace_back(f, c);
    }

    //从s到t的最短路,如果不存在路径输出-1.
    T dijk(int s, int t) {
        memset(dis,0x3f, sizeof(dis));
        memset(vis, 0, sizeof(vis));
        dis[s] = 0;
        priority_queue<Edge, vector<Edge>> pq;
        pq.push({s,0});
        while (!pq.empty()) {
            int v = pq.top().t;
            pq.pop();
            if(vis[v]) continue;
            vis[v] = 1;
            for (auto& e : g[v]) {
                if (dis[e.t] > dis[v] + e.c) {
                    dis[e.t] = dis[v] + e.c;
                    pq.push({e.t, dis[e.t]});
                }
            }
        }
        return dis[t] < 0x3f3f3f3f ? dis[t] : -1;
    }
};


void solve(int tt) {
    rd(n,m);
    DIJ d;
    f0(m){
    	int u,v,w;
    	rd(u,v,w);
    	d.add(u,v,w,1);
    }
    d.dijk(1,n);
    cout<<d.dis[n]<<"\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
