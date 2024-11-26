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
constexpr int N = 2e5 + 5;
int n, m, q;
int x, y, k;
string s, t;

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


using T = ll;
T dp(string &s, int k) {
    int n = s.size();
    ndarr<T, 3> f({n, n*10+4, k}, -1);
    function<T(int, int, int, bool, bool)> dfs = [&](int p, int sum, int d, bool limit, bool is_num) -> T {
        if (p == n) return is_num && sum != 0 && (d!=3); // 
        if (!limit && is_num && ~f[{p, sum, d}]) return f[{p, sum, d}];
        T res{};
        if (!is_num) res = dfs(p + 1, sum, d, false, false);
        int up = limit ? s[p] - '0' : 9;
        for (int i = 1 - is_num; i <= up; ++i) {
            res += dfs(p + 1, (sum + i)%3, i, limit && i == up, true);
                
        }
        if (!limit && is_num)
            f[{p, sum, d}] = res;
        return res;
    };
    return dfs(0, 0, 0, true, false);
}

void solve(int tt) {
    ll n;
    rd(n);
    ll l=n,r=1e18, c=r;
    while(l<=r){
    	ll md=(l+r)/2;
    	string ss=to_string(md);
    	ll t=dp(ss,3);
    	if(t>=n){
    		c=md;r=md-1;
    	}else l=md+1;
    }
    wt(c,nl);
}
bool boolf(int tt) {
    return 0;
}

int main() {
    int T = 1, fun_type = 0;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        if (fun_type == 0) solve(cas);
        else if (fun_type == 1) cout << (boolf(cas) ? "Yes" : "No") << '\n';
        else cout << (boolf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}