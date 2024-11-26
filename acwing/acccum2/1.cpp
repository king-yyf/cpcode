/**
 *    author:  sigma-yyf
 *    created: 02.04.2023 19:00:03       
**/
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
#define rep(x, s, t) for(llint (x) = (s); (x) <= (t); (x)++)
#define chmin(x, y) (x) = min((x), (y))
#define chmax(x, y) (x) = max((x), (y))
#define all(x) (x).begin(),(x).end()
#define inf 1e18
 
const int mod = 1e9+7; // 998244353;
const char nl = '\n';
const int N = 2e5 + 5;

typedef long long llint;
typedef long long ll;
typedef pair<llint, llint> P;
 
ll h, w, k;
ll sx, sy, tx, ty;
ll dist[1005][1005];
bool used[1005][1005][4];
char c[1005][1005];
ll dx[] = {1, 0, -1, 0}, dy[] = {0, -1, 0, 1};
 
int main(void){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> h >> w >> k;
	rep(y, 1, h) rep(x, 1, w) cin >> c[x][y];
	cin >> sy >> sx >> ty >> tx;
	
	queue<P> Q;
	Q.push(P(sx, sy));
	rep(y, 1, h) rep(x, 1, w) dist[x][y] = inf;
	dist[sx][sy] = 0;
	
	while(Q.size()){
		ll x = Q.front().first, y = Q.front().second;
		Q.pop();
		rep(i, 0, 3){
			rep(j, 1, k){
				ll nx = x + dx[i]*j, ny = y + dy[i]*j;
				if(nx < 1 || nx > w || ny < 1 || ny > h) break;
				if(c[nx][ny] == '#') break;
				if(used[nx][ny][i]) break;
				used[nx][ny][i] = true;
				if(dist[nx][ny] > dist[x][y] + 1){
					dist[nx][ny] = dist[x][y] + 1;
					Q.push(P(nx, ny));
				}
			}
		}
	}
	
	/*rep(y, 1, h){
		rep(x, 1, w) cout<< dist[x][y] << " ";
		cout << endl;
	}*/
	
	
	if(dist[tx][ty] > inf/2) cout << -1 << endl;
	else cout << dist[tx][ty] << endl;
	
	return 0;
}