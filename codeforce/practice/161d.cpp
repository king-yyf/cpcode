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

#line 2 "convolution/fft_double.hpp"
#include <complex>
#include <utility>
#include <vector>

// CUT begin
// Convolution by FFT (Fast Fourier Transform)
// Algorithm based on <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>
// Verified: ATC001C (168 ms) <https://atcoder.jp/contests/atc001/submissions/9243440>
using cmplx = std::complex<double>;
double PI = acos(-1);
void fft(int N, std::vector<cmplx> &a, double dir) {
    int i = 0;
    for (int j = 1; j < N - 1; j++) {
        for (int k = N >> 1; k > (i ^= k); k >>= 1)
            ;
        if (j < i) std::swap(a[i], a[j]);
    }

    std::vector<cmplx> zeta_pow(N);
    for (int i = 0; i < N; i++) {
        double theta = PI / N * i * dir;
        zeta_pow[i] = {cos(theta), sin(theta)};
    }

    for (int m = 1; m < N; m *= 2) {
        for (int y = 0; y < m; y++) {
            cmplx fac = zeta_pow[N / m * y];
            for (int x = 0; x < N; x += 2 * m) {
                int u = x + y;
                int v = x + y + m;
                cmplx s = a[u] + fac * a[v];
                cmplx t = a[u] - fac * a[v];
                a[u] = s;
                a[v] = t;
            }
        }
    }
}
template <typename T> std::vector<cmplx> conv_cmplx(const std::vector<T> &a, const std::vector<T> &b) {
    int N = 1;
    while (N < (int)a.size() + (int)b.size()) N *= 2;
    std::vector<cmplx> a_(N), b_(N);
    for (int i = 0; i < (int)a.size(); i++) a_[i] = a[i];
    for (int i = 0; i < (int)b.size(); i++) b_[i] = b[i];
    fft(N, a_, 1);
    fft(N, b_, 1);
    for (int i = 0; i < N; i++) a_[i] *= b_[i];
    fft(N, a_, -1);
    for (int i = 0; i < N; i++) a_[i] /= N;
    return a_;
}
// retval[i] = \sum_j a[j]b[i - j]
// Requirement: length * max(a) * max(b) < 10^15
template <typename T> std::vector<long long int> fftconv(const std::vector<T> &a, const std::vector<T> &b) {
    std::vector<cmplx> ans = conv_cmplx(a, b);
    std::vector<long long int> ret(ans.size());
    for (int i = 0; i < (int)ans.size(); i++) ret[i] = floor(ans[i].real() + 0.5);
    ret.resize(a.size() + b.size() - 1);
    return ret;
}
#line 2 "tree/centroid_decomposition.hpp"
#include <tuple>
#line 5 "tree/centroid_decomposition.hpp"

// CUT begin
/*
(Recursive) Centroid Decomposition
Verification: Codeforces #190 Div.1 C https://codeforces.com/contest/321/submission/59093583

fix_root(int r): Build information of the tree which `r` belongs to.
detect_centroid(int r): Enumerate centroid(s) of the tree which `r` belongs to.
*/
struct CentroidDecomposition {
    int NO_PARENT = -1;
    int V;
    int E;
    std::vector<std::vector<std::pair<int, int>>> to; // (node_id, edge_id)
    std::vector<int> par;                             // parent node_id par[root] = -1
    std::vector<std::vector<int>> chi;                // children id's
    std::vector<int> subtree_size;                    // size of each subtree
    std::vector<int> available_edge;                  // If 0, ignore the corresponding edge.

    CentroidDecomposition(int v = 0) : V(v), E(0), to(v), par(v, NO_PARENT), chi(v), subtree_size(v) {}
    CentroidDecomposition(const std::vector<std::vector<int>> &to_) : CentroidDecomposition(to_.size()) {
        for (int i = 0; i < V; i++) {
            for (auto j : to_[i]) {
                if (i < j) { add_edge(i, j); }
            }
        }
    }

    void add_edge(int v1, int v2) {
        to[v1].emplace_back(v2, E), to[v2].emplace_back(v1, E), E++;
        available_edge.emplace_back(1);
    }

    int _dfs_fixroot(int now, int prv) {
        chi[now].clear(), subtree_size[now] = 1;
        for (auto nxt : to[now]) {
            if (nxt.first != prv and available_edge[nxt.second]) {
                par[nxt.first] = now, chi[now].push_back(nxt.first);
                subtree_size[now] += _dfs_fixroot(nxt.first, now);
            }
        }
        return subtree_size[now];
    }

    void fix_root(int root) {
        par[root] = NO_PARENT;
        _dfs_fixroot(root, -1);
    }

    //// Centroid Decpmposition ////
    std::vector<int> centroid_cand_tmp;
    void _dfs_detect_centroids(int now, int prv, int n) {
        bool is_centroid = true;
        for (auto nxt : to[now]) {
            if (nxt.first != prv and available_edge[nxt.second]) {
                _dfs_detect_centroids(nxt.first, now, n);
                if (subtree_size[nxt.first] > n / 2) is_centroid = false;
            }
        }
        if (n - subtree_size[now] > n / 2) is_centroid = false;
        if (is_centroid) centroid_cand_tmp.push_back(now);
    }
    std::pair<int, int> detect_centroids(int r) { // ([centroid_node_id1], ([centroid_node_id2]|-1))
        centroid_cand_tmp.clear();
        while (par[r] != NO_PARENT) r = par[r];
        int n = subtree_size[r];
        _dfs_detect_centroids(r, -1, n);
        if (centroid_cand_tmp.size() == 1)
            return std::make_pair(centroid_cand_tmp[0], -1);
        else
            return std::make_pair(centroid_cand_tmp[0], centroid_cand_tmp[1]);
    }

    std::vector<int> _cd_vertices;
    void _centroid_decomposition(int now) {
        fix_root(now);
        now = detect_centroids(now).first;
        _cd_vertices.emplace_back(now);
        /*
        do something
        */
        for (auto p : to[now]) {
            int nxt, eid;
            std::tie(nxt, eid) = p;
            if (available_edge[eid] == 0) continue;
            available_edge[eid] = 0;
            _centroid_decomposition(nxt);
        }
    }
    std::vector<int> centroid_decomposition(int x) {
        _cd_vertices.clear();
        _centroid_decomposition(x);
        return _cd_vertices;
    }
};
#line 3 "tree/test/frequency_table_of_tree_distance.test.cpp"
#include <algorithm>
#include <iostream>
#include <unordered_set>
#line 7 "tree/test/frequency_table_of_tree_distance.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
using namespace std;

struct frequency_table_of_tree_distance_ {
    vector<vector<int>> tos;
    vector<int> tmp;

    vector<int> alive;

    void _dfs(int now, int prv, int depth) {
        if (int(tmp.size()) <= depth) { tmp.resize(depth + 1, 0); }
        tmp[depth]++;
        for (auto nxt : tos[now]) {
            if (!alive[nxt]) continue;
            if (nxt != prv) { _dfs(nxt, now, depth + 1); }
        }
    }
    vector<int> cnt_dfs(int root) { return tmp.clear(), _dfs(root, -1, 0), tmp; }
    vector<long long> operator()(const vector<vector<int>>& to) {
        tos.clear();
        alive.assign(to.size(), 1);
        for (const auto v : to) { tos.emplace_back(v.begin(), v.end()); }
        vector<long long> ret(to.size());
        for (auto root : CentroidDecomposition(to).centroid_decomposition(0)) {
            vector<vector<int>> vv;
            alive[root] = 0;
            for (auto nxt : tos[root]) {
                if (!alive[nxt]) continue;
                // tos[nxt].erase(root);
                vector<int> v = cnt_dfs(nxt);
                for (size_t i = 0; i < v.size(); i++) { ret[i + 1] += v[i]; }
                vv.emplace_back(v);
            }
            sort(vv.begin(), vv.end(),
                 [&](const vector<int>& l, const vector<int>& r) { return l.size() < r.size(); });
            for (size_t j = 1; j < vv.size(); j++) {
                const vector<long long> c = fftconv(vv[j - 1], vv[j]);
                for (size_t i = 0; i < c.size(); i++) { ret[i + 2] += c[i]; }
                for (size_t i = 0; i < vv[j - 1].size(); i++) { vv[j][i] += vv[j - 1][i]; }
            }
            tos[root].clear();
        }
        return ret;
    }
} frequency_table_of_tree_distance;

void ac_yyf(int tt) {
    rd(n,k);
    vector<vector<int>> g(n);
    for (int i = 1, u, v; i < n; ++i) {
    	cin >> u >> v;
    	u--, v--;
    	g[u].push_back(v);
    	g[v].push_back(u);
    }
    auto a=frequency_table_of_tree_distance(g);
    wt(k>n-1?0:a[k],nl);
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
