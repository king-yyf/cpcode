#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
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
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    bool f=1;
    each(a, x) if(f==1) {wt(a); f=0;} else {cout<<' ';wt(a);}
}
const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

class Solution {
public:
    struct w{
        int x,y,t;
    };
    int maximumMinutes(vector<vector<int>>& g) {
        int n=sz(g),m=sz(g[0]);
        vector<vector<int>> a(n,vector<int>(m,2e9));
        vector<vector<int>> vis(n,vector<int>(m));
        queue<w> q;
        f0(n){
            f2(j,m){
                if(g[i][j]==1){
                    q.push({i,j,0});
                    a[i][j]=0;
                    vis[i][j]=1;
                }
            }
        }
        while(!q.empty()){
            auto p=q.front();q.pop();
            f0(4){
                int nx=p.x+dx[i],ny=p.y+dy[i];
                if(nx>=0&&nx<n&&ny>=0&&ny<m&&g[nx][ny]==0&&!vis[nx][ny]){
                    vis[nx][ny]=1;
                    q.push({nx,ny,p.t+1});
                    a[nx][ny]=p.t+1;
                }
            }
        }
        f0(n){
            f2(j,m){
                cout<<a[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
        q=queue<w>();
        vis=vector<vector<int>>(n,vector<int>(m));

        vector<vector<int>> c(n,vector<int>(m,2e9));
        q.push({0,0,0});
        vis[0][0]=1;
        c[0][0]=0;
        int ans=2e9;
        bool o=0;
        while(!q.empty()){
            auto p=q.front();q.pop();
            if(p.x==n-1&&p.y==m-1){
                o=1;
                break;
            }
            f0(4){
                int nx=p.x+dx[i],ny=p.y+dy[i];
                if(nx>=0&&nx<n&&ny>=0&&ny<m&&g[nx][ny]==0&&!vis[nx][ny]){
                    vis[nx][ny]=1;
                    q.push({nx,ny,p.t+1});
                    // ans=min(ans,a[nx][ny]-p.t-1);
                    c[nx][ny]=p.t+1;
                }
            }
        }
        // vector<w> ps;
        map<int,vector<w >> mp;
        // ps.push_back({n-1,m-1,c[n-1][m-1]});
        mp[c[n-1][m-1]].push_back({n-1,m-1,c[n-1][m-1]});
        q=queue<w>();
        q.push_back({n-1,m-1,c[n-1][m-1]});
        while(!q.empty()){
            auto p=q.front();q.pop();
            if(p.t==0){
                break;
            }
            f0(4){
                int nx=p.x+dx[i],ny=p.y+dy[i];
                if(nx>=0&&nx<n&&ny>=0&&ny<m&&g[nx][ny]==0){
                   if(c[nx][ny]==p.t-1){
                    q.push({nx,ny,p.t-1});
                    mp[p.t-1].push_back({nx,ny,p.t-1});
                   }
                }
            }
        }

        f0(n){
            f2(j,m){
                cout<<c[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
        ans=2e9;
        for(auto&[k,e]:mp){
            int tt=-1;
            for(auto&p:e){
                tt=max(tt,a[p.x][p.y]-c[p.x][p.y]);
            }
            if(tt>-1)
                ans=min(ans,tt);
        }
        if(ans<=0 ||o==0) return -1;
        if(ans>1e6) return 1e9;
        return ans;
    }
};