#include<bits/stdc++.h>
using namespace std;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
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

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) { cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    for (int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];
}
const int mod = 1e9+7; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 1e5 + 5;
struct w {
    int x;  int y;
    bool operator < (const w& o) const {
        return x!=o.x ? x<o.x : y<o.y;
    }
};

long long tr[N];
int n;

class Solution {
public:
    int totalStrength(vector<int>& a) {
        int n=a.size();
        vector<int> v(n,n),l(n,-1);
        stack<int> s;
        for(int i=0;i<n;++i){
            while(!s.empty()&&a[s.top()]>=a[i]){
                v[s.top()]=i;
                s.pop();
            }
            s.push(i);
        }

        s=stack<int>();
        for(int i=n-1;i>=0;--i){
            while(!s.empty()&&a[s.top()]>a[i]){
                l[s.top()]=i;
                s.pop();
            }
            s.push(i);
        }
        wt(v);
        wt(l);

       vector<int> s1(n+1),s2(n+1);
       f0(n) s1[i+1]=(s1[i]+a[i])%mod;
       f0(n) s2[i+1]=(s2[i]+s1[i+1])%mod;
       long long res=0;
       f1(n){
       	 long long t=(i-l[i])*(ss[r[i]]-ss[i-1])%mod;
       	 t-=(r[i]-i)*(ss[i-1]-)
       }
};


#ifdef LOCAL
int main(){
	vector<int> v{5,4,6};
	Solution so;
	auto c=so.totalStrength(v);
	cout<<c<<"\n";
    return 0;
}
#endif
