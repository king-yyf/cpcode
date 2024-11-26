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

template <typename T>
struct PrefixSum2D {
    int n, m;
    vector<vector<T>> a;
    PrefixSum2D(int N, int M) : n(N), m(M), a(N + 1, vector<T>(M + 1, 0)){}
    PrefixSum2D(vector<vector<T>> &A) {
        n = A.size(), m = A[0].size();
        a.assign(n + 1, vector<T>(m + 1, 0));
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j)
                a[i + 1][j + 1] = a[i][j + 1] + a[i + 1][j] - a[i][j] + A[i][j];
    }
    T sum(int x1, int y1, int x2, int y2) { // sum[x1..x2, y1..y2]
        return a[x2 + 1][y2 + 1] - a[x2 + 1][y1] - a[x1][y2 + 1] + a[x1][y1];
    }
};



void ac_yyf(int tt) {
    rd(n,m,k);
    vector a(n,vector<ll>(m));
    ll s=0;
    int mx=0;
    f0(n){
    	rd(a[i]);
    	s+=Sm(a[i]);
    	cmx(mx,Mx(a[i]));
    }
    if(s<k+1){
    	wt("-1\n");return;
    }
    if(mx>=k+1){
    	wt("0\n");return;
    }
    PrefixSum2D<ll> f(a);
    int l=0,r=max(n,m),ans=r;
    while(l<=r){
    	int md=(l+r)/2;
    	bool o=0;
    	int x,y;
    	f0(n){
    		if(o)break;
    		f2(j,m){
    			if(!a[i][j])continue;
    			int x1=max(0,i-md),y1=max(0,j-md);
	    		int x2=min(i+md,n-1),y2=min(j+md,m-1);
	    		ll s1=f.sum(x1,y1,x2,y2);
	    		if(s1>=k+1){
	    			o=1;
	    			x=i,y=j;
	    			break;
	    		}
	    		// if(x2>=n-1&&y2>=m-1)break;
	    	}
    	}
    	// if(tt==1){
    	// 	if(o &&md==2){
    	// 		dbg("i=",x,"j=",y,nl);
    	// 	}
    	// }
    	if(o){
    		ans=md;r=md-1;
    	}else l=md+1;
    }
    wt(ans,nl);
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
