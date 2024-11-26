#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define ln "\n";
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class A> void rd(vector<A>& v);  // read vector
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

const int mod = 1e9+7; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;
struct w {
    int x;  int y;
    bool operator < (const w& o) const {
        return x!=o.x ? x<o.x : y<o.y;
    }
};

int n,m,x,y,k,q;
void solve(int tt){
	double  a,r;
	rd(a,r);
	auto c1 = [&](double a){
		return sqrt(6.0)*a/4;
	};
	auto c2 = [&](double a){
		return sqrt(3.0)*a/2;
	};
	auto c3 = [&](double a){
		return sqrt(2.0)*a/2;
	};
	auto c4 = [&](double a){

		return sqrt(3.0) * (sqrt(5.0)+1.0)*a/4.0;
	};
	auto c5 = [&](double a){
		return sqrt(10.0+2*sqrt(5.0))*a/4;
	};


	dbg(a,r,c1(a),c2(a),c3(a),c4(a),c5(a),'\n');

	// bool o=0;

	// auto isp1 = [&](double a, double x)->bool{
		
	// 	double r1;
	// 	while(a<x){
	// 		r1=c1(a);
	// 		if(abs(r1-x)<1e-8) return 1;
	// 		a=a+a;
	// 	}
	// 	if(abs(r1-x)<1e-8) return 1;
	// 	return 0;
	// };

	// auto isp2 = [&](double a, double x)->bool{
		
	// 	double r1;
	// 	while(a<x){
	// 		r1=c2(a);
	// 		if(abs(r1-x)<1e-8) return 1;
	// 		a=a+a;
	// 	}
	// 	if(abs(r1-x)<1e-8) return 1;
	// 	return 0;
	// };
	// auto isp3 = [&](double a, double x)->bool{
		
	// 	double r1;
	// 	while(a<x){
	// 		r1=c3(a);
	// 		if(abs(r1-x)<1e-8) return 1;
	// 		a=a+a;
	// 	}
	// 	if(abs(r1-x)<1e-8) return 1;
	// 	return 0;
	// };
	// auto isp4 = [&](double a, double x)->bool{
		
	// 	double r1;
	// 	while(a<x){
	// 		r1=c4(a);
	// 		if(abs(r1-x)<1e-8) return 1;
	// 		a=a+a;
	// 	}
	// 	if(abs(r1-x)<1e-8) return 1;
	// 	return 0;
	// };
	// auto isp5 = [&](double a, double x)->bool{
		
	// 	double r1;
	// 	while(a<x){
	// 		r1=c5(a);
	// 		if(abs(r1-x)<1e-8) return 1;
	// 		a=a+a;
	// 	}
	// 	if(abs(r1-x)<1e-8) return 1;
	// 	return 0;
	// };

	// if(isp1(a,r)) o=1;
	// if(isp2(a,r)) o=1;
	// if(isp3(a,r)) o=1;
	// if(isp4(a,r)) o=1;
	// if(isp5(a,r)) o=1;


	if(c1(a)>=r||c2(a)>=r||c3(a)>=r||c4(a)>=r||c5(a)>=r){
		cout<<"YES\n";
	}else cout<<"NO\n";
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(6);
	int T=1;
	// cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve(case_i);
	}
	return 0;
}
