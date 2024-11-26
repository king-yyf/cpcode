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
	int get(int x,int y) {
		return x*100+y;
	}
	int vis[110][110];
    class Solution {
public:
    int conveyorBelt(vector<string>& g, vector<int>& a, vector<int>& b) {
    	int t=0;
    	int n=sz(g),m=sz(g[0]);
    	mst(vis,0);
    	map<int,vector<int>> mp;
    	function<void(int,int)> dfs = [&](int x, int y) {
    		vis[x][y]=1;
    		mp[t].push_back(get(x,y));
    		int nx=x,ny=y;
    		if(g[x][y]=='^'){
    			nx--;
    		}else if(g[x][y]=='v') nx++;
    		else if(g[x][y]=='<') ny--;
    		else ny++;
    		if(nx>=0&&nx<n&&ny>=0&&ny<m){
    			dfs(nx,ny);
    		}
    	}

    	
    	f0(n){
    		f2(j,m){
    			if(!vis[i][j]) {
    				dfs(i,j);
    				t++;
    			}
    		}
    	}

    	auto chk = [&](vector<int> v1,vector<int> v2) -> bool {

    	}

    	for(int i=0;i<t;++i){
    		for(int j=i+1;j<t;++j){
    			if(chk(mp[i],mp[j]))
    		}
    	}
    }
};
};
