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
const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

long long  n,m,x,y,k;
long long  a[3005];
void solve(){
	rd(n,k);
	long long  s=0,c=0;
	
	f0(n){
		cin>>a[i];
		s+=a[i];
		c+=a[i]==0;
	}
	long long s1=-s;
	if(s1>k*c||s1<-(k*c)){
		wt("-1\n");
		return;
	}

	long long mx=0,mi=0,p=0,s2=s1,t=0;
	long long ans=0;
	f2(j,n){
		mx=0,mi=0,p=0,s2=s1,t=0;
		for(int i=0;i<=j;++i){
			if(a[i]==0){
				if(c-t==1){
					p+=s2;
					mx=max(mx,p);
					mi=min(mi,p);
					t++;
				}else{
					long long mm=min(s2+(k*(c-t-1)),k);
					// cout<<"i="<<i<<"\n";
					// cout<<mm<<", "<<s2<<", "<<c<<", " <<t<<", "<<"\n";
					p+=mm;
					mx=max(mx,p);
					mi=min(mi,p);
					t++;
					s2-=mm;
				}	
			}else{
				p+=a[i];
				mx=max(mx,p);
				mi=min(mi,p);
			}
		}
		for(int i=j+1;i<n;++i){
			if(a[i]==0){
				if(c-t==1){
					p+=s2;
					mx=max(mx,p);
					mi=min(mi,p);
					t++;
				}else{
					long long mm=max(s2-(k*(c-t-1)),-k);
					p+=mm;
					mx=max(mx,p);
					mi=min(mi,p);
					t++;
					s2-=mm;
				}
			}else{
				p+=a[i];
				mx=max(mx,p);
				mi=min(mi,p);
			}
		}
		ans=max(ans,mx-mi+1);
	}

	// cout<<mx<<", "<<mi<<"\n";
	
	f2(j,n){
		mx=0,mi=0,p=0,s2=s1,t=0;
		for(int i=0;i<=j;++i){
			if(a[i]==0){
				if(c-t==1){
					p+=s2;
					mx=max(mx,p);
					mi=min(mi,p);
					t++;
				}else{
					long long mm=max(s2-(k*(c-t-1)),-k);
					p+=mm;
					mx=max(mx,p);
					mi=min(mi,p);
					t++;
					s2-=mm;
				}
			}else{
				p+=a[i];
				mx=max(mx,p);
				mi=min(mi,p);
			}
		}
		for(int i=j+1;i<n;++i){
			if(a[i]==0){
				if(c-t==1){
					p+=s2;
					mx=max(mx,p);
					mi=min(mi,p);
					t++;
				}else{
					long long mm=min(s2+(k*(c-t-1)),k);
					// cout<<"i="<<i<<"\n";
					// cout<<mm<<", "<<s2<<", "<<c<<", " <<t<<", "<<"\n";
					p+=mm;
					mx=max(mx,p);
					mi=min(mi,p);
					t++;
					s2-=mm;
				}	
			}else{
				p+=a[i];
				mx=max(mx,p);
				mi=min(mi,p);
			}
		}
		ans=max(ans,mx-mi+1);
	}

	wt(ans,'\n');
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	// cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve();
	}
	return 0;
}
