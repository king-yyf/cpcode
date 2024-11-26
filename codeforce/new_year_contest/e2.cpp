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

int n, m, q;
int x, y, k;
string s, t;

const int N=1005;

int w[N][N];
int d[N][N];


const int DN = 1005;
class DIJ {
public:

    

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
    cin>>n>>m;
    mst(w,0);
    for(int i=0;i<m;++i){
    	cin>>x>>y;
    	w[x][y]=1;
    }
    mst(d,0x3f);
    for(int i=1;i<=n;++i){
    	for(int j=1;j<=n;++j){
    		if(i==j)d[i][j]=0;
    		else if(w[i][j]){
    			d[i][j]=0;
    		}else if(w[j][i]){
    			d[i][j]=1;
    		}
    	}
    }
    // for(int k=1;k<=n;++k){
    // 	for(int i=1;i<=n;++i){
    // 		for(int j=1;j<=n;++j){
    // 			d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
    // 		}
    // 	}
    // }
    // for(int i=1;i<=n;++i){
    // 	for(int j=1;j<=n;++j){
    // 		cout<<d[i][j]<<" ";
    // 	}cout<<"\n";
    // }
    cin>>q;
    while(q--){
    	cin>>x>>y;
    	queue<pair<int,int>> q;
        vector<int> vis(n+1);
        vector<int> d(n+1,0x3f);
        q.push({x,0});
        while(!q.empty()){
            auto [k,v]=q.front();q.pop();
            if(vis[k]) continue;
            for(int i=1;i<=n;++i){
                
            }
        }
    }
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
