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
	vector<string> a(n);
	rd(a);

	auto get=[&](int x, int y){
		return x*100+y;

	};

	vector<vector<int>> vis(n,vector<int>(m));
	bool o=1;

	auto chk=[&](set<int> s)->bool{
		auto t=s;
		int it=*t.begin();
		t.erase(it);
		bool o=1;
		int x=it/100,y=it%100;
		for(int i=0;i<8;++i){
			int nx=fx[i]+x,ny=fy[i]+y;
			if(nx>=0&&nx<n&&ny>=0&&ny<m){
				if(!s.count(get(nx,ny))&&a[nx][ny]=='*')o=0;
			}
		}

		it=*t.begin();
		t.erase(it);

		x=it/100,y=it%100;
		for(int i=0;i<8;++i){
			int nx=fx[i]+x,ny=fy[i]+y;
			if(nx>=0&&nx<n&&ny>=0&&ny<m){
				if(!s.count(get(nx,ny))&&a[nx][ny]=='*')o=0;
			}
		}

		it=*t.begin();

		x=it/100,y=it%100;
		for(int i=0;i<8;++i){
			int nx=fx[i]+x,ny=fy[i]+y;
			if(nx>=0&&nx<n&&ny>=0&&ny<m){
				if(!s.count(get(nx,ny))&&a[nx][ny]=='*')o=0;
			}
		}

		return o;
	};

	

	auto chk1=[&](int x, int y)->bool{
		if(x<n-1&&y<m-1&&a[x+1][y]=='*'&&a[x+1][y+1]=='*') {

			set<int> s;
			s.insert(get(x,y));
			s.insert(get(x+1,y));
			s.insert(get(x+1,y+1));
			if(chk(s)) return 1;
		}
		return 0;
	};

	auto co1=[&](int x,int y){
		vis[x][y]=1;
		vis[x+1][y]=1;
		vis[x+1][y+1]=1;
	};

	auto chk2=[&](int x, int y)->bool{
		if(x<n-1&&y>0&&a[x+1][y]=='*'&&a[x+1][y-1]=='*') {
			set<int> s;
			s.insert(get(x,y));
			s.insert(get(x+1,y));
			s.insert(get(x+1,y-1));
			if(chk(s)) return 1;
		}
		return 0;
	};

	auto co2=[&](int x,int y){
		vis[x][y]=1;
		vis[x+1][y]=1;
		vis[x+1][y-1]=1;
	};

	auto chk3=[&](int x, int y)->bool{
		if(x<n-1&&y<m-1&&a[x][y+1]=='*'&&a[x+1][y+1]=='*') {
			set<int> s;
			s.insert(get(x,y));
			s.insert(get(x,y+1));
			s.insert(get(x+1,y+1));
			if(chk(s)) return 1;
		}
		return 0;
	};

	auto co3=[&](int x,int y){
		vis[x][y]=1;
		vis[x+1][y+1]=1;
		vis[x][y+1]=1;
	};

	auto chk4=[&](int x, int y)->bool{
		if(x<n-1&&y<m-1&&a[x+1][y]=='*'&&a[x][y+1]=='*') {
			set<int> s;
			s.insert(get(x,y));
			s.insert(get(x+1,y));
			s.insert(get(x,y+1));
			if(chk(s)) return 1;
		}
		return 0;
	};

	auto co4=[&](int x,int y){
		vis[x][y]=1;
		vis[x+1][y]=1;
		vis[x][y+1]=1;
	};

	for(int i=0;i<n;++i){
		for(int j=0;j<m;++j){
			if(a[i][j]=='.'||vis[i][j]) continue;
			bool ok=0;
			if(chk1(i,j)){
				ok=1;
				co1(i,j);
			}else if(chk2(i,j)){
				ok=1;
				co2(i,j);
			}else if(chk3(i,j)){
				ok=1;
				co3(i,j);
			}else if(chk4(i,j)){
				ok=1;
				co4(i,j);
			}
			if(ok==0){
				o=0;
			}
		}
	}
	if(o)cout<<"YES\n";
	else cout<<"NO\n";
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve(case_i);
	}
	return 0;
}
