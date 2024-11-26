#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst ? (r=md-1):(l=md+1);} else fst ? (l=md+1):(r=md-1);}
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
template<class A> void dbg(A x) { cout<<x<<' ';}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 1e6 + 3;

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
using mint = static_mod<1000000007>; // 1000000007

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
    mint invfac(int n) {if(n < 0) return 0; reserve(n + 1); return inv[n]; }
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
} comb;

mint D[N];
void ac_yyf(int tt) {
    rd(n);
    f0(n+1){
    	mint c=comb.C(n,i)*D[n-i]/comb.fact(n);
    	wt(c,' ');
    }
    wt(nl);
}

int main() {
    int T = 1;
    cin >> T;
    D[0]=1;

    f1(3)D[i]=i-1;
    mint x = 1, y = 2, ans;
    for (int i = 4; i < N - 1; ++i) {
        ans = (i - 1) * (x + y);
        D[i]=ans;
        x = y, y = ans;
    }

    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
