#pragma GCC optimize("Ofast,unroll-loops")
#include <bits/stdc++.h>
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
constexpr int N = 1e6 + 5;
int n, m, q;
int x, y, k;
string s, t;

struct Sieve {
    vector<int> min_fact, primes;
    int N;
    Sieve(int n): N(n), min_fact(n + 1) {
        for (int d = 2; d <= N; d++) {
            if (!min_fact[d]) {
                min_fact[d] = d;
                primes.push_back(d);
            }
            for (const auto &p : primes) {
                if (p > min_fact[d] or d * 1ll * p > N) break;
                min_fact[d * p] = p;
            }
        }
    }
    bool is_prime(int x) {
        if (x < N + 1) return min_fact[x] == x;
        assert(N * 1ll * N >= x);
        for (const auto &p : primes) if (x % p == 0) return false;
        return true;
    }
    template <class T> map<T, int> factorize(T x) const {
        map<T, int> ret;
        for (const auto &p : primes) {
            if (x < T(N + 1)) break;
            while (!(x % p)) x /= p, ret[p]++;
        }
        if (x >= T(N + 1)) ret[x]++, x = 1;
        while (x > 1) ret[min_fact[x]]++, x /= min_fact[x];
        return ret;
    }
    template <class T> vector<T> divisors(T x) const {
        vector<T> ret{1};
        for (const auto p : factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                for (T a = 1, d = 1; d <= p.second; d++) {
                    a *= p.first;
                    ret.push_back(ret[i] * a);
                }
            }
        }
        // sort(ret.begin(), ret.end()); // if need sort
        return ret; 
    }
    template <class T> map<T, T> euler_of_divisors(T x) const {
        assert(x >= 1);
        map<T, T> ret; ret[1] = 1;
        vector<T> divs{1};
        for (auto p : factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);
                divs.push_back(divs[i] * p.first);
                for (T a = divs[i] * p.first, d = 1; d < p.second; a *= p.first, d++) {
                    ret[a * p.first] = ret[a] * p.first;
                    divs.push_back(a * p.first);
                }
            }
        }
        return ret;
    }
    vector<int> moebius_table() const {
        vector<int> ret(N + 1);
        for (unsigned i = 1; i <= N; i++) {
            if (i == 1) ret[i] = 1;
            else if ((i / min_fact[i]) % min_fact[i] == 0) ret[i] = 0;
            else ret[i] = -ret[i / min_fact[i]];
        }
        return ret;
    }
};

vector<int> p;
set<int> ss;
Sieve se(N);
void solve(int tt) {
    
}
bool boolf(int tt) {
	ll n;
	rd(n);
	n-=4;
	if(n<34){
		return 0;
	}

	for(auto&x:p) {
		if(x==2)continue;
		ll s=x*1ll*x;
		if(s>n)break;
		ll cu=n-s;
		int y=sqrtl(cu);
		if(y*1ll*y==cu && ss.count(y) && y!=x&&y!=2) return 1;
	}
	return 0;
}

int main() {
    int T = 1, fun_type = 1;
    p=se.primes;
    ss=set<int>(all(p));
    // each(x,d){
    // 	if(x*1ll*x<N) p.push_back(x);
    // }
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        if (fun_type == 0) solve(cas);
        else if (fun_type == 1) cout << (boolf(cas) ? "Yes" : "No") << '\n';
        else cout << (boolf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
