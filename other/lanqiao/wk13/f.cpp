#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define ar(x) array<int,x> 
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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> T f_div(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0));}
template <class T> T c_div(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0));}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
#ifdef sigma-yyf
#define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    cerr << s << ": " << h, ((cerr << ", " << t), ..., (cerr << "\n"));
}
#else
#define dbg(...) void(0)
#endif
template<class Fun> class Y_comb {
    Fun _f;
public:
    template<class T> explicit Y_comb(T &&fun): _f(forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...As) {return _f(ref(*this), forward<Args>(As)...);}
};
template<class Fun> decltype(auto) y_comb(Fun &&fun) { return Y_comb<decay_t<Fun>>(forward<Fun>(fun));}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;
constexpr char nl = '\n';
constexpr int inf = 1'061'109'567;
constexpr ll infll = 2'000'000'000'000'000'000;
constexpr int N = 2e5 + 5;
int n, m, q;
int x, y, k;
string s, t;



void solve(int tt) {
    rd(n,q);
    vector<int> a(n);
    rd(a);
    sort(all(a));
    vector<long long> s;
    psum(s,a);
    
    f0(q){
    	rd(k,m);
    	if(k>=a[n-1]) {
    		wt(s[m],nl);
    		continue;
    	}
    	if(a[0]>=k) {
    		ll x1=m*1ll*k;
    		ll x2=s[n]-s[n-m]-x1;
    		wt(x1-x2,nl);
    		continue;
    	}
    	ll x1=0,x2=0;
    	auto p=rb(a,k);
    	// a[p]>k

    	// 最小m个数
    	int l=-1e9,r=k,mn=r;

    	while(l<=r) {
    		int md=(l+r)/2;
    		int p1=0;
    		if(a[0]<=md) {
    			p1=rb(a,md);
    		}
    		int p2=0;
    		if(2*k-a[n-1]<=md) {
    			int l1=p,r1=n-1,c1=r1;
    			while(l1<=r1){
    				int m1=(l1+r1)/2;
    				if(2*k-a[m1]<=md){
    					c1=m1;
    					r1=m1-1;
    				}else l1=m1+1;
    			}
    			p2=n-c1;
    		}
    		// dbg(md,p1,p2,m);
    		if(p1+p2>=m){
    			mn=md;
    			r=md-1;
    		}else l=md+1;
    		
    	}
    	int p1=0;
    	if(a[0]<=mn) {
    		p1=rb(a,mn-1);
    		p1=min(m,p1);
    		x1=s[p1];
    	}
    	int cntt=p1;
    	if(2*k-a[n-1]<=mn&&p1<m) {
    		int l1=p,r1=n-1,c1=r1;
			while(l1<=r1){
				int m1=(l1+r1)/2;
				if(2*k-a[m1]<=mn-1){
					c1=m1;
					r1=m1-1;
				}else l1=m1+1;
			}
			int cnt2=n-c1;
			cntt+=cnt2;
			// c1=n-c1;
			x1+=k*1ll*(cnt2);
			// dbg(c1,p1,m,)
			x2=s[n]-s[c1]-k*1ll*cnt2;
			// dbg(c1,cnt2,k,cntt,m);
    	}
    	// dbg(p1,mn,x1,x2);
    	x1-=x2;
    	if(cntt<m)x1+=mn*1ll*(m-cntt);
    	wt(x1,nl);
    }
}
bool boolf(int tt) {
    return 0;
}

int main() {
    int T = 1, fun_type = 0;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        if (fun_type == 0) solve(cas);
        else if (fun_type == 1) cout << (boolf(cas) ? "Yes" : "No") << '\n';
        else cout << (boolf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}