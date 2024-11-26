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

int n, m, q;
int x, y, k;
string s, t;

vector<pair<int,int>> getDivisors(ll x) {
    vector<pair<int,int>> res;
    for (int i = 2; i * 1ll * i <= x; ++i) {
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) 
                x /= i, s++;
            res.emplace_back(i,s);
        }
    }
    if (x > 1) res.emplace_back(x,1);
    return res;
}

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


void ac_yyf(int tt) {
    // set<int> s;
    // f0(n){

    // }
    // ll x=7109;
    // // auto a=getDivisors(x);
    // // for(auto&[f,s]:a){
    // //     cout<<f<<", "<<s<<"\n";
    // // }
    // for(int i=1;i<=100;++i){
    //     x+=998244353;
    //     if(x%13==0)
    //         cout<<i<<", " << x<<"\n";
    // }
    long long s=0;
    for(int i=0;i<10;++i){
        long long x=comb(10,i);
        s+=x;
        cout<<x<<", "<<s<<"\n";
    }
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
