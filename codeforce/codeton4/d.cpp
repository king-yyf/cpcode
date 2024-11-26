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
ll x, y, k;
string s, t;

ll get(ll x, ll y, ll h){
    if(h<=x) return 1ll;
    return 1ll+(h-y-1)/(x-y);
	// ll l=1,r=2e9,c=r;
	// while(l<=r){
	// 	ll md=(l+r)/2;
	// 	ll p=(md-1)*(x-y)+x;
	// 	if(p>=h){
    //         c=md;
	// 		r=md-1;
	// 	}else l=md+1;
	// }
	// return c;
}

ll cc(ll x, ll y, ll n){
	return x*1ll*n-(n-1)*1ll*y;
}

pair<ll,ll> cal(int x, int y, int n){
	if(n==1) return {1,x};
	long long mn=cc(x,y,n-1)+1,mx=cc(x,y,n);
	pair<long long, long long> p{mn,mx};
	return p;
}

void ac_yyf(int tt) {
    rd(q);
    int t;


    // if(tt==1){
    // 	// ll x1=get(4,1,7);
    // 	// ll x2=get(3,2,7);
    // 	// dbg("x1=",x1,"x2=",x2,'\n');
    // 	auto [m1,m2]=cal(4,2,2);
    // 	dbg("m1=",m1,"m2=",m2,'\n');
    // 	auto [m3,m4]=cal(2,1,3);
    // 	dbg("m3=",m3,"m4=",m4,'\n');

    // }

    auto pp=[&](ll x1, ll y1, ll x2, ll y2){
    	return max(0ll, min(y1,y2)-max(x1,x2)+1);
    };

    ll mn=-1,mx=-1;
    while(q--){
    	cin>>t;
    	if(t==1){
    		cin>>x>>y>>k;
    		auto [m1,m2]=cal(x,y,k);
    		if(mn==-1){
    			mn=m1,mx=m2;
    			cout<<1<<' ';
    		}else{
    			 if(pp(m1,m2,mn,mx)>0){
    			 	cout<<1<<' ';
    			 	mx=min(mx,m2);
    			 	mn=max(mn,m1);
    			 }else {
    			 	cout<<"0 ";
    			 }
    		}
    		// if(tt==4){
    		// 	dbg("mn=",mn,"mx=",mx,'\n');
    		// }
    	}else{
    		cin>>x>>y;
    		// if(tt==4){
    		// 	dbg("mn=",mn,"mx=",mx,'\n');
    		// }
    		if(mn==-1){
    			cout<<"-1 ";
    		}else{
    			ll p1=get(x,y,mn);
    			ll p2=get(x,y,mx);
                if(p1==p2){
    				cout<<p1<<' ';
                
    			}else {
    				cout<<-1<<' ';
    			}
    		}
    	}
    }
    cout<<"\n";
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
