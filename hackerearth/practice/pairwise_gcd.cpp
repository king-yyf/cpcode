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
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

template <class T> void multiple_zeta(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = N / p; j > 0; --j) f[j] += f[j * p];
    }
}
// inverse of multiple_zeta O(N loglog N)
template <class T> void multiple_moebius(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = 1; j * p <= N; ++j) f[j] -= f[j * p];
    }
}
// 对于n的所有约数m,求f(m)的总和 O(N loglog N)
template <class T> void divisor_zeta(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; ++p) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = 1; j * p <= N; ++j) f[j * p] += f[j];
    }
}
// inverse of divisor_zeta()
template <class T> void divisor_moebius(vector<T> &f) {
    int N = int(f.size()) - 1;
    vector<char> is_prime(N + 1, 1);
    for (int p = 2; p <= N; ++p) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = N / p; j > 0; --j) f[j * p] -= f[j];
    }
} 
// GCD convolution, ret[k] = \sum_{gcd(i, j) = k} f[i] * g[j]
template <class T> vector<T> gcdconv(vector<T> f, vector<T> g) {
    assert(f.size() == g.size());
    multiple_zeta(f); multiple_zeta(g);
    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];
    multiple_moebius(f);
    return f;
}
// LCM convolution ret[k] = \sum_{lcm(i, j) = k} f[i] * g[j]
template <class T> vector<T> lcmconv(vector<T> f, vector<T> g) {
    assert(f.size() == g.size());
    divisor_zeta(f); divisor_zeta(g);
    for (int i = 0; i < int(g.size()); ++i) f[i] *= g[i];
    divisor_moebius(f);
    return f;
}

void ac_yyf(int tt) {
	rd(n);
    vector<ll> a(n+1);
    f1(n)a[i]=1;
    auto c=gcdconv(a,a);
    ll ans=0;
    f1(n){
    	ans+=i*1ll*c[i];
    }
    wt((ans-n*1ll*(n+1)/2)/2,nl);
}

int main() {
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
