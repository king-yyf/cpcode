#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
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
int n, m, k;

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

class Solution {
public:
    vector<int> gcdValues(vector<int>& a, vector<long long>& qs) {
        n=sz(a),m=sz(qs);
        int mx=Mx(a);
        int d=clg(mx+1);
        vector<int> f((1<<d));
        each(x,a)f[x]++;
        vector<int> g=gcdconv(f,f);
        f0(mx+1){
        	g[i]-=f[i];
        	g[i]/=2;
        }
        vector<long long> s(mx+1);
        f1(mx){
        	s[i]=s[i-1]+g[i];
        }
        // wt(g);
        // wt(s);
        // wt(qs);
        vector<int> c(m);
        f0(m)c[i]=rb(s,qs[i]);
        // wt(c);
        return c;
    }
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a{2,1,4,4},b;
    vector<long long> qs={5,3,1,0};
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    Solution so;
    // rd(a,k);
    auto ans = so.gcdValues(a,qs);
    // wt(ans);
    cout<<'\n';
    return 0;
}
#endif
