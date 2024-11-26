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

int n,m,x,y,k;
int a[110][110],c[110],d[110];
struct W
{
	int x,t,cnt;
	bool operator < (const W& o)const{
		return t>o.t;
	}
};
void solve(){
	int e,w;
	rd(e,w);
	mst(c,0);//cnt of pos
	mst(d,0);
	vector<W> v;

	f1(e){
		f3(j,w){
			cin>>a[i][j];
		}
	}
	int ans=0;
	for(int i=1;i<=e;++i){
		while(v.size()&&v.back().t<=i){
			c[v.back().x]-=v.back().cnt;
			d[v.back().t]-=v.back().cnt;
			v.pop_back();
			ans+=v.back().cnt;
		}
		vector<W> b;
		for(int j=1;j<=w;++j){
			if(a[i][j]>c[j]){
				int t=a[i][j]-c[j],u=t;
				int x=a[i][j],p=e+1;
				vector<W> tmp;
				int cur=0;
				for(int k=i+1;k<=e&&u;++k){
					if(a[k][j]<x){
						y=min(u,x-a[k][j]);
						tmp.push_back({j,k,y});
						u-=y;
						cur+=y;
						x=a[k][j];
					}
				}
				for(auto vv:tmp){
					b.push_back(vv);
				}
				if(t-cur>0)
					b.push_back({j,e+1,t-cur});
			}
		}
		if(b.size()>0){
			int mx=0,s=0;
			for(int j=0;j<b.size();++j){
				mx=max(mx,b[j].t);
			}
			for(int j=0;j<mx;++j){
				ans+=d[j];
			}
			for(auto vv:b){
				v.push_back(vv);
				c[vv.x]+=vv.cnt;
				d[vv.t]+=vv.cnt;
				ans+=vv.cnt;
			}

		}
		sort(v.begin(),v.end());
		
	}
	while(v.size()>0){
		ans+=v.back().cnt;
		v.pop_back();
	}
	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
        cout << "Case #" << case_i << ": ";
		solve();
	}
	return 0;
}
