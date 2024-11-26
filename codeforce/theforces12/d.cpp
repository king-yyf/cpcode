#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define yn(o) cout << ((o) ? "Yes" : "No") << "\n";
#define YN(o) cout << ((o) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

int p[16][3][3]={
	{{0,0,0},
	{0,0,0},
	{0,0,0}},
	{{0,0,0},
	{0,0,0},
	{1,0,1}},
	{{0,0,0},
	{0,1,0},
	{0,0,1}},
	{{0,0,0},
	{0,1,0},
	{1,0,0}},
	{{0,0,1},
	{0,0,0},
	{0,0,1}},
	{{0,0,1},
	{0,0,0},
	{1,0,0}},
	{{0,0,1},
	{0,1,0},
	{0,0,0}},
	{{0,0,1},
	{0,1,0},
	{1,0,1}},
	{{1,0,0},
	{0,0,0},
	{0,0,1}},
	{{1,0,0},
	{0,0,0},
	{1,0,0}},
	{{1,0,0},
	{0,1,0},
	{0,0,0}},
	{{1,0,0},
	{0,1,0},
	{1,0,1}},
	{{1,0,1},
	{0,0,0},
	{0,0,0}},
	{{1,0,1},
	{0,0,0},
	{1,0,1}},
	{{1,0,1},
	{0,1,0},
	{0,0,1}},
	{{1,0,1},
	{0,1,0},
	{1,0,0}}
};

void ac_yyf(int tt) {
    rd(n,m);
    vector a(n,vector<int>(m)),b(n,vector<int>(m));
    f0(n)rd(a[i]);f0(n)rd(b[i]);
    f0(n)f2(j,m)a[i][j]^=b[i][j];
   	// dbg("tt= ",tt);wt(nl);
   	// f0(n){
   	// 	f2(j,m){
   	// 	dbg(a[i][j]);
   	// }
   	// wt(nl);
   	// }
   	// wt(nl);

   	for(int i=0;i+3<=n;++i){
   		for(int j=0;j+3<=m;++j){
   			if(i+3==n){

   				if(a[i][j]==0&&a[i+1][j]==0&&a[i+2][j]==0)continue;

   				for(int k=0;k<16;++k){
   					if(p[k][0][0]==a[i][j]&&p[k][1][0]==a[i+1][j]&&p[k][2][0]==a[i+2][j]){
   						for(int x=0;x<3;++x){
   							for(int y=0;y<3;++y){
   								a[i+x][j+y]^=p[k][x][y];
   							}
   						}
   						break;
   					}
   				}


   			} else if(j+3==m){
   				if(a[i][j]==0&&a[i][j+1]==0&&a[i][j+2]==0)continue;

   				for(int k=0;k<16;++k){
   					if(p[k][0][0]==a[i][j]&&p[k][0][1]==a[i][j+1]&&p[k][0][2]==a[i][j+2]){
   						for(int x=0;x<3;++x){
   							for(int y=0;y<3;++y){
   								a[i+x][j+y]^=p[k][x][y];
   							}
   						}
   						break;
   					}
   				}
   			}
   			else if(a[i][j]==1){
   				for(int k=0;k<16;++k){
   					if(p[k][0][0]==1){
   						for(int x=0;x<3;++x){
   							for(int y=0;y<3;++y){
   								a[i+x][j+y]^=p[k][x][y];
   							}
   						}
   						break;
   					}
   				}
   			}
   		}
   	}

   	dbg("tt= ",tt);wt(nl);
   	f0(n){
   		f2(j,m){
   		dbg(a[i][j]);
   	}
   	wt(nl);
   	}
   	wt(nl);


   	vector<vector<int>> c(3,vector<int>(3));
   	for(int i=n-3;i<n;++i){
   		for(int j=m-3;j<m;++j){
   			c[i-n+3][j-m+3]=a[i][j];
   		}
   	}
   	bool o=0;
   	for(int i=0;i<16;++i){
   		bool o1=1;
   		for(int x=0;x<3;++x){
   			for(int y=0;y<3;++y){
   				if(p[i][x][y]!=c[x][y]){
   					o1=0;break;
   				}
   			}
   		}
   		if(o1){
   			o=1;break;
   		}
   	}
   	YN(o);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
