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

struct SCC {
    int n, cnt = 0;
    vector<pair<int, int>> edges;
    vector<int> low, dfn, ids, in, out;
    explicit SCC(int n) : n(n), low(n), dfn(n, -1), ids(n){}
    void add_edge(int from, int to) { edges.push_back({from, to}); }

    void scc_ids() {
        vector<int> start(n + 1), elist(edges.size()), visited;
        for (auto &e : edges) 
            start[e.first + 1]++;
        for (int i = 1; i <= n; ++i) 
            start[i] += start[i - 1];
        auto counter = start;
        for (auto &e : edges)
            elist[counter[e.first]++] = e.second;
        int now_dfn = 0;
        visited.reserve(n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = dfn[v] = now_dfn++;
            visited.push_back(v);
            for (int i = start[v]; i < start[v + 1]; i++) {
                auto to = elist[i];
                if (dfn[to] == -1) {
                    self(self, to);
                    low[v] = min(low[v], low[to]);
                } else {
                    low[v] = min(low[v], dfn[to]);
                }
            }
            if (low[v] == dfn[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    dfn[u] = n, ids[u] = cnt;
                    if (u == v) break;
                }
                cnt++;
            }
        };
        for (int i = 0; i < n; i++) if (dfn[i] == -1) dfs(dfs, i);
        in.assign(cnt, 0);
        for (auto& x : ids) {
            x = cnt - 1 - x;
            in[x]++;
        }
    }

    vector<vector<int>> scc(bool cal_degree = false) {
        scc_ids();
        vector<vector<int>> groups(cnt);
        for (int i = 0; i < cnt; ++i) groups[i].reserve(in[i]);
        for (int i = 0; i < n; i++) groups[ids[i]].push_back(i);
        if (cal_degree) {
            in.assign(cnt, 0), out.assign(cnt, 0);
            for (auto &[from, to]: edges) {
                int x = ids[from], y = ids[to];
                if (x != y) in[y]++, out[x]++;
            }
        }
        return groups;
    }
};

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

bool ac_yyf(int tt) {
    rd(n,m);
    vector<string> a(n);
    rd(a);
    DSU d(n*m);
    auto get=[&](int x, int y){
    	return x*m+y;
    };

    f0(n)f2(j,m){
    	if(i&&a[i-1][j]==a[i][j]&&!d.merge(get(i-1,j),get(i,j)))
    		return 1;

    	if(j&&a[i][j-1]==a[i][j]&&!d.merge(get(i,j-1),get(i,j)))
    		return 1;
    }
    return 0;
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
