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
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
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

template <typename T, int DIM> struct Ndarray {
    static_assert(DIM >= 0, "DIM must >= 0");
    array<int, DIM> shape, strides; T* data;
    Ndarray(array<int, DIM> sp, array<int, DIM> st, T* d) : shape(sp), strides(st), data(d) {}
    Ndarray() : shape{0}, strides{0}, data(nullptr) {}
    int flatten_index(array<int, DIM> idx, bool checked = false) const {
        int res = 0;
        for (int i = 0; i < DIM; i++) { 
            if (checked) assert(0 <= idx[i] && idx[i] < shape[i]);
            res += idx[i] * strides[i]; 
        }
        return res;
    }
    T& operator[] (array<int, DIM> idx) const { return data[flatten_index(idx)];}
    T& at(array<int, DIM> idx) const { return data[flatten_index(idx, true)];}
    template <int D = DIM>
    typename enable_if<(0 < D), Ndarray<T, DIM-1>>::type operator[] (int idx) const {
        array<int, DIM-1> nshape; copy(shape.begin()+1, shape.end(), nshape.begin());
        array<int, DIM-1> nstrides; copy(strides.begin()+1, strides.end(), nstrides.begin());
        T* ndata = data + (strides[0] * idx);
        return Ndarray<T, DIM-1>(nshape, nstrides, ndata);
    }
    template <int D = DIM> typename enable_if<(0 < D), Ndarray<T, DIM-1>>::type at(int x) const { 
        assert(0 <= x && x < shape[0]); return operator[](x);
    }
    template <int D = DIM> typename enable_if<(0 == D), T&>::type operator * () const { return *data;}
};
 
template <typename T, int DIM> struct ndarr {
    static_assert(DIM >= 0, "DIM must >= 0");
    array<int, DIM> shape, strides;
    int len; T* data;
    ndarr() : shape{0}, strides{0}, len(0), data(nullptr) {}
    explicit ndarr(array<int, DIM> shape_, const T& t = T()) {
        shape = shape_, len = 1;
        for (int i = DIM-1; i >= 0; i--) { strides[i] = len; len *= shape[i];}
        data = new T[len];
        fill(data, data + len, t);
    }
    ndarr(const ndarr& o) : shape(o.shape), strides(o.strides), len(o.len), data(new T[len]) {
        for (int i = 0; i < len; i++) data[i] = o.data[i];
    }
    ndarr& operator=(ndarr&& o) noexcept {
        swap(shape, o.shape); swap(strides, o.strides);
        swap(len, o.len); swap(data, o.data);
        return *this;
    }
    ndarr(ndarr&& o) : ndarr() { *this = move(o);}
    ndarr& operator=(const ndarr& o) { return *this = ndarr(o);}
    ~ndarr() { delete[] data; }
    using view_t = Ndarray<T, DIM>;
    view_t view() { return Ndarray<T, DIM>(shape, strides, data);}
    operator view_t() { return view(); }
    using const_view_t = Ndarray<const T, DIM>;
    const_view_t view() const { return Ndarray<const T, DIM>(shape, strides, data);}
    operator const_view_t() const { return view(); }
    T& operator[] (array<int, DIM> idx) { return view()[idx]; }
 
    T& at(array<int, DIM> idx) { return view().at(idx); }
    const T& operator[] (array<int, DIM> idx) const { return view()[idx]; }
    const T& at(array<int, DIM> idx) const { return view().at(idx); }
    template <int D = DIM> typename enable_if<(0 < D), Ndarray<T, DIM-1>>::type operator[] (int x) { return view()[x];}
    template <int D = DIM> typename enable_if<(0 < D), Ndarray<T, DIM-1>>::type at(int x) { return view().at(x);}
    template <int D = DIM> typename enable_if<(0 < D), Ndarray<const T, DIM-1>>::type operator[] (int x) const { return view()[x];}
    template <int D = DIM> typename enable_if<(0 < D), Ndarray<const T, DIM-1>>::type at(int x) const { return view().at(x);}
    template <int D = DIM> typename enable_if<(0 == D), T&>::type operator * () { return *view(); }
    template <int D = DIM> typename enable_if<(0 == D), const T&>::type operator * () const { return *view();}
};

void ac_yyf(int tt) {
    rd(n);
    if(n<3){
    	wt(0);
    	return;
    }
    ndarr<mint, 3> f({5,5,2}, 0);
    f0(4)f2(j,4){
    	f[{i,j,0}]=(i==3?23:1)*(j==3?23:1);
    }
    for(int i=2;i<n;++i){
    	ndarr<mint, 3> g({5,5,2}, 0);
    	f2(c,4){
    		f2(b,4){
    			f2(a,4){
    				if(c==2&&b==1&&a==0)continue;
    				g[{a,b,(c==0&&b==1&&a==1)?1:0}]+=f[{b,c,0}]*(a==3?23:1);
    				g[{a,b,1}]+=f[{b,c,1}]*(a==3?23:1);
    			}
    		}
    	}
    	f=g;
    }
    mint c=0;
    f0(4)f2(j,4){
    	c+=f[{i,j,1}];
    }
    wt(c);
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
