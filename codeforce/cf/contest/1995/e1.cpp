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

void solve(int tt) {
    rd(n);
    vector<int> a(2*n);
    rd(a);
    if(n==1){
        wt(0,nl);
        return;
    }
    ll c=infll;
    vector<int> b,d;
    for(int i=0;i<2*n;i+=2) {
        // a[i],a[i+1],
        if(i+n>=2*n)break;
        int x1=a[i],y1=a[i+1],x2=a[i+n],y2=a[i+n+1];
        ar(2) p = {x1+y1,x2+y2};
        ar(2) q = {x1+y2,x2+y1};
        int mn=max(min(p[0],p[1]),min(q[0],q[1]));
        int mx=min(max(p[0],p[1]),max(q[0],q[1]));
        b.push_back(mn);
        d.push_back(mx);
    }
    sort(all(b));
    sort(all(d));



    for(int i=0;i<2*n;i+=2) {
        if(i+n>=2*n)break;
        int mn=b[i/2];
        int mx=d.back();
        bool ok=1;
        for(int j=0;j<2*n;j+=2) {
            if(j+n>=2*n)break;
            int x1=a[j],y1=a[j+1],x2=a[j+n],y2=a[j+n+1];
            ar(2) p = {x1+y1,x2+y2};
            ar(2) q = {x1+y2,x2+y1};
            bool o=0;
            if(tt==3)
                dbg(x1,y1,x2,y2,p[0],p[1],q[0],q[1]);
            int x=min(p[0],p[1]),y=max(p[0],p[1]);
            int cu=d.back();
            if(x>=mn){
                o=1;
                cmn(cu,y);
            }
            x=min(q[0],q[1]),y=max(q[0],q[1]);
            if(x>=mn){
                o=1;
                cmn(cu,y);
            }
            if(o){
                cmn(mx,cu);
            }else {
                ok=0;
                break;
            }
            // int mn=max(min(p[0],p[1]),min(q[0],q[1]));
            // int mx=min(max(p[0],p[1]),max(q[0],q[1]));
        }
        if(tt==3)
        dbg(mn,mx,ok,c,i);
        if(ok)cmn(c,mx-mn);
    }

    // if(tt>=4){
    //     wt(b);
    //     wt(d);
    // }
    // if(b.back()>=d[0]){
    //     wt(0,nl);
    //     return;
    // }
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