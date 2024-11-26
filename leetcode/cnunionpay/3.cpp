#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
#define f1(e) for(int i=0;i<(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,b,e) for(int i=(b);i<(e);++i)
#define f4(i,b,e,s) for(int i=(b); (s)>0?i<(e):i>(e); i+=(s))
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 10;

class Solution {
public:
	using ll=long long ;
    int maxInvestment(vector<int>& p, int t) {
    	ll s=Sum(p);
    	if(s<=t){
    		ll s1=0;
    		each(x,p){
    			s1=s1+(1ll+x)*2/2;
    			s1=s1%mod;
    		}
    		return s1;
    	}
    	long long l=0,r=1e7,s1,mid,s2;
    	while(l<r){
    		mid=(l+r)/2;
    		s2=0;
    		each(x,p){
    			s2+=max(0,x-mid+1);
    		}
    		if(s2<=t){
    			r=mid;
    		}else l=mid+1;
    	}
    	s2=0;s1=0;
    	each(x,p){
    		if(x<l) continue;
    		s2=s2+(x-l+1ll)*(x+r)/2;
    		s1+=x-l+1;
    		s2=s2%mod;
    	}
    	if(l>0) {
    		s2=(s2+(l-1)*(t-s1))%mod;
    	}
    	return s2;
    }
};