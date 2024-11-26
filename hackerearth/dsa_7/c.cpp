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

struct BipMatching {
    static constexpr int ABSENT = -1;
    int _n, _m;
    vector<int> _to_r, _to_l;
    vector<vector<int>> _g;
    int _f = 0;
    BipMatching() {}
    BipMatching(int n, int m) : _n(n), _m(m), _to_r(_n, ABSENT), _to_l(_m, ABSENT), _g(n + m) {}

    void add_edge(int from, int to) { _g[from].push_back(to), _f = -1;}

    template <bool shuffle = true>
    int solve_heuristics() {
        if (_f >= 0) return _f;
        static std::mt19937 rng(std::random_device{}());
        if constexpr (shuffle) for (auto& adj : _g) std::shuffle(adj.begin(), adj.end(), rng);

        vector<int8_t> vis(_n, false);
        auto dfs = [&, this](auto dfs, int u) -> bool {
            if (std::exchange(vis[u], true)) return false;
            for (int v : _g[u]) if (_to_l[v] == ABSENT) return _to_r[u] = v, _to_l[v] = u, true;
            for (int v : _g[u]) if (dfs(dfs, _to_l[v])) return _to_r[u] = v, _to_l[v] = u, true;
            return false;
        };

        for (bool upd = true; std::exchange(upd, false);) {
            vis.assign(_n, false);
            for (int i = 0; i < _n; ++i) if (_to_r[i] == ABSENT) upd |= dfs(dfs, i);
        }

        return _f = _n - std::count(_to_r.begin(), _to_r.end(), ABSENT);
    }
    int solve_maxflow() {
        if (_f >= 0) return _f;

        const auto h = reversed_graph();
        vector<int> level(_n + _m), iter(_n + _m);
        deque<int> que;

        auto bfs = [&] {
            for (int i = 0; i < _n; ++i) {
                if (_to_r[i] == ABSENT) level[i] = 0, que.push_back(i);
                else level[i] = -1;
            }
            fill(level.begin() + _n, level.end(), -1);
            bool ok = false;
            while (not que.empty()) {
                int v = que.front();
                que.pop_front();
                for (int r : _g[v]) if (_to_r[v] != r and level[_n + r] < 0) {
                    const int l = _to_l[r];
                    level[_n + r] = level[v] + 1;
                    if (l == ABSENT) ok = true;
                    else if (level[l] < 0) level[l] = level[v] + 2, que.push_back(l);
                }
            }
            return ok;
        };
        auto dfs = [&](auto dfs, const int r) -> bool {
            const int level_v = level[_n + r];
            if (level_v < 0) return false;
            const int dr = h[r].size();
            for (int &i = iter[_n + r]; i < dr; ++i) {
                const int l = h[r][i];
                if (level_v <= level[l] or _to_l[r] == l or iter[l] > _m) continue;
                if (int r2 = _to_r[l]; r2 == ABSENT) {
                    iter[l] = _m + 1, level[l] = _n + _m;
                    _to_r[l] = r, _to_l[r] = l;
                    return true;
                } else if (iter[l] <= r2) {
                    iter[l] = r2 + 1;
                    if (level[l] > level[_n + r2] and dfs(dfs, r2)) {
                        _to_r[l] = r, _to_l[r] = l;
                        return true;
                    }
                    iter[l] = _m + 1, level[l] = _n + _m;
                }
            }
            return level[_n + r] = _n + _m, false;
        };

        int flow = 0;
        while (bfs()) {
            fill(iter.begin(), iter.end(), 0);
            for (int j = 0; j < _m; ++j) if (_to_l[j] == ABSENT) flow += dfs(dfs, j);
        }
        return _f = flow;
    }
    int solve() { return solve_maxflow();}

    vector<pair<int, int>> max_matching() { // 最大匹配
        if (_f < 0) solve();
        vector<pair<int, int>> res;
        res.reserve(_f);
        for (int i = 0; i < _n; ++i) if (_to_r[i] != ABSENT) res.emplace_back(i, _to_r[i]);
        return res;
    }

    vector<std::pair<int, int>> min_edge_cover() { //最小路径匹配
        auto res = max_matching();
        vector<bool> vl(_n, false), vr(_n, false);
        for (const auto& [u, v] : res) vl[u] = vr[v] = true;
        for (int u = 0; u < _n; ++u) for (int v : _g[u]) if (not (vl[u] and vr[v])) {
            vl[u] = vr[v] = true;
            res.emplace_back(u, v);
        }
        return res;
    }

    vector<int> min_vertex_cover() {  //最小点匹配
        if (_f < 0) solve();
        vector<vector<int>> g(_n + _m);
        vector<bool> cl(_n, true), cr(_m, false);
        for (int u = 0; u < _n; ++u) for (int v : _g[u]) {
            if (_to_r[u] == v) {
                g[v + _n].push_back(u);
                cl[u] = false;
            } else {
                g[u].push_back(v + _n);
            }
        }
        vector<bool> vis(_n + _m, false);
        deque<int> dq;
        for (int i = 0; i < _n; ++i) if (cl[i]) {
            dq.push_back(i);
            vis[i] = true;
        }
        while (dq.size()) {
            int u = dq.front();
            dq.pop_front();
            for (int v : g[u]) {
                if (vis[v]) continue;
                vis[v] = true;
                (v < _n ? cl[v] : cr[v - _n]) = true;
                dq.push_back(v);
            }
        }
        vector<int> res;
        for (int i = 0; i < _n; ++i) if (not cl[i]) res.push_back(i);
        for (int i = 0; i < _m; ++i) if (cr[i]) res.push_back(_n + i);
        return res;
    }

    vector<int> max_independent_set() {
        vector<bool> use(_n + _m, true);
        for (int v : min_vertex_cover()) use[v] = false;
        vector<int> res;
        for (int i = 0; i < _n + _m; ++i) if (use[i]) res.push_back(i);
        return res;
    }

    int left_size() const { return _n; }
    int right_size() const { return _m; }
    pair<int, int> size() const { return { _n, _m }; }

    int right(int l) const { assert(_f >= 0); return _to_r[l]; }
    int left(int r) const { assert(_f >= 0); return _to_l[r]; }

    const auto graph() const { return _g; }

    vector<vector<int>> reversed_graph() const {
        vector<vector<int>> h(_m);
        for (int i = 0; i < _n; ++i) for (int j : _g[i]) h[j].push_back(i);
        return h;
    }
};

void ac_yyf(int tt) {
    rd(n,m,k);
    BipMatching g(n,m);
    f0(k){
    	rd(x,y);
    	x--,y--;
    	g.add_edge(x,y);
    }
    auto p=g.max_matching();
    wt(sz(p),nl);

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
