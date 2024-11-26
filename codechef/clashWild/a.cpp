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

void ac_yyf(int tt) {
	ll n,x,y;
    rd(n,x,y);
    long long ans=0;
    if(n%2==0){
    	auto get=[&](long long t){
    		long long l,r;
    		if (t <=n/2){
    			l=n/2-t+1,r=n-(n/2-t);
    		}else{
    			l=1+t-n/2,r=n-(t-n/2);
    		}
    		pair<long long, long long> p{l,r};
    		return p;
    	};
    	if(x>n-1){
    		wt("-1\n");return;
    	}
    	auto [l,r]=get(x);
    	if(y>r-l+1){
    		wt("-1\n");return;
    	}
    	y=l+y-1;
    	long long lo=x,hi=1,c=x;
    	while(lo>=hi){
    		long long md=(lo+hi)/2;
    		long long x1=md,y1=x+y-md;
    		auto [l1,r1]=get(md);
    		if(r1>=y1){
    			c=md;
    			lo=md-1;
    		}else hi=md+1;
    	}
    	ans+=x-c+1;
    	// dbg("ans=",ans);
    	lo=x,hi=1,c=x;
    	while(lo>=hi){
    		long long md=(lo+hi)/2;
    		long long x1=md,y1=y-(x-md);
    		auto [l1,r1]=get(md);
    		// dbg("lo=",lo,"hi=",hi,"md=",md,l1,r1,'\n');
    		if(l1<=y1){
    			c=md;
    			lo=md-1;
    		}else hi=md+1;
    	}
    	ans+=x-c+1;
    	// dbg("ans=",ans);
    	lo=x,hi=n-1,c=x;
    	while(lo<=hi){
    		long long md=(lo+hi)/2;
    		long long x1=md,y1=y+(md-x);
    		auto [l1,r1]=get(md);
    		if(r1>=y1){
    			c=md;
    			lo=md+1;
    		}else hi=md-1;
    	}
    	ans+=c-x+1;
    	// dbg("ans=",ans);
    	lo=x,hi=n-1,c=x;
    	while(lo<=hi){
    		long long md=(lo+hi)/2;
    		long long x1=md,y1=y-(md-x);
    		auto [l1,r1]=get(md);
    		if(l1<=y1){
    			c=md;
    			lo=md+1;
    		}else hi=md-1;
    	}
    	ans+=c-x+1;
    	// dbg("ans=",ans);
    }else{
    	auto get=[&](long long t){
    		long long l,r;
    		long long c=(n+1)/2;
    		if (t <=c){
    			l=c-t+1,r=n-(c-t);
    		}else{
    			l=1+t-c,r=n-(t-c);
    		}
    		pair<long long, long long> p{l,r};
    		return p;
    	};
    	if(x>n){
    		wt("-1\n");return;
    	}
    	auto [l,r]=get(x);
    	if(y>r-l+1){
    		wt("-1\n");return;
    	}
    	y=l+y-1;
    	long long lo=x,hi=1,c=x;
    	while(lo>=hi){
    		long long md=(lo+hi)/2;
    		long long x1=md,y1=x+y-md;
    		auto [l1,r1]=get(md);
    		if(r1>=y1){
    			c=md;
    			lo=md-1;
    		}else hi=md+1;
    	}
    	ans+=x-c+1;
    	// dbg("ans=",ans);
    	// lo=x,hi=1,c=x;
    	// while(lo<=hi){
    	// 	long long md=(lo+hi)/2;
    	// 	long long x1=md,y1=x+y-md;
    	// 	auto [l1,r1]=get(md);
    	// 	if(l1<=x1){
    	// 		c=md;
    	// 		lo=md-1;
    	// 	}else hi=md+1;
    	// }
    	// ans+=c-x+1;
    	lo=x,hi=1,c=x;
    	while(lo>=hi){
    		long long md=(lo+hi)/2;
    		long long x1=md,y1=y-(x-md);
    		auto [l1,r1]=get(md);
    		if(l1<=y1){
    			c=md;
    			lo=md-1;
    		}else hi=md+1;
    	}
    	ans+=x-c+1;
    	// dbg("ans=",ans);
    	lo=x,hi=n,c=x;
    	while(lo<=hi){
    		long long md=(lo+hi)/2;
    		long long x1=md,y1=y+(md-x);
    		auto [l1,r1]=get(md);
    		if(r1>=y1){
    			c=md;
    			lo=md+1;
    		}else hi=md-1;
    	}
    	ans+=c-x+1;
    	// dbg("ans=",ans);
    	lo=x,hi=n,c=x;
    	while(lo<=hi){
    		long long md=(lo+hi)/2;
    		long long x1=md,y1=y-(md-x);
    		auto [l1,r1]=get(md);
    		if(l1<=y1){
    			c=md;
    			lo=md+1;
    		}else hi=md-1;
    	}
    	ans+=c-x+1;
    	// dbg("ans=",ans);
    }
    wt(ans-3,'\n');
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
