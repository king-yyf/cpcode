#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9+7;
using ll=long long ;

using ull = unsigned long long;
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

int maximumPossible(int n,int k,string s){
	vector<int> cnt(26);
	for(auto&x:s){
		cnt[x-'a']++;
	}

	while(k){
		int mx=cnt[0],mn=cnt[0],x=0,y=0;
		for(int i=0;i<26;++i){
			if(cnt[i]>mx){
				mx=cnt[i],x=i;
			}
			if(cnt[i]<mn){
				mn=cnt[i],y=i;
			}
		}
		if(mx-mn<=1){
			break;
		}

		cnt[x]-=1;
		cnt[y]+=1;
		k--;
	}

	vector<mint> f(n+1);

	f[1]=1;
	for(int i=2;i<=n;++i){
		f[i]=f[i-1]*i;
	}
	mint ans=1;
	for (int i = 0; i < 26; ++i) {
		if (cnt[i] == 0) continue;
		ans=ans*f[cnt[i]];
	}
	ans=f[n]/ans;
	return ans;
}


int main() {
	string s="tkvzoncjulufgfrowfscpjglolfrosvkpnfrmtwhwjoqwkpavvsjgufpkrpzyullotjg";
	cout<<maximumPossible(68,94,s);
    return 0;
}
