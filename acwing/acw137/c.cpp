#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<ll, 3>;
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
	int b;
	rd(n,m,b);
   
    vector<ar3> a(n); 
    vector<long long> v{0};

    f0(n){
    	ll s=0;
    	int z=0;
    	rd(x,y,z);
    	f2(j,z){
    		rd(k);k--;
    		s+=(1<<k);
    	}
    	a[i]={y,x,s};
    }

    sort(all(a));

    // f0(n){
    // 	dbg("i=",i,nl);
    // 	wt(a[i]);
    // }

    const ll inf=2e18;

    ndarr<ll, 2> f({2,1<<m}, inf);

    // f0((1<<m)) {
    // 	f2(j,2){
    // 		f[{j,i}]=inf;
    // 	}
    // }

    f[{0,0}]=0;

    f0(n) for(int s=0;s<(1<<m);++s){
    	cmn(f[{(i+1)&1,s}],f[{(i)&1,s}]);
    	int s1=s|a[i][2];

    	// dbg("i=",i,"s=",s,f[{i&1,s}],nl);

    	if(s1==(1<<m)-1){
    		ll x1=f[{i&1,s}]+a[i][1]+a[i][0]*b;
    		ll x2=f[{(i+1)&1,s1}];
    		// dbg("x1=",x1,"x2=",x2,nl);
    		f[{(i+1)&1,s1}]=min(x1,x2);
    	}else{

    		ll x1=f[{i&1,s}]+a[i][1];
    		ll x2=f[{(i+1)&1,s1}];
    		// dbg("x1=",x1,"x2=",x2,nl);
    		f[{(i+1)&1,s1}]=min(x1,x2);

    		// cmn(f[{(i+1)&1,s1}],x1);

    	}
    }

    if(f[{n&1,(1<<m)-1}]==inf){
    	wt(-1,nl);
    	return;
    }

    wt(f[{n&1,(1<<m)-1}],nl);


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