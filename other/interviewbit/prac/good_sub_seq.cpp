#include <bits/stdc++.h>
using namespace std;

// https://www.interviewbit.com/problems/count-good-subsequences/

using ll = long long;
const int mod = 1e9 + 7;
struct mint{
    int v = 0;
    constexpr mint()  {}
    constexpr mint(const mint &x) : v(x.v){}
    inline constexpr operator int() const { return v; }
    inline constexpr mint& operator+=(mint x) { v += x.v; if(v >= mod) v -= mod; return *this; }
    inline constexpr mint& operator++() { if(v == mod - 1) v = 0; else v++; return *this; }
    inline constexpr mint operator++(int) { mint ans(*this); operator++(); return ans; }
    inline constexpr mint operator-() const { return mint(0) -= *this; }
    inline constexpr mint operator-(mint x) const { return mint(*this) -= x; }
    inline constexpr mint& operator-=(mint x) { if(v < x.v) v += mod; v -= x.v; return *this; }
    inline constexpr mint& operator--() { if(v == 0) v = mod - 1; else v--; return *this; }
    inline constexpr mint operator--(int) { mint ans(*this); operator--(); return ans; }
    inline constexpr mint& operator*=(mint x) { v = ll(v) * x.v % mod; return *this; }
    inline constexpr mint& operator/=(mint x) { return operator*=(x.inv()); }
    template<class T> constexpr mint(T x)  {
        using U = typename conditional<sizeof(T) >= 4, T, int>::type;
        U y = x; y %= U(mod); if(y < 0) y += mod; v = int(y);
    }
    template<class T> inline constexpr mint operator+(T x) const { return mint(*this) += x; }
    template<class T> inline constexpr mint& operator+=(T x) { return operator+=(mint(x)); }
    template<class T> inline constexpr mint operator-(T x) const { return mint(*this) -= x; }
    template<class T> inline constexpr mint& operator-=(T x)  { return operator-=(mint(x)); }
    template<class T> inline constexpr mint operator*(T x) const { return mint(*this) *= x; }
    template<class T> inline constexpr mint& operator*=(T x)  { return operator*=(mint(x)); }
    template<class T> inline constexpr mint operator/(T x) const { return mint(*this) /= x; }
    template<class T> inline constexpr mint& operator/=(T x) { return operator/=(mint(x)); }
    inline constexpr mint inv() const  { ll x = 0, y = 0; exgcd(v, mod, x, y); return x; }
    static inline constexpr ll exgcd(ll a, ll b, ll &x, ll &y) { ll g = a; x = 1; y = 0; if(b){ g = exgcd(b, a % b, y, x); y -= a / b * x; } return g; }
    inline constexpr mint pow(ll x) const { mint ans = 1, cnt = *this; while(x){ if(x & 1) ans *= cnt; cnt *= cnt; x /= 2; } return ans; }
    friend ostream& operator << (ostream& out, const mint& n) { return out << int(n); }
    friend istream& operator >> (istream& in, mint& n) { ll x; in >> x; n = mint(x); return in; }
};
vector<mint> fac(1, 1), inv(1, 1);
void reserve(int a){
    if(fac.size() >= a) return;
    if(a < fac.size() * 2) a = fac.size() * 2;
    if(a >= mod) a = mod;
    while(fac.size() < a) fac.push_back(fac.back() * mint(fac.size()));
    inv.resize(fac.size());
    inv.back() = fac.back().inv();
    for(int i = inv.size() - 1; !inv[i - 1]; i--) inv[i - 1] = inv[i] * i;
}
mint fact(int n){ if(n < 0) return 0; reserve(n + 1); return fac[n]; }
mint perm(int n, int r){
    if(r < 0 || n < r) return 0;
    if(n >> 24){ mint ans = 1; for(int i = 0; i < r; i++) ans *= n--; return ans; }
    reserve(n + 1); return fac[n] * inv[n - r];
}
mint comb(int n, int r){ if(r < 0 || n < r) return 0; reserve(r + 1); return perm(n, r) * inv[r]; }
mint Mcomb(int n, int r){ return comb(n + r - 1, n - 1); } // r个相同物品放到n个篮子方案数
mint catalan(int n){ reserve(n * 2 + 1); return fac[n * 2] * inv[n] * inv[n + 1]; }


int solve(vector<int> &a) {
	map<int,int>mp;
	for(int x:a)
		mp[x]++;
	vector<int> v;
	for(auto&[k,freq]:mp) 
		v.push_back(freq);
	sort(v.begin(), v.end());
	mint ans=0;
	for(int i=1;i<=v.back();i++){
        mint res = 1;
        for(auto it=lower_bound(v.begin(),v.end(),i); it != v.end(); it++)
        	res = res * (1 + comb(*it, i));
        ans = ans + res - 1;
    }
    return ans;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    vector<int> a{2,4,3,3,2,4};
    int n=a.size();
    for(int i=1;i<1<<n;++i){
    	for(int j=0;j<n;++j){
    		if((i>>j)&1)cout<<a[j]<<" ";
    	}
    	cout<<"\n";
    }
    cout<<solve(a)<<"\n";

    return 0;
}
