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
	rd(n,m);
	vector<vector<int>> a(n,vector<int>(m));
	f0(n){
		string s;
		cin>>s;
		f2(j,m) if(s[j]=='.') a[i][j]=1;
	}

	int x1,y1,x2,y2;

	function<void(int,int)> dfs=[&](int x, int y){
		a[x][y]=2;
		x1=max(x1,x);
		y1=max(y1,y);
		f0(4){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx>=0&&nx<n&&ny>=0&&ny<m){
				if(a[nx][ny]==0) {
					dfs(nx,ny);
				}
			}
		}
	};

	// dbg(s);


	vector<int> c(3);


	vector<vector<int>> p;

	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			if(a[i][j]==0) {
				x1=i,y1=j;
				dfs(i,j);

				p.push_back({i,j,x1,y1});
			}
		}
	}

	bool ok;


	function<void(int,int)> dfs1=[&](int x, int y){
		a[x][y]=2;
		f0(4){
			int nx=x+dx[i],ny=y+dy[i];
			if(nx<x1||nx>x2||ny<y1||ny>y2) ok=0;
			if(nx>=x1&&nx<=x2&&ny>=y1&&ny<=y2){
				if(a[nx][ny]==1) {
					dfs1(nx,ny);
				}
			}
		}
	};

	for(auto&v:p){
		x1=v[0],y1=v[1],x2=v[2],y2=v[3];
		int t=0;
		for(int i=x1;i<=x2;++i){
			for(int j=y1;j<=y2;++j){
				if(a[i][j]==1) {
					ok=1;
					
					dfs1(i,j);
					if(ok==1)t++;
				}
			}
		}
		if(t>=0&&t<3) c[t]++;
	}

	wt(c);

}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	// cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve(case_i);
	}
	return 0;
}
