#include <bits/stdc++.h>
using namespace std;

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
const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 10;

int n,m,x,k;

void solve(){
	cin>>n;
	long long  a0,an,b0,bn;
	multiset<long long > m1,m2;
	f1(n){
		cin>>x;
		m1.insert(x);
		if(i==0)a0=x;
		if(i==n-1)an=x;
	}
	f1(n){
		cin>>x;
		m2.insert(x);
		if(i==0)b0=x;
		if(i==n-1)bn=x;
	}
	m1.insert(1e12);m1.insert(-1e12);
	m2.insert(1e12);m2.insert(-1e12);
	long long s1=abs(a0-b0)+abs(an-bn);

	// m1.erase(m1.find(a0));
	// m2.erase(m2.find(b0));
	// m1.erase(m1.find(an));
	// m2.erase(m2.find(bn));

	long long s2=abs(a0-b0);

	auto it=m2.lower_bound(an);
	long long t=(*it)-an;
	it--;
	t=min(t,an-(*it));
	s2+=t;
	auto it1=m1.lower_bound(bn);
	t=(*it1)-bn;
	it1--;
	t=min(t,bn-(*it1));
	s2+=t;

	long long s3=abs(an-bn);
	
	it=m2.lower_bound(a0);
	t=(*it)-a0;
	it--;
	t=min(t,a0-(*it));
	s3+=t;
	it1=m1.lower_bound(b0);
	t=(*it1)-b0;
	it1--;
	t=min(t,b0-(*it1));
	s3+=t;

	long long s4=0;

	it=m2.lower_bound(a0);
	t=(*it)-a0;
	it--;
	t=min(t,a0-(*it));
	s4+=t;
	it1=m1.lower_bound(b0);
	t=(*it1)-b0;
	it1--;
	t=min(t,b0-(*it1));
	s4+=t;
	it=m2.lower_bound(an);
	t=(*it)-an;
	it--;
	t=min(t,an-(*it));
	s4+=t;
	it1=m1.lower_bound(bn);
	t=(*it1)-bn;
	it1--;
	t=min(t,bn-(*it1));
	s4+=t;

	long long s5=abs(a0-bn)+abs(an-b0);

	long long s6=abs(a0-bn);

	it=m2.lower_bound(an);
	t=(*it)-an;
	it--;
	t=min(t,an-(*it));
	s6+=t;
	it1=m1.lower_bound(b0);
	t=(*it1)-b0;
	it1--;
	t=min(t,b0-(*it1));
	s6+=t;

	long long s7=abs(an-b0);
	
	it=m2.lower_bound(a0);
	t=(*it)-a0;
	it--;
	t=min(t,a0-(*it));
	s7+=t;
	it1=m1.lower_bound(bn);
	t=(*it1)-bn;
	it1--;
	t=min(t,bn-(*it1));
	s7+=t;

	// long long s8=0;

	// it=m2.lower_bound(a0);
	// t=(*it)-a0;
	// it--;
	// t=min(t,a0-(*it));
	// s4+=t;
	// it1=m1.lower_bound(b0);
	// t=(*it1)-b0;
	// it1--;
	// t=min(t,b0-(*it1));
	// s4+=t;
	// it=m2.lower_bound(an);
	// t=(*it)-an;
	// it--;
	// t=min(t,an-(*it));
	// s4+=t;
	// it1=m1.lower_bound(bn);
	// t=(*it1)-bn;
	// it1--;
	// t=min(t,bn-(*it1));
	// s4+=t;


	vector<long long> v{s1,s2,s3,s4,s5,s6,s7};
	cout<<Min(v)<<"\n";
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
        // cout << "Case #" << case_i << ": ";
		solve();
	}
	return 0;
}
