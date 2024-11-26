#include<bits/stdc++.h>
using namespace std;
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
    int maximumWhiteTiles(vector<vector<int>>& a, int k) {
        sort(all(a));
        int n=sz(a);
        vector<long long> s(n+1);
        f0(n)s[i+1]=s[i]+a[i][1]-a[i][0]+1;
        int mx=0;
        f0(n){
        	long long  l=i,r,c,p=a[i][0]+k-1,x=l-1;
            // cout<<a[i][0]<<", "<<k<<", "<<p<<"\n";
        	if(a[n-1][1]<=p) c=s[n]-s[i];
        	else{
        		r=n-1;
        		while(l<=r){
        			long long md=(l+r)/2;
        			if(a[md][1]<=p){
        				x=md;
        				l=md+1;
        			}else{
        				r=md-1;
        			}
        		}
        		c=s[x+1]-s[i];
        		if(x<n-1)x++;
        		int q=max(0ll,p-a[x][0]+1);
        		c+=q;
        	}
        	if(c>mx)mx=c;
        	wt("i=",i,' ',c,' ',x,' ','\n');
        }
        cout<<"\n\n";
        for(int i=n-1;i>=0;--i){
        	long long r=i,l,c,p=a[i][1]-k+1,x=r+1;
            // wt(a[i][1],' ',p,'\n');
        	if(a[0][0]>=p) c=s[i+1];
        	else{
        		l=0;
        		while(l<=r){
        			long long md=(l+r)/2;
        			if(a[md][0]>=p){
        				x=md;
        				r=md-1;
        			}else l=md+1;
        		}
        		c=s[i+1]-s[x];
        		if(x>0)x--;
        		int q=max(0ll,a[x][1]-p+1);
        		c+=q;
        	}
        	wt("i=",i,' ',c,' ',x,'\n');
        	if(c>mx)mx=c;
        }
        return mx;
    }
};

#ifdef LOCAL
int main(){
        vector<vector<int>>  v={{1,5},{10,11},{12,18},{20,25},{30,32}};
        int k=10;
        Solution so;
        auto t=so.maximumWhiteTiles(v,k);
        cout<<t<<"\n";
        return 0;
}
#endif

