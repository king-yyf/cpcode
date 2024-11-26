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
const int N = 2023;

int n, m, q;
int x, y, k;
string s, t;

ll inverse(ll a, ll m) { 
    a %= m; if (a == 0) return 0; if (a < 0) a += m;
    ll u = 0, v = 1;
    while (a) { ll t = m / a;  m -= t * a; swap(a, m); u -= t * v; swap(u, v); }
    return u;
}
template <int m, bool is_prime = true>
struct static_mod {
    using mint = static_mod;
    static constexpr int mod() { return m; }
    static_mod() : _v(0) {}
    template <class T> static_mod(T v) {ll x = (ll)(v % (ll)(umod())); if (x < 0) x += umod(); _v = (unsigned int)(x);}
    static_mod(unsigned int v) { _v = (unsigned int)(v % umod());}
    unsigned int val() const { return _v; }
    mint& operator++() { _v++; if (_v == umod()) _v = 0; return *this;}
    mint& operator--() { if (_v == 0) _v = umod(); _v--; return *this;}
    mint operator++(int) { mint result = *this; ++*this; return result;}
    mint operator--(int) { mint result = *this; --*this; return result;}
    mint& operator+=(const mint& rhs) { _v += rhs._v; if (_v >= umod()) _v -= umod();return *this;}
    mint& operator-=(const mint& rhs) { _v -= rhs._v; if (_v >= umod()) _v += umod();return *this;}
    mint& operator*=(const mint& rhs) { unsigned long long z = _v; z *= rhs._v; _v = (unsigned int)(z % umod()); return *this;}
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(ll n) const {mint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x;n >>= 1;} return r;}
    mint inv() const { if(is_prime) {assert(_v);return pow(umod() - 2);} return inverse(_v, m);}
    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs;}
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs;}
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs;}
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v;}
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v;}
    friend ostream& operator << (ostream& out, const mint& n) { return out << n.val(); }
    friend istream& operator >> (istream& in, mint& n) { ll x; in >> x; n = mint(x); return in; }
private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
};
using mint = static_mod<998244353>; // 1000000007

namespace tuple_ops {
    template <std::size_t N, typename F, typename ...Args>
    std::tuple<Args...>& update(std::tuple<Args...>& lhs, F&& fun) {
        if constexpr (N == std::tuple_size_v<std::tuple<Args...>>) return lhs;
        else return fun(std::get<N>(lhs)), update<N + 1>(lhs, std::forward<F>(fun));
    }
    template <std::size_t N, typename F, typename ...Args>
    std::tuple<Args...>& merge(std::tuple<Args...>& lhs, const std::tuple<Args...>& rhs, F&& fun) {
        if constexpr (N == std::tuple_size_v<std::tuple<Args...>>) return lhs;
        else return fun(std::get<N>(lhs), std::get<N>(rhs)), merge<N + 1>(lhs, rhs, std::forward<F>(fun));
    }
}
template <typename ...Args>
std::tuple<Args...>& operator+=(std::tuple<Args...>& t1, const std::tuple<Args...>& t2) {
    return tuple_ops::merge<0>(t1, t2, [](auto& x, const auto& y) { x += y; });
}
template <typename ...Args>
std::tuple<Args...>& operator-=(std::tuple<Args...>& t1, const std::tuple<Args...>& t2) {
    return tuple_ops::merge<0>(t1, t2, [](auto& x, const auto& y) { x -= y; });
}
template <typename ...Args>
std::tuple<Args...> operator+(std::tuple<Args...> t1, const std::tuple<Args...>& t2) { return std::move(t1 += t2); }
template <typename ...Args>
std::tuple<Args...> operator-(std::tuple<Args...> t1, const std::tuple<Args...>& t2) { return std::move(t1 -= t2); }

template <typename V, typename ...Args>
std::tuple<Args...>& operator+=(std::tuple<Args...>& t1, const V& v) { return tuple_ops::update<0>(t1, [&v](auto& x) { x += v; }); }
template <typename V, typename ...Args>
std::tuple<Args...>& operator-=(std::tuple<Args...>& t1, const V& v) { return tuple_ops::update<0>(t1, [&v](auto& x) { x -= v; }); }
template <typename V, typename ...Args>
std::tuple<Args...>& operator*=(std::tuple<Args...>& t1, const V& v) { return tuple_ops::update<0>(t1, [&v](auto& x) { x *= v; }); }
template <typename V, typename ...Args>
std::tuple<Args...>& operator/=(std::tuple<Args...>& t1, const V& v) { return tuple_ops::update<0>(t1, [&v](auto& x) { x /= v; }); }

template <typename V, typename ...Args>
std::tuple<Args...> operator*(const V& v, std::tuple<Args...> t1) { return std::move(t1 *= v); }
template <typename V, typename ...Args>
std::tuple<Args...> operator*(std::tuple<Args...> t1, const V& v) { return std::move(t1 *= v); }
template <typename V, typename ...Args>
std::tuple<Args...> operator/(std::tuple<Args...> t1, const V& v) { return std::move(t1 /= v); }

using T=tuple<int,int,int>;
map<T,mint> mp;

mint get(int n, int k, int s) {
	if(n==0) {
		if(k==0 && s==0) return 1;
		return 0;
	}
	if(n==1){
		if(k==1&&s==1) return 1;
		if(k==-1&&s==0) return 1;
		return 0;
	}
	if(n==2){
		if(k==0) {
			if(s==1) return 1;
			if(s==0)return 1;
			return 0;
		}
		if(k==2&&s==2) return 1;
		if(k==-2&&s==0) return 1;
		return 0;
	}
	mint ans=0;
	if(s==0){

	}else if(s==1){

	}else if(s==2){

	}else{

	}

	if(mp.count({n,k,s})) return mp[{n,k,s}];

	if(s==0){
		ans= get(n-1,k+1,0)+get(n-1,k+1,1)+get(n-1,k+1,2)+get(n-1,k+1,3);
	}else if(s==1){
		ans=get(n-1,k-1,0);
	}else if(s==2){
		ans=get(n-1,k-1,1);
	}else if(s==3){  // >=3
		ans=get(n-1,k-2,2)+get(n-1,k-2,3);
	}

	mp[{n,k,s}]=ans;
	return ans;
}

void ac_yyf(int tt) {
    rd(n,k);
  // mint ans=0;
    // f0(4)ans+=get(n,k,i);
    mint ans=0;
    ans=get(n,k,0)+get(n,k,1)+get(n,k,2)+get(n,k,3);
    wt(ans,nl);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    // get(2023,2023,0);
    // get(2023,2023,1);
    // get(2023,2023,2);
    // get(2023,2023,3);
    // map<pair<int,int>, int> m2;
    // for(int i=1;i<=N;++i){
    // 	for(int j=1;j<=N;++j){

    // 		if(i<3||j<3){
    // 			for(int k=0;k<4;++k){
    // 				dp[i][j][k]=get(i,j,k);
    // 			}
    // 		}else{
    // 			dp[i][j][0]=j+1<=N ? dp[i-1][j+1][0]+dp[i-1][j+1][1]+dp[i-1][j+1][2]+dp[i-1][j+1][3]:get(i-1,j+1,0)+get(i-1,j+1,1)+get(i-1,j+1,2)+get(i-1,j+1,3);
	//     		dp[i][j][1]=dp[i-1][j-1][0];
	//     		dp[i][j][2]=dp[i-1][j-1][1];
	//     		dp[i][j][3]=dp[i-1][j-2][2]+dp[i-1][j-2][3];
    // 		}
    // 	}
    // }
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
