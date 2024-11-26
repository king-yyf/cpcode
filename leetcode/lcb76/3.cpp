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
    int maxTrailingZeros(vector<vector<int>>& g) {
        int n=g.size(),m=g[0].size(),ans=0;
        vector<vector<int>> s2(m,vector<int>(n+1));
        vector<vector<int>> s5(m,vector<int>(n+1));
        f0(m){
        	f2(j,n){
        		int x=0,y=0,t=g[j][i];
        		while(t%2==0){
        			x++;
        			t/=2;
        		}
        		t=g[j][i];
        		while(t%5==0){
        			y++;
        			t/=5;
        		}
        		s2[i][j+1]=s2[i][j]+x;
        		s5[i][j+1]=s5[i][j]+y;
        	}
        }
        f0(n){
        	vector<int> r2(m+1),r5(m+1);
        	f2(j,m){
        		int x=0,y=0,t=g[i][j];
        		while(t%2==0){
        			x++;
        			t/=2;
        		}
        		t=g[i][j];
        		while(t%5==0){
        			y++;
        			t/=5;
        		}
        		s[j+1]=r2[j]+x;
        		r5[j+1]=r5[j]+y;
        	}
        	f2(j,m){
        		int x1=s2[j][i+1],y1=s5[j][i+1];
        		int x2=s[m]-s[j+1],y2=r5[m]-r5[j+1];
        		ans=max(asns,min(x1+x2,y1+y2));
        		x2=s[j],y2=r5[j];
        		ans=max(ans,min(x1+x2,y1+y2));
        		x1=s2[j][n]-s2[j][i],y1=s5[j][n]-s5[j][i];
        		ans=max(ans,min(x1+x2,y1+y2));
        		x2=r2[m]-r2[j+1],y2=r5[m]-r5[j+1];
        		ans=max(ans,min(x1+x2,y1+y2));
        	}
        }
        return ans;
    }
};