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

struct DSU {
    vector<int> p, siz;
    DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) { return siz[get(x)]; }
    vector<vector<int>> groups() {
        vector<vector<int>> res(p.size());
        for (int i = 0; i < p.size(); i++) res[get(i)].push_back(i);
        res.erase(
            remove_if(res.begin(), res.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
};


template <typename T, typename Comp>
struct KruscalMST {
    KruscalMST() : KruscalMST(0) {}
    explicit KruscalMST(const int n) : _n(n) {}

    void add_edge(const int u, const int v, const T& cost) { _built = false; es.emplace_back(u, v, cost);}
    void add_edge(const tuple<int, int, T>& e) { _built = false; es.push_back(e);}
    bool build() {
        _built = true, _weight_sum = 0;
        if (_n == 0) return true;
        DSU uf(_n);
        sort(es.begin(), es.end(), [this](const auto& u, const auto& v) { return _comp(std::get<2>(u), std::get<2>(v));});
        for (auto& [u, v, w] : es) {
            if (uf.same(u, v)) u = v = _n;
            else { uf.merge(u, v); _weight_sum += w;}
        }
        es.erase(std::remove_if(es.begin(), es.end(), [this](auto& e) { return std::get<0>(e) == _n; }), es.end());
        return int(es.size()) == _n - 1;
    }
    T get_weight() const { assert(_built); return _weight_sum;}
    const vector<tuple<int, int, T>>& get_mst() const { assert(_built); return es;}
private:
    int _n;
    T _weight_sum;
    Comp _comp{};
    vector<tuple<int, int, T>> es;
    bool _built = false;
};
template <typename T> using minMst = KruscalMST<T, less<T>>;
template <typename T> using maxMst = KruscalMST<T, greater<T>>;

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

const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
void ac_yyf(int tt) {
    rd(n,m);
    vector a(n,vector<int>(m));
    vector<int> p(n*m);
    int t=0;
    f0(n)f2(j,m){
    	rd(x);
    	a[i][j]=x;
    	p[t++]=x;
    }
    Discrete<int> v(p);
    m=v.size();
    minMst<int> g(m);
    f0(n)f2(j,m){
    	for(int k=0;k<2;++k){
    		int nx=i+dx[k],ny=j+dy[k];
    		if(nx>=0&&nx<n&&ny>=0&&ny<m&&a[nx][ny]!=a[i][j]){
    			int x=v(a[i][j]),y=v(a[nx][ny]);
    			g.add_edge(x,y,1);
    		}
    	}
    }
    g.build();
    auto s=g.get_weight();
    wt(s,nl);
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
