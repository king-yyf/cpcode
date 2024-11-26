#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

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
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 1e5 + 1;
int n, m, k;

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

Sieve s(N);


template <typename T, class LF, class RF>
void monoStack(vector<T> &a, vector<int> &lt, vector<int> &rt, LF F1, RF F2) {
    int n = a.size();
    lt.assign(n, -1), rt.assign(n, n);
    stack<int> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && F1(a[i],a[sk.top()])) {
            rt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    sk = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && F2(a[i],a[sk.top()])) {
            lt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
}
template <typename T>  // 左右第一个更小的数，即以当前元素为最小值的区间
void le_le(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, less<T>(), less<T>());
}
template <typename T>  // 左右第一个更小的数，右侧是小于等于
void le_le_eq(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, less<T>(), less_equal<T>());
}
template <typename T> // 左右第一个更大的数，即以当前元素为最大值的区间
void gt_gt(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, greater<T>(), greater<T>());
}
template <typename T> // 左右第一个更大的数，右侧是大于等于
void gt_gt_eq(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, greater<T>(), greater_equal<T>());
}

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


const int mod=1000000007;
class Solution {
public:
    int maximumScore(vector<int>& a, int k) {
        n=sz(a);
        vector<ar3> b(n);
        f0(n){
        	auto p=s.factorize(a[i]).size();
        	b[i]={a[i],(int)p,i};
        	a[i]=p;
        }
        sort(rall(b));
        vector<int> lmx,rmx;
        gt_gt_eq(a,lmx,rmx);
        // int mx=Mx(a);
        // vector<ll> p(mx+1);
        // f0(n){
        // 	int l=lmx[i],r=rmx[i];
        // 	p[a[i]]+=(i-l)*1ll*(r-i);
        // }
        mint c=1;
        for(auto&[x,p,i]:b){
        	int l=lmx[i],r=rmx[i];
        	ll t=(i-l)*1ll*(r-i);
        	cmn(t,k);

        	c*=mint(x).pow(t);
        	// dbg(l,r,t,c,x,i,nl);
        	k-=t;
        	if(k==0)break;
        }
        return c.val();
    }
};

#ifdef sigma-yyf
int main(){
     vector<int> a{19,12,14,6,10,18};
     Solution so;
     int k=3;
     auto c=so.maximumScore(a,k);
    cout<<'\n';
    return 0;
}
#endif
