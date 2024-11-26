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

int dp[6][505][5];
vector<int> g[6];
class Solution {
public:

    int defendSpaceCity(vector<int>& a, vector<int>& b) {
    	int n=sz(a);
    	f0(6) g[i].clear();
    	mst(dp,0x3f);

    	f0(n){
    		g[a[i]].push_back(b[i]);
    	}
    	sort(g[1].begin(),g[1].end());
    	dp[1][0][0]=0;
    	for(int i=0;i<g[1].size();++j){
    		dp[1][i+1][1]=min(dp[1][i][1],dp[1][i][0])+2;
    		dp[1][i+1][2]=min(dp[1][i][1],dp[1][i][0],dp[1][i][3])+3;
    		dp[1][i+1][3]= dp[1][i][2];
    	}

    	for(int i=2;i=5;++i){
    		set<int> s(g[i].begin(),g[i].end())
    		for(int j=0;j<=500;++j){
    			if(s.count(j)){
    				dp[i][j+1][1]=min(dp[i][j][1],dp[i][j][0])+2;
		    		dp[i][j+1][2]=min(dp[i][j][1],dp[i][j][0],dp[i][j][3])+3;
		    		dp[i][j+1][3]= dp[i][j][2];
		    		dp[i][j+1][4]= min(dp[i-1][j+1][1],dp[i-1][j+1][2],dp[i-1][j+1][3]);
    			}else{
    				dp[i][j+1][4]
    			}
    		}
    	}
    }
};