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

int get(int x,int y){
	if(x<y) return min(y-x,x+m-y);
	return min(x-y,m-x+y);
}
long long f[45][45][10];
void solve(){
	int d,it=-1;
	rd(n,d);
	vector<int> v;
	f0(n){
		cin>>x;
		if(it==-1) {
			v.push_back(x);
			it=x;
		}else{
			if(x==it)continue;
			v.push_back(x);
			it=x;
		}
	}
	if(d>10||n>40){
		wt("-1\n");
		return;
	}

	mst(f,0x3f);
	n=sz(v);m=d;

	for(int l=1;l<=n;++l){
		for(int i=0;i+l<=n;++i){
			if(l==1){
				for(int h=0;h<d;++h){
					f[i][i][h]=get(v[i],h);
				}
			}else{
				int j=i+l-1;
				for(int h=0;h<d;++h){
					for(int k=i;k<=j;++k){
						if(k==i){
							f[i][j][h]=min(f[i][j][h],get(v[k],h)+f[i+1][j][v[k]]);
							f[i][j][h]=min(f[i][j][h],get(v[k],v[k+1])+f[i+1][j][h]);							
						}else if(k==j){						
							f[i][j][h]=min(f[i][j][h],get(v[k],h)+f[i][j-1][v[k]]);
							f[i][j][h]=min(f[i][j][h],get(v[k],v[k-1])+f[i][j-1][h]);
						}else {
							f[i][j][h]=min({f[i][j][h],f[i][k-1][v[k]]+get(v[k],v[k+1])+f[k+1][j][h],f[k+1][j][v[k]]+get(v[k],v[k-1])+f[i][k-1][h]});
						}	
					}
					
				}
			}
			
		}
	}
	wt(f[0][n-1][0],'\n');
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
