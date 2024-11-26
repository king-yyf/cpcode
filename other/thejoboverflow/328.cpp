#include <bits/stdc++.h>
using namespace std;

// http://www.thejoboverflow.com/problem/376/

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
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
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';

int n, m, q;
int x, y, k;
string s, t;

const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int N=1010,M=12;
bool vis[N][N][M];
int minStep(vector<vector<char>> &g, int k) {
	int n=sz(g),m=sz(g[0]), x1,y1,x2,y2;
	f0(n)f2(j,m){
		if(g[i][j]=='S'){x1 = i, y1 = j;}
		else if(g[i][j]=='G') {
			x2=i,y2=j;
		}
	}
	mst(vis,0);
	queue<ar3>q;
	q.push({k,x1,y1});
	vis[x1][y1][k]=1;
	int res=0;
	while(sz(q)){
		int siz=sz(q);
		while(siz--){
			auto cur=q.front();
			q.pop();
			int K=cur[0],x=cur[1],y=cur[2];
			if(x==x2&&y==y2) return res;
			f0(4){
				int nx=x+dx[i],ny=y+dy[i];
				if(nx>=0&&nx<n&&ny>=0&&ny<m){
					if(g[nx][ny]=='#'&&K>0&&!vis[nx][ny][K-1]){
						vis[nx][ny][K-1]=true;
						q.push({K-1,nx,ny});
					}
					if(!vis[nx][ny][K]&&(g[nx][ny]=='.'||g[nx][ny]=='G')){
						vis[nx][ny][K]=true;
						q.push({K,nx,ny});
					}
				}
			}
		}
		res++;
	}
	return -1;
}

void ac_yyf(int tt) {
    rd(n,m,k);
    vector<vector<char>> a(n, vector<char>(m));
    rd(a);
    auto ans=minStep(a, k);
    wt(ans,nl);
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
