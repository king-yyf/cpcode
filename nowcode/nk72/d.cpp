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

void ac_yyf(int tt) {
    rd(n,m);
    vector a(n,vector<ll>(m));
    f0(n)rd(a[i]);int t;
    

    vector f(n,vector<long long>(m)),g(n,vector<long long>(m));

    f[0][0]=a[0][0];
    for(int i=1;i<n;++i)
    	f[i][0]=f[i-1][0]+a[i][0];
    for(int j=1;j<m;++j)
    	f[0][j]=f[0][j-1]+a[0][j];
    for(int i=1;i<n;++i)
    	for(int j=1;j<m;++j)
    		f[i][j]=max(f[i-1][j],f[i][j-1])+a[i][j];

    g[n-1][m-1]=a[n-1][m-1];

    for(int i=n-2;i>=0;--i)
    	g[i][m-1]=g[i+1][m-1]+a[i][m-1];
    for(int j=m-2;j>=0;--j)\
    	g[n-1][j]=g[n-1][j+1]+a[n-1][j];

    for(int i=n-2;i>=0;--i)
    	for(int j=m-2;j>=0;--j)
    		g[i][j]=max(g[i+1][j],g[i][j+1])+a[i][j];

    // f0(n){
    // 	f2(j,m){
    // 		if(i==0&&j==0) f[i][j]=a[0][0];
    // 		else if(i==0){
    // 			cmx(f[i][j],f[i][j-1]+a[i][j]);
    // 		}else if(j==0) cmx(f[i][j],f[i-1][j]+a[i][j]);
    // 		else {
    // 			cmx(f[i][j],max(f[i-1][j],f[i][j-1])+a[i][j]);
    // 		}
    // 	}
    // }

    // r3(i,n,0)r3(j,m,0){
    // 	if(i==n-1&&j==m-1) g[i][j]=a[i][j];
	// 	else if(i==n-1){
	// 		cmx(g[i][j],g[i][j+1]+a[i][j]);
	// 	}else if(j==m-1) cmx(g[i][j],g[i+1][j]+a[i][j]);
	// 	else {
	// 		cmx(g[i][j],max(g[i+1][j],g[i][j+1])+a[i][j]);
	// 	}
    // }

    long long s=f[n-1][m-1];

    // wt(s,nl);

    rd(t);

    f3(_,0,t){
    	rd(k);
    	 vector<pair<int,int> > p(k);
	    f0(k){
	    	rd(x,y);
	    	x--,y--;
	    	p[i]={x,y};
	    }
	    ll c=s;

	    f0(k){
	    	for(int j=0;j<k;++j){
	    		if(i!=j){
	    			ll cu=f[p[i].first][p[i].second]+g[p[j].first][p[j].second];
	    			
	    			cmx(c,cu);
	    		}
	    	}
	    }
	    wt(c,nl);
    }


   

}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
