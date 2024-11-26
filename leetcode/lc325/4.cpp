#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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
#define fi first
#define se second
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

const int mod = 1e9+7; 

int lengthOfLIS(vector<int>& nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
        auto it = lower_bound(res.begin(), res.end(), nums[i]);
        if (it == res.end()) res.push_back(nums[i]);
        else *it = nums[i];
    }
    return res.size();
}

class Solution {
public:
    int countPartitions(vector<int>& a, int k) {
        int n=a.size();
        long long s=0;
        for(auto&x:a)
            s+=x;
        if(s<2*k)return 0;
        vector<long long> dp(k+1);
        dp[0]=1;
        for(int i=0;i<n;++i){
            for(int j=k;j>=a[i];--j)
                dp[j]=(dp[j-a[i]]+dp[j])%mod;
        }
        long long c=0;
        for(int i=0;i<k;++i){
            c=(c+dp[i])%mod;
        }
        // wt(dp);
        long long p=1;
        for(int i=1;i<=n;++i) 
            p=(p*2)%mod;
        dbg(p,c,'\n');
        c=((p-c-c)%mod+mod)%mod;
        // c=(c+c)%mod;
        return c;
    }
};

#ifdef sigma-yyf
int main(){
    Solution so;
    int n,k=505,m,x;
    long long l,r;
    string s,t;
    vector<int> a{96,40,22,98,9,97,45,22,79,57,95,62};
    vector<string> sv;
    vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    // // 测试leetcode时，需要修改rd中的参数，
    // // 比如 fun(vector<int>&a,int k),写为 rd(v);rd(k);
    // rd(a,k);
    auto ans = so.countPartitions(a,k);
    wt(ans);wt("\n");
    return 0;
}
#endif
