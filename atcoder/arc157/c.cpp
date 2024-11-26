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

constexpr pair<ll, ll> inv_gcd(ll a, ll b) { 
    a %= b; if (a == 0) return {b, 0}; if (a < 0) a += b;
    ll s = b, u = 0, v = 1;
    while (a) { ll t = s / a; s -= a * t, u -= v * t; swap(s, a); swap(u, v);}
    if (u < 0) u += b / s;
    return {s, u};
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
    mint inv() const { if(is_prime) {assert(_v);return pow(umod() - 2);} return inv_gcd(_v, m).second;}
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


void ac_yyf(int tt) {
    rd(n,m);
    vector<string> a(n);
    rd(a);

    vector dp(n,vector<mint>(m) );
    vector f(n,vector<mint>(m) ); // path
    vector c(n,vector<mint>(m) ); //cons y pair

    for (int i = 0; i < n; ++i) {
        f[i][0] = 1;
    }
    for (int j = 0; j < m; ++j) {
        f[0][j] = 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            f[i][j] = f[i - 1][j] + f[i][j - 1];
        }
    }

    for(int i=1;i<n;++i){
        if(a[i][0]=='Y'&&a[i][0]==a[i-1][0]){
            c[i][0]=f[i-1][0]+c[i-1][0];
            dp[i][0]=dp[i-1][0]+f[i-1][0]+2*(c[i-1][0]);
        }else{
            c[i][0]=c[i-1][0];
            dp[i][0]=dp[i-1][0];
        }
    }

    for(int i=1;i<m;++i){
        if(a[0][i]=='Y'&&a[0][i]==a[0][i-1]){
            c[0][i]=f[0][i-1]+c[0][i-1];
            dp[0][i]=dp[0][i-1]+f[0][i-1]+2*(c[0][i-1]);
        }else{
            c[0][i]=c[0][i-1];
            dp[0][i]=dp[0][i-1];
        }
    }

    for(int i=1;i<n;++i){
        for(int j=1;j<m;++j){
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
            c[i][j]=c[i-1][j]+c[i][j-1];
            if(a[i][j]=='Y'){       
                if(a[i-1][j]=='Y'){
                    dp[i][j]+=f[i-1][j]+2*c[i-1][j];
                    c[i][j]+=f[i-1][j];
                }
                if(a[i][j-1]=='Y'){
                    dp[i][j]+=f[i][j-1]+2*c[i][j-1];
                    c[i][j]+=f[i][j-1];
                }
            }
        }
    }
    cout<<dp[n-1][m-1]<<"\n";

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
