#include <bits/stdc++.h>
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
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> a;
    static int lg(unsigned x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
    FenwickTree(int n) : n(n), a(n) {}
    FenwickTree(vector<T> &A) : FenwickTree((int)A.size()) {
        for (int i = 0; i < n; ++i) add(i, A[i]);
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    T sum(int x) {
        T ans{};
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T sum(int l, int r) { //sum[l..r]
        return l <= r ? sum(r) - sum(l - 1) : T{}; 
    }
    T get(int x) const {   // 0 <= x < n, get a[x] in O(1), Equivalent to sum(x, x).
        T s = a[x];
        int y = x + 1;
        y -= y & -y;
        while (x != y) s -= a[x - 1], x -= x & -x;
        return s;
    }
    void set(int x, T v) {  // 0 <= x < n, set a[x] = v
        add(x, v - get(x));
    }
    int kth(T k) const {
        if (k < T()) return -1;
        int x = 0;
        for (int i = 1 << lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i, k -= a[x - 1];
            }
        }
        return x;
    }
};

template <class T>
struct Discrete {
    vector<T> xs;
    Discrete(const vector<T>& v) {
        xs = v;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }
    int get(const T& x) const {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    inline int operator()(const T& x) const { return get(x); }
    T operator[](int i) { return xs[i]; }
    int size() const { return xs.size(); }
};


void ac_yyf(int tt) {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    Discrete<int> v(a);
    each(x,a)x=v(x);
    map<int,int>mp;
    for(auto&x:a)
        mp[x]++;
    m=sz(v);
    FenwickTree<int> f(m);
    f0(n)f.add(a[i],1);
    FenwickTree<int> g(m);

    ll c=0;
    f0(n){
    	f.add(a[i],-1);
        int lbg=g.sum(a[i]+1,m-1),lsm=g.sum(0,a[i]-1),leq=g.get(a[i]);
        int rbg=f.sum(a[i]+1,m-1),rsm=f.sum(0,a[i]-1),req=f.get(a[i]);
        c+=lbg*1ll*rsm;
        c+=lsm*1ll*rbg;
        c+=leq*1ll*(rbg+rsm);
        c+=(lbg+lsm)*1ll*req;
        g.add(a[i],1);
    }
    for(auto&[k,v]:mp){
        if(v>=3){
            c+=v*(v-1ll)*(v-2ll)/6;
        }
    }
    wt(c,nl);
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