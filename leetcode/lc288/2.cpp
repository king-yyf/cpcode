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
    string minimizeResult(string s) {
        string s1,s2;
        bool o=1;
        for(auto&x:s){
        	if(x=='+') {
        		o=0;continue;
        	}
        	else if(o) s1+=x;
        	else s2+=x;
        }
        int n=sz(s1),m=sz(s2);
        ll ans=1e18;
        for(int i=0;i<n;++i){
        	for(int j=1;j<=m;++j){
        		string t1=s1.substr(0,i),t2=s1.substr(i);
        		string t3=s2.substr(0,j),t4=s2.substr(j);
        		// ll a=-1,b=-1,c=-1,d=-1,v=1;
        		// if(t1.size()>0) a=stoll(t1);
        		// if(t2.size()>0) b=stoll(t2);
        		// if(t3.size()>0) c=stoll(t3);
        		// if(t4.size()>0) d=stoll(t4);
        		// if(a!=-1) v=a;
        		// if(d!=-1)
        		long long  v=ans;
        		if(i==0){
        			if(j==0){
        				v=stoll(t2)*stoll(t4);
        			}else if(j==m){
        				v=stoll(t2)+stoll(t3);
        			}else {
        				v=(stoll(t2)+stoll(t3))*stoll(t4);
        			}
        		}else if(i==n){
        			if(j==0){
        				v=stoll(t1)*stoll(t4);
        			}else if(j==m){
        				v=stoll(t1)*stoll(t3);
        			}else {
        				v=stoll(t1)*stoll(t3)*stoll(t4);
        			}
        		}else {
        			if(j==0){
        				v=stoll(t1)*stoll(t2)*stoll(t4);
        			}else if(j==m){
        				v=stoll(t1)*(stoll(t2)+stoll(t3));
        			}else {
        				v=stoll(t1)*(stoll(t2)+stoll(t3))*stoll(t4);
        			}
        		}
        		ans=min(ans,v);
        	}
        }
        return ans;
    }
};
