#include <bits/stdc++.h>
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

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) { cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    bool f=1;
	each(a, x) if(f==1) {wt(a); f=0;} else {cout<<' ';wt(a);}
}
const int mod = 998244353; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

long long  n,m,x,y,k;


void solve(){

	cin>>n;
	long long s=(n*(n+1ll)/2)%mod;
	long long s1=(s*n)%mod;
	for(long long i=1;i*i<=n;++i){
		long long l=n/(i+1)+1,r=n/i;
		if(n%r==0)r--;
		if(l>r) continue;
		int m=r-l+1;
		long long d=i+1;
		long long c=(n/l+1ll)*l-n;
		long long x=l-1,y=c-d;
		long long s2=(d*m*(m+1ll)*(2ll*m+1ll)/6ll)%mod;
		long long s3=((y+d*x)*(m*(m+1ll)/2))%mod;
		long long s4=(((m*x)%mod)*y)%mod;
		s1=(s1+s2+s3+s4)%mod;
		long long j=n/i;
		// if(j>i){
		// 	l=i,r=n/j;
		// 	if(n%r==0)r--;
		// 	if(l>r)continue;
		// 	c=(n/l+1ll)*l-n;
		// 	s1=(s1+l*c)%mod;
		// }
		s1=s1%mod;
		if(s1<0)s1+=mod;
	}
	for(long long i=1;i*i<=n;++i){
		if(n%i==0) continue;
		long long c=(n/i+1ll)*i-n;
		s1=(s1+i*c)%mod;
	}
	wt(s1,'\n');
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int t=1;
	cin>>t;
	while(t--)
	solve();
	return 0;
}
