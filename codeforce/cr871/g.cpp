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
const int N = 1e6 + 2;

int n, m, q;
int x, y, k;
string s, t;

ll f[N];

ll s2(int x){
	return x*1ll*(x+1)/2*(2*x+1)/3;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);
    f[0]=0;
    f[1]=1;
    int t=1;
    for(int i=2;i<N;++i){
    	f[i]=f[i-1]+t;
    	t++;
    }
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        rd(n);
        // if(n==1){
        // 	wt(1,nl);continue;
        // }
        // if(n==2){
        // 	wt(5,nl);continue;
        // }
        //  if(n==3){
        // 	wt(10,nl);continue;
        // }
	    // auto get=[&](int x){
	    // 	int l=1,r=N-1,ans=-1;
	    // 	while(l<=r){
	    // 		int md=(l+r)/2;
	    // 		if(f[md]<x){
	    // 			ans=md;
	    // 			l=md+1;
	    // 		}else r=md-1;
	    // 	}
	    // 	return ans;
	    // };
	    auto cal=[&](int h, int l, int r) {
	    	if(r>h)r=h;
	    	int t=f[h]+l-1,p=f[h]+r-1;
	    	return s2(p)-s2(t-1);
	    };
	     ll s=0;
	     
	    int t=upper_bound(f,f+N-1,n)-f;
	    t--;

	    // dbg(t,nl);continue;
	    int l=n-f[t]+1,r=l;
	    for(int i=t;i>=1;--i){
	    	ll s2=cal(i,l,r);
	    	// if(cas==1)dbg(i,l,r,s2,s,nl);
	    	s+=s2;
	    	if(l>1)l--;
	    }
	    wt(s,nl);
    }

    return 0;
}
