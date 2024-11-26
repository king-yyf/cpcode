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

using ull = unsigned long long;
constexpr pair<ll, ll> inv_gcd(ll a, ll b) { 
    a %= b; if (a == 0) return {b, 0}; if (a < 0) a += b;
    ll s = b, u = 0, v = 1;
    while (a) { ll t = s / a; s -= a * t, u -= v * t; swap(s, a); swap(u, v);}
    if (u < 0) u += b / s;
    return {s, u};
}
struct barrett {
    unsigned int _m;
    ull im;
    explicit barrett(unsigned int m) : _m(m), im((ull)(-1) / m + 1) {} // 1 <= m < 2^31
    unsigned int umod() const { return _m; }
    unsigned int mul(unsigned int a, unsigned int b) const { // 0 <= a, b < m, return a * b % m
        ull z = a; z *= b;
        ull x = (ull)(((unsigned __int128)(z)*im) >> 64);
        unsigned int v = (unsigned int)(z - x * _m);
        if (_m <= v) v += _m;
        return v;
    }
};
template <int id> struct dynamic_mod {
    using mint = dynamic_mod;
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) { assert(1 <= m); bt = barrett(m);}
    static mint raw(int v) { mint x; x._v = v; return x;}
    dynamic_mod() : _v(0) {}
    template <class T>
    dynamic_mod(T v) { ll x = (ll)(v % (ll)(mod())); if (x < 0) x += mod(); _v = (unsigned int)(x);}
    dynamic_mod(unsigned int v) { _v = (unsigned int)(v % mod());}
    unsigned int val() const { return _v; }
    mint& operator++() { _v++; if (_v == umod()) _v = 0; return *this;}
    mint& operator--() { if (_v == 0) _v = umod(); _v--; return *this;}
    mint operator++(int) { mint result = *this; ++*this; return result;}
    mint operator--(int) { mint result = *this; --*this; return result;}
    mint& operator+=(const mint& rhs) { _v += rhs._v; if (_v >= umod()) _v -= umod(); return *this;}
    mint& operator-=(const mint& rhs) { _v += mod() - rhs._v; if (_v >= umod()) _v -= umod(); return *this;}
    mint& operator*=(const mint& rhs) { _v = bt.mul(_v, rhs._v); return *this;}
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }
    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }
    mint pow(ll n) const { assert(0 <= n); mint x = *this, r = 1; while (n) { if (n & 1) r *= x; x *= x; n >>= 1;}return r;}
    mint inv() const { return inv_gcd(_v, mod()).second; }
    friend mint operator+(const mint& lhs, const mint& rhs) { return mint(lhs) += rhs;}
    friend mint operator-(const mint& lhs, const mint& rhs) { return mint(lhs) -= rhs;}
    friend mint operator*(const mint& lhs, const mint& rhs) { return mint(lhs) *= rhs;}
    friend mint operator/(const mint& lhs, const mint& rhs) { return mint(lhs) /= rhs;}
    friend bool operator==(const mint& lhs, const mint& rhs) { return lhs._v == rhs._v;}
    friend bool operator!=(const mint& lhs, const mint& rhs) { return lhs._v != rhs._v;}
private:
    unsigned int _v;
    static barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id> barrett dynamic_mod<id>::bt(998244353);
using mint = dynamic_mod<-1>;

struct Comb {
    vector<mint> fac, inv;
    vector<vector<mint>> s1, s2;
    Comb() : fac(1, 1), inv(1, 1){}
    void reserve(int a){
        if(fac.size() >= a) return;
        if(a < fac.size() * 2) a = fac.size() * 2;
        while(fac.size() < a) fac.push_back(fac.back() * mint(fac.size()));
        inv.resize(fac.size());
        inv.back() = fac.back().inv();
        for(int i = inv.size() - 1; inv[i - 1] == 0; i--) inv[i - 1] = inv[i] * i;
    }
    mint fact(int n){ if(n < 0) return 0; reserve(n + 1); return fac[n]; }
    mint P(int n, int r){ // 排列数
        if(r < 0 || n < r) return 0;
        if(n >> 24){ mint ans = 1; for(int i = 0; i < r; i++) ans *= n--; return ans; }
        reserve(n + 1); return fac[n] * inv[n - r];
    }
    mint Q(int n) {reserve(n); return fac[n - 1];} // n个元素的圆排列数
    mint C(int n, int m) { // 组合数
        if (n < m || m < 0) return 0;
        reserve(n + 1);
        return fac[n] * inv[m] * inv[n - m];
    }
    mint MC(int n, int m) { // r个相同物品放到n个篮子方案数
        return C(n + m - 1, n - 1);
    }
    mint catalan(int n) {
        reserve(n * 2 + 1); return fac[n * 2] * inv[n] * inv[n + 1];
    }
    mint CQ(int n, int m) {  // n个元素中选m个元素围成一圈的圆排列数。
        return C(n, m) * Q(m);
    }
    mint D(int n) { // 1-n的排列p的错位排列数  D[n]=(n-1)*(D[n-1]+D[n-2])
        if (n <= 3) return mint(n - 1);
        mint x = 1, y = 2, ans;
        for (int i = 4; i <= n; ++i) {
            ans = (i - 1) * (x + y);
            x = y, y = ans;
        }
        return ans;
    }
    mint stl1(int n, int m) { //n个不同元素，划分为m个非空圆排列的方案数(第一类斯特林数)
        if (s1.size() == 0) {
            int N = 10, M = 5;  // 根据题目数据范围调整
            s1.assign(N, vector<mint>(M));
            s1[0][0] = 1;
            for (int i = 1; i < N; ++i) for (int j = 1; j < M; ++j) {
                s1[i][j] = s1[i - 1][j - 1] + (i - 1) * s1[i - 1][j];
            }
        }
        return s1[n][m];
    }
    mint stl2(int n, int m) {// n个不同元素，划分为m个非空子集的方案数(第二类斯特林数)
        if (s2.size() == 0) {
            int N = 10, M = 5;  // 根据题目数据范围调整
            s2.assign(N, vector<mint>(M));
            s2[0][0] = 1;
            for (int i = 1; i < N; ++i) for (int j = 1; j < M; ++j) {
                s2[i][j] = s2[i - 1][j - 1] + j * s2[i - 1][j];
            }
        }
        return s2[n][m];
    }
    mint lucas(long long a, long long b, int p) { // 大组合数，p为质数
        if (a < p && b < p) return C(a, b);
        return C(a % p, b % p) * lucas(a / p, b / p, p);
    }
} comb;

void ac_yyf(int tt) {
    long long n,m;
    int p;
    rd(n,m,p);
    mint::set_mod(p);
    Comb c;
    mint ans=c.lucas(n+m,n,p);
    cout<<ans.val()<<"\n";
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
