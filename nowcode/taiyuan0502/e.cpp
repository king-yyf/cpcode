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
    rd(n,k,s);
    int l=n,r=0;
    f0(n){
    	if(s[i]=='1'){
    		l=i;break;
    	}
    }
    for(int i=n-1;i>=0;--i){
    	if(s[i]=='1'){
    		r=i;break;
    	}
    }
    if(l<r){
    	if(r-l+1>k){
    		wt("delicious");return;
    	}
    	for(int i=l;i<r;++i){
    		if(s[i]=='0'){
    			wt("delicious");return;
    		}
    	}
    }
    int ans=0;

    if(l<=r){
    	string t="";
    	bool o=0;
    	f0(n){
    		if(s[i]=='1'||s[i]=='?'){
    			if(s[i]=='1')o=1;
    			t+=s[i];
    		}else{
    			if(o)break;
    			t="";
    		}
	    }

	    n=sz(t);
	    f0(n){
	    	if(t[i]=='1') {
	    		l=i;break;
	    	}
	    }
	    for(int i=n-1;i>=0;--i){
	    	if(t[i]=='1'){
	    		r=i;break;
	    	}
	    }
	    // dbg(t,nl);
	    for(int i=0;i <= l&&i+k<=n;++i){
	    	if(i+k-1>=r){
	    		// dbg(i,t.substr(i,k),nl);
	    		ans++;
	    	}
	    }

    }else{
	    string t="";
	    f0(n){
	    	if(s[i]=='?'){
	    		t+=s[i];
	    	}else{
	    		if(sz(t)>=k){
	    			ans+=sz(t)-k+1;
	    		}
	    		t="";
	    	}
	    }
	    if(sz(t)>=k){
	    	ans+=sz(t)-k+1;
		}
    }
    if(ans==0){
    	wt("delicious");return;
    }
    wt(ans);
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
