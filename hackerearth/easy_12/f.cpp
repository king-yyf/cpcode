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

struct Edcc {
    int n, m = 0, dcc_cnt = 0, init = 0;
    vector<vector<pair<int,int>>> g;
    vector<array<int, 2>> elist;
    vector<int> dfn, low, ids, deg;
    vector<bool> is_bridge;

    Edcc(int n = 0): n(n), dfn(n, -1), low(n), g(n), ids(n){}

    void add_edge(int a, int b) {
        g[a].emplace_back(b, m);
        g[b].emplace_back(a, m);
        elist.push_back({a, b});
        m++;
    }

    void get_ids() {
        init = 1;
        vector<bool> visited(n, false);
        is_bridge.assign(m, false);
        vector<int> stk;
        int now_dfn = 0;

        function<void(int, int)> dfs = [&](int u, int fa) {
            visited[u] = true;
            stk.push_back(u);
            low[u] = dfn[u] = now_dfn++;
            int pa_cnt = 0;
            for (auto &[v, id]: g[u]) {
                if (v == fa && pa_cnt++ == 0) continue;
                if (visited[v]) {
                    low[u] = min(low[u], dfn[v]);
                } else {
                    dfs(v, u);
                    is_bridge[id] = low[v] > dfn[u];
                    low[u] = min(low[u], low[v]);
                }
            }
            if (dfn[u] == low[u]) {
                while (true) {
                    int v = stk.back();
                    stk.pop_back();
                    ids[v] = dcc_cnt;
                    if (u == v) break;
                }
                dcc_cnt ++;
            }
        };
        
        for (int i = 0; i < n; i++)
            if (!~dfn[i])
                dfs(i, -1);
    }

    vector<vector<int>> edcc() {
        if (!init) get_ids();
        vector<vector<int>> groups(dcc_cnt);
        for (int i = 0; i < n; ++i) {
            groups[ids[i]].push_back(i);
        }
        deg.assign(dcc_cnt, 0);
        for (int i = 0; i < m; ++i) {
            if (is_bridge[i]) {
                deg[ids[elist[i][0]]]++;
                deg[ids[elist[i][1]]]++;
            }
        }
        return groups;
    }

    vector<vector<int>> bridge_tree() {
        if (!init) get_ids();
        vector<vector<int>> tr(dcc_cnt);
        for (int i = 0; i < m; ++i) {
            if (is_bridge[i]) {
                int x = ids[elist[i][0]], y = ids[elist[i][1]];
                tr[x].push_back(y);
                tr[y].push_back(x);
            }
        }
        return tr;
    }
};

void ac_yyf(int tt) {
    int n, m;
    cin>>n>>m;
    Edcc g(n);
    vector<int> p(m);
    rd(p);
    f0(m){
    	int u,v;
    	cin>>u>>v;
    	u--,v--;
    	g.add_edge(u,v);
    }
    auto dcc = g.edcc();
    int c=0;
    ll s1=0,s2=0;
    vector<int> q;
    f0(m){
    	if(g.is_bridge[i]) {
    		q.push_back(p[i]);
    	}
    }
    sort(rall(q));
    f0(sz(q)){
    	if(i%2==0)s1+=q[i];
    	else s2+=q[i];
    }
    wt(s1,' ',s2,nl);
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
