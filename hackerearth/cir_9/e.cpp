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

struct EulerTour {
  int n, m;
    vector<int> in, out, dep, seg;
    template <typename G>
    EulerTour(const G g, int n, int root = 0) : n(n), m(ceil_pow(2 * n)), in(n), out(n), dep(n + 1) {
        seg.assign(2 * m, n);
        dfs(g, root);
        for (int k = m - 1; k > 0; --k) seg[k] = argmin(seg[(k << 1) | 0], seg[(k << 1) | 1]);
    }
    template <typename E, typename EdgeToNode>
    EulerTour(const vector<vector<E>> &g, const EdgeToNode e2n, int root = 0) :
        EulerTour([&](int u, auto f) { for (const E &e : g[u]) f(e2n(e)); }, g.size(), root) {}
    EulerTour(const vector<vector<int>> &g, int root = 0) :
        EulerTour([&](int u, auto f) { for (int v : g[u]) f(v); }, g.size(), root) {}
    int lca(int u, int v) const {
        if (in[u] > in[v]) return lca(v, u);
        int res = n;
        for (int l = m + in[u], r = m + in[v] + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = argmin(res, seg[l++]);
            if (r & 1) res = argmin(res, seg[--r]);
        }
        return res;
    }
    inline int dis(int u, int v) const { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }
    inline int parent(int u) const {
        int p = seg[m + out[u]];
        return p == n ? -1 : p;
    }
    template <typename F>
    void node_query(int u, int v, F &&f) {
      int l = lca(u, v);
      f(in[l], in[u]);
      f(in[l] + 1, in[v]);
    }
    template <typename F>
    void edge_query(int u, int v, F &&f) {
      int l = lca(u, v);
      f(in[l] + 1, in[u]);
      f(in[l] + 1, in[v]);
    }
    template <typename G>
    void dfs(G g, int root) {
        dep[root] = 0, dep[n] = numeric_limits<int>::max();
        int k = 0;
        auto f = [&](auto self, int u, int p) -> void {
            in[u] = k, seg[m + k++] = u;
            g(u, [&](int v){ if (v != p) dep[v] = dep[u] + 1, self(self, v, u); });
            out[u] = k, seg[m + k++] = p;
        };
        f(f, root, n);
    }
    inline int argmin(int u, int v) const { return dep[u] < dep[v] ? u : v; }
    static int ceil_pow(const int n) {
        return 1 << (n <= 1 ? 0 : 32 - __builtin_clz(n - 1));
    }
};
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


vector<int> path_equal_k(vector<int> &a, vector<vector<int>> &es, vector<vector<int>> &qs){
	int n=sz(a),q=sz(qs);
	vector<vector<int>> g(n);
	for(auto&e:es){
		g[e[0]].push_back(e[1]);
		g[e[1]].push_back(e[0]);
	}
	EulerTour e(g);
	vector<int> v=a;
	for(auto&q1:qs)
		v.push_back(q1[2]);
	Discrete<int> d(v);
	int m=sz(v);

	vector<vector<int>> c(m), p(m);
	f0(n)c[d(a[i])].push_back(i);
	f0(q)p[d(qs[i][2])].push_back(i);

	FenwickTree<int> f(n*2);
	auto add=[&](int k, int v){
		for (auto &x: c[k]) {
			f.add(e.in[x], v);
			f.add(e.out[x], -v);
		}
	};
	vector<int> ans(q);

	f0(m) {
		if(sz(c[i])==0||sz(p[i])==0) continue;
		add(i, 1);
		for(auto&j:p[i]){
			int s=0;
			e.node_query(qs[j][0],qs[j][1],[&](int x, int y){
				s+=f.sum(x,y);
			});
			ans[j]=s;
		}
		add(i, -1);
	}
	return ans;
}

void ac_yyf(int tt) {
    rd(n);
    vector<int> a(n);
    rd(a);
    vector<vector<int>> es(n-1,vector<int>(2));
    rd(es);
    rd(q);
    vector<vector<int>> qs(q,vector<int>(3));
    rd(qs);
    auto ans=path_equal_k(a, es, qs);
    each(x,ans)wt(x,nl);
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
