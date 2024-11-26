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
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
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

template <class T,   // dp值的类型，如ll，int等。
        T(*op)(T, T), // 合并运算，需要满足交换律 op(dp[i], dp[j])
        T(*e)(),    // op 运算单位元，op(x, e()) = x
        T(*G)(T, int, int), // 根节点累积信息 G(dp[child], child, fa)
        class E,  // 边上 weight 的类型
        T(*F)(T, int, int, E)> // 子节点信息转移为父节点 F(dp[child], child, fa, weight(child, fa))
struct ReRooting : public vector<vector<pair<int, E>>> {
    using base_type = vector<vector<pair<int, E>>>;
    public:
        static constexpr int NIL = -1;
        using base_type::base_type;

        void add_edge(int u, int v, const E& w) {
            (*this)[u].emplace_back(v, w);
            (*this)[v].emplace_back(u, w);
        }

        const vector<T>& get(int root = 0) {
            const int n = this->size();
            dp.resize(n), to_par.resize(n);
            dfs_subtree(root, NIL);
            dfs(root, NIL, e());
            return dp;
        }

    private:
        vector<T> dp, to_par;

        void dfs_subtree(int u, int p) {
            dp[u] = e();
            for (auto [v, w] : (*this)[u]) {
                if (v == p) continue;
                dfs_subtree(v, u);
                dp[u] = op(dp[u], to_par[v] = F(G(dp[v], v, u), v, u, w));
            }
        }
        void dfs(int u, int p, T from_p) {
            dp[u] = G(dp[u], u, NIL);
            const int sz = (*this)[u].size();
            vector<T> cum_l { e() };
            cum_l.reserve(sz + 1);
            for (const auto& [v, _] : (*this)[u]) cum_l.push_back(op(cum_l.back(), v == p ? from_p : to_par[v]));
            T cum_r = e();
            for (int i = sz - 1; i >= 0; --i) {
                const auto& [v, w] = (*this)[u][i];
                if (v == p) {
                    cum_r = op(from_p, cum_r);
                } else {
                    T from_u = F(G(op(cum_l[i], cum_r), u, v), u, v, w);
                    dp[v] = op(dp[v], from_u);
                    dfs(v, u, from_u);
                    cum_r = op(to_par[v], cum_r);
                }
            }
        }
};

// dp[v]=g( op(f(dp[c1], v1),  f(dp[c2], v2) , ... f(dp[c2], v2)), v)
using S = pair<long long, int>;
using E = nullptr_t;
S op(S x, S y) {
    return S{x.first + y.first, x.second + y.second};
}
S e() {
    return S{};
}
S G(S x, int u, int fa) {
    return S{x.first, x.second + 1};
}
S F(S x, int u, int fa, E w) {
    return S{x.first + x.second, x.second};
}

void ac_yyf(int tt) {
    cin >> n;
    ReRooting<S, op, e, G, E, F> g(n);
    for (int i = 0; i < n - 1; ++i) {
        cin >> x >> y;
        g.add_edge(--x, --y, nullptr);
    }
    long long s = 0, c = n * 1ll * (n - 1) * (n - 2) / 6;
    for (auto x : g.get()) {
        s += x.first;
    }
    cout << c - (s - n * (n - 1ll)) / 2 << "\n";
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
