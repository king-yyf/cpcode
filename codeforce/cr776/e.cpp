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
int a[N],b[N];
int n,m,x,y,k,d;
void solve(){
	rd(n,d);
	f1(n) rd(a[i+1]);
	map<int,int>mp;
	// a[n]=d;
	int s=0;
	for(int i=1;i<=n;++i){
		int t=a[i]-a[i-1]-1;
		mp[t]++;
		b[i]=t;
	}
	if(d==n) {
		wt("0\n");
		return ;
	}
	if(n==1){
		wt(d-1,"\n");
		return;
	}
	auto it=mp.begin();
	x=it->first,y=it->second;
	if(y>=3){
		wt(x,'\n');
		return;
	}
	vector<int> v;
	for(int i=1;i<=n;++i){
		if(b[i]==x){
			v.push_back(i);
		}
	}
	int ans=x;
	if(y==1){
		mp[x]--;
		int t=v[0];
		auto rb=mp.rbegin();
		int x1=rb->first,y1=rb->second;
		auto c=mp;
		if(t>1){
			int u=b[t-1];
			mp[u]--;
			if(mp[u]==0) mp.erase(u);
			mp[u+x+1]++;
			x1=max(x1,u+1+x);
			mp.erase(x);
			it=mp.begin();
			int tt=ans;
			if((x1-1)/2>tt){
				tt=it->first;
				if(tt>(x1-1)/2)tt=(x1-1)/2;
			}
			ans=max(ans,tt);
		}
		mp=c;
		if(t<n) {
			int u=b[t+1];
			mp[u]--;
			if(mp[u]==0) mp.erase(u);
			mp[u+x+1]++;
			x1=max(x1,u+1+x);
			mp.erase(x);
			it=mp.begin();
			int tt=ans;
			if((x1-1)/2>tt){
				tt=it->first;
				if(tt>(x1-1)/2)tt=(x1-1)/2;
			}
			ans=max(ans,tt);
		}else {
			if(a[n]<d) {
				a[n]=d;
				mp.erase(x);
				auto ccc=mp;
				mp[d-a[n-1]-1]++;
				// for(auto&[k,vv]:mp){
				// 	wt(k,". ..", vv, '\n');
				// }
				it=mp.begin();
				int tmp=it->first;
				if(tmp>ans) ans=tmp;
				mp=ccc;
				int u=b[n-1];
				mp[u]--;
				if(mp[u]==0) mp.erase(u);
				mp[u+x+1]++;
				it=mp.begin();
				tmp=it->first;
				if(tmp>ans) ans=tmp;
			}
		}
	}else {
		mp[x]--;
		int t=v[0];
		auto rb=mp.rbegin();
		int x1=rb->first,y1=rb->second;
		if(t<n) {
			int u=b[t+1];
			mp[u]--;
			if(mp[u]==0) mp.erase(u);
			mp[u+x+1]++;
			x1=max(x1,u+1+x);
		}
		if(mp[x]>0){
			return;
		}
		mp.erase(x);
		if((x1-1)/2>ans) {
			it=mp.begin();
			ans=it->first;
			if(ans>(x1-1)/2)ans=(x1-1)/2;
		}
		mp[d-a[n]-1]++;
		it=mp.begin();
		if((it->first)>ans)ans=it->first;
	}
	wt(ans,'\n');
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
