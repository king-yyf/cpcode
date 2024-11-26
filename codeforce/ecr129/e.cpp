#include <bits/stdc++.h>
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
const int N = 2e5 + 5;
struct w {
	int x;  int y;
	bool operator < (const w& o) const {
		return x!=o.x ? x<o.x : y<o.y;
	}
};

int n,m,x,y,k,q;
void solve(){
	cin>>n;
	vector<w> a(n-1),b(n-1);
	int x1,y1,x2,y2;
	// map<pair<int,int>,int>m1,m2,m3,m4;
	vector<long long> v1(n),v2(n),v3(n),v4(n);
	f0(n-1){
		
		rd(x1,y1,x2,y2);
		a[i]={x1,y1};
		b[i]={x2,y2};
	}
	auto dis=[&](w x,w y){
		return abs(x.x-y.x)+abs(x.y-y.y);
	};
	for(int i=1;i<n;++i){
		if(i==1){
			v1[i]=dis(a[i],a[i-1])+1;
			v2[i]=dis(b[i],a[i-1])+1;
			v3[i]=dis(b[i-1],a[i])+1;
			v4[i]=dis(b[i-1],a[i-1])+1;
		}else{
			v1[i]=min(v1[i-1]+dis(a[i],a[i-1])+1,v2[i-1]+dis(a[i],b[i-1]))+1;
			v2[i]=min(v1[i-1]+dis(b[i],a[i-1])+1,v2[i-1]+dis(b[i],b[i-1]))+1;
			v3[i]=min(v3[i-1]+dis(a[i],a[i-1])+1,v4[i-1]+dis(b[i],b[i-1]))+1;
			v4[i]=min(v3[i-1]+dis(b[i],a[i-1])+1,v2[i-1]+dis(b[i],b[i-1]))+1;
		}
	}

	cin>>m;
	f0(m){
		rd(x1,y1,x2,y2);
		x=max(x1,y1)-1,y=max(x2,y2)-1;
		if(x==y){
			cout<<dis({x1,y1},{x2,y2})<<"\n";
		}
		else{
			bool o=0;
			vector<int> vv{x1,y1,x2,y2},uu{1,2,3,3};
			if(vv==uu)o=1;
			// if(o){
			// 	wt(v1);wt(v2);wt(v3);wt(v4);
			// }
			int u,v;
			if(x<y){
				u=x,v=y;
				long long d1=v1[v-1]-v1[u],d2=v2[v-1]-v2[u],d3=v3[v-1]-v3[u],d4=v4[v-1]-v4[u];
				// if(o){
				// 	wt(d1,' ',d2,' ',d3,' ',d4,'\n');
				// }
				// if(o){
				// 	cout<<"1 :-- "<<dis({x1,y1},a[u])+d1+dis({x2,y2},a[v-1])<<"\n";
				// 	cout<<"2 :-- "<<dis({x1,y1},a[u])+d2+dis({x2,y2},b[v-1])<<"\n";
				// 	cout<<"3 :-- "<<dis({x1,y1},b[u])+d3+dis({x2,y2},a[v-1])<<"\n";
				// 	cout<<"4 :-- "<<dis({x1,y1},b[u])+d4+dis({x2,y2},b[v-1])<<"\n";
				// }
				
				int t = v-1==u?0:1;
				long long d=min({
					dis({x1,y1},a[u])+d1+t+dis({x2,y2},a[v-1]),
					dis({x1,y1},a[u])+d2+t+dis({x2,y2},b[v-1]),
					dis({x1,y1},b[u])+d3+t+dis({x2,y2},a[v-1]),
					dis({x1,y1},b[u])+d4+t+dis({x2,y2},b[v-1])
				});
				cout<<d<<"\n";
			}else{
				u=y,v=x;
				int a1=x1,b1=y1,a2=x2,b2=y2;
				x1=a2,y1=b2,x2=a1,y2=b1;
				long long d1=v1[v-1]-v1[u],d2=v2[v-1]-v2[u],d3=v3[v-1]-v3[u],d4=v4[v-1]-v4[u];
				int t = v-1==u?0:1;
				long long d=min({
					dis({x1,y1},a[u])+d1+t+dis({x2,y2},a[v-1]),
					dis({x1,y1},a[u])+d2+t+dis({x2,y2},b[v-1]),
					dis({x1,y1},b[u])+d3+t+dis({x2,y2},a[v-1]),
					dis({x1,y1},b[u])+d4+t+dis({x2,y2},b[v-1])
				});
				cout<<d<<"\n";
			}
			
		}
	}
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
