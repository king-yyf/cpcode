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
const int N = 3000 + 5;

int n, m, q;
int x, y, k;
string s, t;

int d[N][N];

void ac_yyf(int tt) {
	rd(n);
    vector<array<int,2 >>a(n); 
    f0(n){
    	rd(a[i][0],a[i][1]);
    }
    sort(all(a),[&](auto &x, auto &y){
    	if(x[0]!=y[0]) return x[1]<y[1];
    	return x[0]<y[0];
    });
    const int inf=1e9;
    ll ans=0;
    auto get=[&](int i ,int j){
    	int x1=a[i][0],y1=a[i][1];
    	int x2=a[j][0],y2=a[j][1];
    	pair<int,int> p;
    	if(x1==x2) p={inf,0};
    	else if(y1==y2) p={0,inf};
    	else {
    		int x=x1-x2,y=y1-y2;
    		bool d=0;
    		if(x*y<0)d=1;
    		if(x<0)x=-x;
    		if(y<0)y=-y;
    		if(d)p={-x,y};
    		else p={x,y};
    	}
    	return p;
    };
    f0(n){
    	for(int j=i+1;j<n;++j){
    		d[i][j]=d[i][j]=(a[i][0]-a[j][0])*(a[i][0]-a[j][0])+(a[i][1]-a[j][1])*(a[i][1]-a[j][1]);


    	}
    }


    f0(n){
    	map<int,int>mp;
    	f2(j,n)mp[d[i][j]]++;
    	for(auto&[k,v]:mp){
    		if(v>=2) ans+=v*(v-1)/2;
    	}
    }
    wt(ans/2);


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
