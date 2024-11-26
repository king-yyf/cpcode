#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
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
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;
int n, m, k;

using ll=long long;

class Solution {
public:
    long long minIncrementOperations(vector<int>& nums, int k) {
    	n=sz(nums);
    	vector<ll> a(n+1);
    	f0(n)a[i+1]=nums[i];
    	vector dp(n+1,vector<long long>(9));
    	const ll inf=1e18;
    	if(a[1]<k || a[2]<k || a[3]<k) dp[3][1] = inf; 

        {
         
    } 
    
    if(a[3]<=k){
        dp[3][2] = abs(a[3]-k) ;
    } 
    
    
    if(a[2]<=k){
        dp[3][3] = abs(a[2]-k) ;
    } 
    
    if(a[1]<=k){
        dp[3][4] = abs(a[1]-k) ;
    }
    
    
    ll gg = 0 ; 
    if(a[1]<=k){
        gg = gg + abs(a[1]-k); 
    }
    if(a[2]<=k){
        gg = gg + abs(a[2]-k); 
    }
    dp[3][5] = gg ; 
    
    
     gg = 0 ; 
    if(a[1]<=k){
        gg = gg + abs(a[1]-k); 
    }
    if(a[3]<=k){
        gg = gg + abs(a[3]-k); 
    }
    dp[3][6] = gg ; 
    
    gg = 0 ; 
    if(a[2]<=k){
        gg = gg + abs(a[2]-k); 
    }
    if(a[3]<=k){
        gg = gg + abs(a[3]-k); 
    }
    dp[3][7] = gg ; 
    
    
    
    gg = 0 ; 
    if(a[1]<=k){
        gg = gg + abs(a[1]-k); 
    }
    if(a[2]<=k){
        gg = gg + abs(a[2]-k); 
    }
    if(a[3]<=k){
        gg = gg + abs(a[3]-k); 
    }
    dp[3][8] = gg ; 
    

    int i = 4 ; 
    while(i<=n){

    dp[i][1] = min(dp[i-1][1],dp[i-1][4]);
    if(a[i]<k){
        dp[i][1]=1e18 ; 
    }

    dp[i][2] = min(dp[i-1][1],dp[i-1][4]) ; 
    if(a[i]<k){
        dp[i][2]+=abs(a[i]-k);
    }

    dp[i][3] = min(dp[i-1][2],dp[i-1][6]) ;
    
    
    

    dp[i][4] = min(dp[i-1][3],dp[i-1][5]);

    dp[i][5] = min(dp[i-1][7],dp[i-1][8]);
    
    

    dp[i][6] = min(dp[i-1][3],dp[i-1][5]);
    if(a[i]<k){
        dp[i][6]+=abs(a[i]-k);
    }
    
    

    dp[i][7] = min(dp[i-1][2],dp[i-1][6]);
    if(a[i]<k){
        dp[i][7]+=abs(a[i]-k);
    }

    dp[i][8] = min(dp[i-1][7],dp[i-1][8]);
    if(a[i]<k){
        dp[i][8]+=abs(a[i]-k);
    }

    i++;
    }
    ll vv = 1e18 ; 
    i = 1 ; 
    for(int i=1;i<=n;++i)a[i]=0;
    while(i<=8){
        vv = min(vv,dp[n][i]);
        i++;
    }
        return vv;
    }
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a,b;
    string s,t;
    vector<string> sv;
    vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    // Solution so;
    // rd(a,k);
    // auto ans = so.;
    // wt(ans);
    cout<<'\n';
    return 0;
}
#endif
