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
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
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
const int N = 2e5 + 5;
int n, m, k;

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


class Solution {
public:
    int minAnagramLength(string s) {
        n=sz(s);
        if(s==string(n,s[0])){
        	return 1;
        }
        ndarr<int, 2> f({n+1,26}, 0);
        f0(n){
        	int t=s[i]-'a';
        	f2(j,26){
        		f[{i+1,j}]=f[{i,j}]+(t==j);
        	}
        }
        int c=n;
        for(int i=i/2;i>1;--i){
        	if(n%i==0){
        		vector<int> p(26);
        		bool o=1;
        		wt(p);
        		for(int j=0;j<n;j+=i){
        			if(j==0){
        				f2(k,26)p[k]=f[{j+i,k}]-f[{j,k}];
        			}else{
        				f2(k,26) if(p[k]!=f[{j+i,k}]-f[{j,k}]){
        					o=0;break;
        				}
        			}
        		}
        		if(o)c=i;
        	}
        }
        return c;
    }
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a,b;
    string s="abba",t;
    Solution so;
    auto p=so.minAnagramLength(s);
    cout<<'\n';
    return 0;
}
#endif