#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const int N = 2e5 + 5;

class Solution {
public:
    int rampartDefensiveLine(vector<vector<int>>& a) {
    	ll l = 0,r=1e9,c=0;
    	int n=sz(a);
    	
    	while(l<=r){
    		ll md=(l+r)/2;
    		// dbg(l,r,md,'\n');
    		// dbg(l,r,t,'\n');
    		ll t=a[0][1];
    		bool o=1;
    		for(int i=1;i<n-1;++i){
    			
    			if(a[i][0]-t>=md){
    				t=a[i][1];
    			}else{
    				ll x=a[i][0]-t;
    				ll p=md-x;
    				if(p>0&&a[i][1]+p>a[i+1][0]){
    					o=0;break;
    				}
    				t=a[i][1];
    				// dbg(i,p,t,'\n');
    			}
    			// dbg("i=",i,a[i][0],a[i][1],md,t,'\n');
    		}
    		if(o){
    			c=md;
    			l=md+1;
    		}else {
    			r=md-1;
    		}
    		
    	}
    	return c;
    }
};


#ifdef sigma-yyf
int main(){
    Solution so;
    int n,k=3,m,x;

    vector<vector<int>> a{{0,3},{4,5},{7,9}};
    auto p=so.rampartDefensiveLine(a);
    wt(p,'\n');
    long long l,r;
    string s,t;
    
    // vector<string> sv;
    // vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    cout<<"\n";
    // 测试leetcode时，需要修改rd中的参数，
    // 比如 fun(vector<int>&a,int k),写为 rd(v);rd(k);
    // rd(root);
    // auto ans = so.;
    // wt(ans);wt("\n");
    return 0;
}
#endif
