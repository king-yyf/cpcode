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
    using ll=long long;
    long long maximumBeauty(vector<int>& a, long long k, int t, int f, int p) {
        int n=sz(a);
        // if(n==1){
        //     if(a[0]<t)
        // }
        sort(a.rbegin(),a.rend());
        vector<long long> ps(n+1);
        for(int i=1;i<=n;++i) ps[i]=ps[i-1]+a[i-1];
        long long s=0;
        int mx=-1,c=0;
        for(int i=0;i<n;++i){
            if(a[i]>=t) {
                mx=i;
                c++;
                continue;
            }
            s+=t-a[i];
            if(s>k) break;
            mx=i;
        }
        
        ll ans=0,cur;
        s=0;
        ll s1,s2;
        for(int i=c-1;i<=mx;++i){
            if(i==n-1){
                ans=max(ans,n*1ll*f);
                break;
            }
            if(i>=0 && a[i]<t) s+=t-a[i];
            s1=k-s;
            if(a[n-1]>=t-1){
                cur=(i+1ll)*f+(t-1)*p;
                ans=max(ans,cur);
                continue;
            }
            int l=a[n-1],r=t-1,mx1=a[n-1];
            while(l<=r){
                int mid=(l+r)/2;
                int l1=i+1,r1=n-1,x=n;
                while(l1<=r1){
                    int m2=(l1+r1)/2;
                    if(a[m2]>=mid){
                        l1=m2+1;
                    }else {
                        x=m2;
                        r1=m2-1;
                    }
                }
                ll sm=ps[n]-ps[x];
                ll nd=(n-x+0ll)*mid-sm;
                if(nd<=s1){
                    mx1=mid;
                    l=mid+1;
                }else r=mid-1;
            }
            // cout<<
            cur=(i+1ll)*f+mx1*1ll*p;
            ans=max(ans,cur);
        }
        return ans;
    }
};
