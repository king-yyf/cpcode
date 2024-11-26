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

const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};

int n, m, q;
int x, y, k;
string s, t;

void ac_yyf(int tt) {
	/*
    n=5,m=20;

    auto get=[&](int x,int y){
    	return x*100+y;
    };
    f1(n){
    	for(int j=1;j<=m;++j){
    		// dbg("i=",i,"j=",j);wt(nl);
    		vector<vector<int> > d(n+1,vector<int>(m+1,100000));
    		vector<vector<int> > vis(n+1,vector<int>(m+1));
    		queue<pair<int,int>> q;
    		int t=get(i,j);
    		q.push({t,0});
    		vis[i][j]=1;
    		while(sz(q)){
    			auto [f,p]=q.front();q.pop();

    			int x=f/100,y=f%100;
    			d[x][y]=p;
    			f0(8){
    				int nx=x+fx[i],ny=y+fy[i];
    				if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&!vis[nx][ny]){
    					q.push({get(nx,ny),p+1});
    					vis[nx][ny]=1;
    				}
    			}
    		}
    		// for(int k=1;k<=n;++k){
    		// 	for(int l=1;l<=m;++l){
    		// 		cout<<d[k][l]<<' ';
    		// 	}cout<<nl;
    		// }
    		// cout<<nl;

    		int p=d[1][1];
    		int x=-1,y=-1;
    		if(p+1<=n) y=d[p+1][1];
    		if(p+1<=m) x=d[1][p+1];

    		if(x==-1)x=p;
    		if(y==-1)y=p;
    		x++,y++;
    		// dbg("i=",i,"j=",j,"x=",x,"y=",y);wt(nl);
    		
    		bool o=(x==i&&y==j);
    		dbg("o=",o,nl);
    	}
    }
    */
    cin>>n>>m;
    cout<<"? "<<1<<" "<<1<<endl;
    int p;
    int x=-1,y=-1;
    cin>>p;
    if(p+1<=n){
    	cout<<"? "<<p+1<<" "<<1<<endl;
    	cin>>y;
    }
    if(p+1<=m){
    	cout<<"? "<<1<<" "<<p+1<<endl;
    	cin>>x;
    }
    if(x==-1)x=p;
    if(y==-1)y=p;
    x++,y++;
    cout<<"! "<<x<<" "<<y<<endl;
}

int main() {
    // ios::sync_with_stdio(false); cin.tie(nullptr);
    // cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
