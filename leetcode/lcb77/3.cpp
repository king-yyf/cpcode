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
    int countUnguarded(int m, int n, vector<vector<int>>& g, vector<vector<int>>& w) {
        vector<vector<int>> v(m,vector<int>(n));
        // a(m,vector<int>(n,n));
        // vector<vector<int>> b(m,vector<int>(n,-1));

        // vector<vector<int>> c(m,vector<int>(n,m));
        // vector<vector<int>> d(m,vector<int>(n,-1));
        each(e,w){
        	v[e[0]][e[1]]=1;
        }
        each(e,g){
        	v[e[0]][e[1]]=2;
        }
        f0(m){
        	vector<int> lg(n,-1),lw(n,-1),rg(n,n),rw(n,n);
        	for(int j=n-1;j>=0;--j){
        		if(v[i][j]==1){
        			rw[j]=j;
        		}else{
        			if(j<n-1)rw[j]=rw[j+1];
        		}
        		if(v[i][j]==2){
        			rg[j]=j;
        		}else{
        			if(j<n-1)rg[j]=rg[j+1];
        		}
        	}

        	for(int j=0;j<n;++j){
        		if(v[i][j]==1){
        			lw[j]=j;
        		}else{
        			if(j<n-1)lw[j]=lw[j-1];
        		}
        		if(v[i][j]==2){
        			lg[j]=j;
        		}else{
        			if(j<n-1)lg[j]=lg[j-1];
        		}
        	}
        	f2(j,n){
        		if(v[i][j]==0){
        			if(rg[i]<rw[i]||lg[i]>lw[i]) v[i][j]=3;
        		}
        	}
        }
        f0(n){
        	vector<int> lg(m,-1),lw(m,-1),rg(m,m),rw(m,m);
        	for(int j=m-1;j>=0;--j){
        		if(v[i][j]==1){
        			rw[j]=j;
        		}else{
        			if(j<m-1)rw[j]=rw[j+1];
        		}
        		if(v[i][j]==2){
        			rg[j]=j;
        		}else{
        			if(j<m-1)rg[j]=rg[j+1];
        		}
        	}

        	for(int j=0;j<m;++j){
        		if(v[i][j]==1){
        			lw[j]=j;
        		}else{
        			if(j<m-1)lw[j]=lw[j-1];
        		}
        		if(v[i][j]==2){
        			lg[j]=j;
        		}else{
        			if(j<m-1)lg[j]=lg[j-1];
        		}
        	}
        	f2(j,m){
        		if(v[i][j]==0){
        			if(rg[i]<rw[i]||lg[i]>lw[i]) v[i][j]=3;
        		}
        	}
        }
        // each(e,g){

        // }
    }
};