#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

int bct(long long x){return __builtin_popcountll(x);}
int lg2(int x){return x==0?0:31-__builtin_clz(x);} //x>=0, floor(log2(x)) 
long long fbs(function<bool(long long)> f, long long& lb, long long rb) {  // first true binary search
    while(lb<rb) {
		long long mb=(lb+rb)/2;
		f(mb)?rb=mb:lb=mb+1; 
	} 
	return lb;
}
long long lbs(function<bool(long long)> f, long long& lb, long long rb) {  // last true binary search
	while(lb<rb) {
		long long mb=(lb+rb+1)/2;
		f(mb)?lb=mb:rb=mb-1; 
	} 
	return lb;
}

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) { cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    bool f=1;
	each(a, x) if(f==1) {wt(a); f=0;} else {cout<<' ';wt(a);}
}
const int mod = 998244353; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n,m,x,y,k;
int a[N],b[N];


using ll = long long;
using ull = unsigned long long;
// constexpr unsigned mod = 1000000007;
struct mint{
    unsigned num = 0;
    constexpr mint() noexcept {}
    constexpr mint(const mint &x) noexcept : num(x.num){}
    inline constexpr operator ll() const noexcept { return num; }
    inline constexpr mint& operator+=(mint x) noexcept { num += x.num; if(num >= mod) num -= mod; return *this; }
    inline constexpr mint& operator++() noexcept { if(num == mod - 1) num = 0; else num++; return *this; }
    inline constexpr mint operator++(int) noexcept { mint ans(*this); operator++(); return ans; }
    inline constexpr mint operator-() const noexcept { return mint(0) -= *this; }
    inline constexpr mint operator-(mint x) const noexcept { return mint(*this) -= x; }
    inline constexpr mint& operator-=(mint x) noexcept { if(num < x.num) num += mod; num -= x.num; return *this; }
    inline constexpr mint& operator--() noexcept { if(num == 0) num = mod - 1; else num--; return *this; }
    inline constexpr mint operator--(int) noexcept { mint ans(*this); operator--(); return ans; }
    inline constexpr mint& operator*=(mint x) noexcept { num = ull(num) * x.num % mod; return *this; }
    inline constexpr mint& operator/=(mint x) noexcept { return operator*=(x.inv()); }
    template<class T> constexpr mint(T x) noexcept {
        using U = typename conditional<sizeof(T) >= 4, T, int>::type;
        U y = x; y %= U(mod); if(y < 0) y += mod; num = unsigned(y);
    }
    template<class T> inline constexpr mint operator+(T x) const noexcept { return mint(*this) += x; }
    template<class T> inline constexpr mint& operator+=(T x) noexcept { return operator+=(mint(x)); }
    template<class T> inline constexpr mint operator-(T x) const noexcept { return mint(*this) -= x; }
    template<class T> inline constexpr mint& operator-=(T x) noexcept { return operator-=(mint(x)); }
    template<class T> inline constexpr mint operator*(T x) const noexcept { return mint(*this) *= x; }
    template<class T> inline constexpr mint& operator*=(T x) noexcept { return operator*=(mint(x)); }
    template<class T> inline constexpr mint operator/(T x) const noexcept { return mint(*this) /= x; }
    template<class T> inline constexpr mint& operator/=(T x) noexcept { return operator/=(mint(x)); }
    inline constexpr mint inv() const noexcept { ll x = 0, y = 0; extgcd(num, mod, x, y); return x; }
    static inline constexpr ll extgcd(ll a, ll b, ll &x, ll &y) noexcept { ll g = a; x = 1; y = 0; if(b){ g = extgcd(b, a % b, y, x); y -= a / b * x; } return g; }
    inline constexpr mint pow(ull x) const noexcept { mint ans = 1, cnt = *this; while(x){ if(x & 1) ans *= cnt; cnt *= cnt; x /= 2; } return ans; }
};
std::istream& operator>>(std::istream& is, mint& x) noexcept { ll a; cin >> a; x = a; return is; }
inline constexpr mint operator""_M(ull x) noexcept { return mint(x); }
std::vector<mint> fac(1, 1), inv(1, 1);
inline void reserve(ll a){
    if(fac.size() >= a) return;
    if(a < fac.size() * 2) a = fac.size() * 2;
    if(a >= mod) a = mod;
    while(fac.size() < a) fac.push_back(fac.back() * mint(fac.size()));
    inv.resize(fac.size());
    inv.back() = fac.back().inv();
    for(ll i = inv.size() - 1; !inv[i - 1]; i--) inv[i - 1] = inv[i] * i;
}
inline mint fact(ll n){ if(n < 0) return 0; reserve(n + 1); return fac[n]; }
inline mint perm(ll n, ll r){
    if(r < 0 || n < r) return 0;
    if(n >> 24){ mint ans = 1; for(ll i = 0; i < r; i++) ans *= n--; return ans; }
    reserve(n + 1); return fac[n] * inv[n - r];
}
inline mint comb(ll n, ll r){ if(r < 0 || n < r) return 0; reserve(r + 1); return perm(n, r) * inv[r]; }
inline mint Mcomb(ll n, ll r){ return comb(n + r - 1, n - 1); } // r个相同物品放到n个篮子方案数
inline mint catalan(ll n){ reserve(n * 2 + 1); return fac[n * 2] * inv[n] * inv[n + 1]; }


void solve(){
	cin>>n;
	f1(n)cin>>a[i];
	f1(n)cin>>b[i];
	int c=0,d=0;
	set<pair<int,int> > s;
	vector<int> v;
	f1(n){
		if(a[i]==b[i])c++;
		else {
			x=min(a[i],b[i]),y=max(a[i],b[i]);
			if(s.count({x,y})) d++;
			else v.push_back(i);
			s.insert({x,y});
		}		
	}

	int m=v.size();
	// set<int> st;
	k=n-c-2*d,x=(k+1)/2;
	// int mx=m;
	// for(int i=0;i<m;++i){
	// 	st.insert(a[v[i]]);
	// 	st.insert(b[v[i]]);
	// 	if(st.size()==k) {
	// 		mx=i+1;
	// 		break;
	// 	}
	// }
	
	// cout<<k<<", "<<c<<", "<< d<< "\n";
	long long ans=0;
	for(int i=x;i<=k;++i){
		
		long long p=comb(k,i);
		// cout<<"i="<<i<<", "<<k<<", "<< x<<", "<<p<<'\n';
		if(k-x<2)
			ans=(ans+comb(k,i))%mod;
		else{
			ans=(ans+comb(k,i)-k*comb(k-2,k-i-2))%mod;
		}
	}
	if(ans==0) ans=1;
	for(int i=0;i<d;++i){
		ans=(ans*3ll)%mod;
	}
	ans=(ans+mod)%mod;
	wt(ans,'\n');
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	solve();
	return 0;
}
