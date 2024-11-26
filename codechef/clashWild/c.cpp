#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define yn(cond) cout << ((cond) ? "Yes" : "No") << "\n";
#define YN(cond) cout << ((cond) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
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
const double PI = acos(-1.0);
const int N = 2e5 + 5;

const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 

void ac_yyf(int tt) {
    int m,n,r,c;
    rd(n,r,c);
    vector<vector<int>> g(r,vector<int>(c));
    f0(r){
    	f2(j,c)cin>>g[i][j];
    }
    rd(m);
    set<int> s;
    f0(m){
    	int x;cin>>x;s.insert(x);
    }
    map<int,int>mp;

    vector<vector<int>> vis(r,vector<int> (c));

    function<void(int, int)> dfs = [&](int x, int y) {
    	vis[x][y]=1;
    	f0(4){
    		int nx=x+dx[i],ny=y+dy[i];
    		if(nx>=0&&nx<r&&ny>=0&&ny<c&&g[nx][ny]==g[x][y]&&!vis[nx][ny]){
    			dfs(nx,ny);
    		}
    	}
    };
    f0(r){
    	f2(j,c){
    		if(!vis[i][j]){
    			mp[g[i][j]]++;
    			dfs(i,j);
    		}
    	}
    }
    const int inf =(int)1e9;
    int mn=inf;
    for(auto&[k,v]:mp){
    	if(s.count(k))
    	cmn(mn,v);
    }
    if(mn==inf)mn=-1;
    wt(mn,'\n');
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