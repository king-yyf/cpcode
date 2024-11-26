#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;
constexpr char nl = '\n';
constexpr int inf = 1'061'109'567;
constexpr ll infll = 2'000'000'000'000'000'000;
const int N = 2e5 + 5;
int n, m, k;

struct DSU {
    vector<int> f, siz;
    DSU(int n) : f(n), siz(n, 1) { iota(f.begin(), f.end(), 0); }
    int leader(int x) {
        while (x != f[x]) x = f[x] = f[f[x]];
        return x;
    }
    bool same(int x, int y) { return leader(x) == leader(y); }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        siz[x] += siz[y];
        f[y] = x;
        return true;
    }
    int size(int x) { return siz[leader(x)]; }
};

class Solution {
public:
    vector<int> findPermutation(vector<int>& P) {
        int N=sz(P);
        vector<int> par(N, -1);
        auto get_par = [&](int a) {
            while (par[a] >= 0) {
                if (par[par[a]] >= 0) par[a] = par[par[a]];
                a = par[a];
            }
            return a;
        };
        auto merge = [&](int a, int b) {
            a = get_par(a);
            b = get_par(b);
            if (a == b) return false;
            if (par[a] > par[b]) swap(a, b);
            par[a] += par[b];
            par[b] = a;
            return true;
        };
        auto reset_par = [&]() {
            for (int i = 0; i < N; i++) par[i] = -1;
        };
 
        vector<vector<int>> outEdges(N);
        for (int i = 0; i < N; i++) {
            outEdges[P[i]].push_back(i);
        }
 
        // we start at the P[0] -> 0 edge
        vector<int> Q; Q.reserve(N);
        Q.push_back(0);
 
        vector<bool> used(N);
        used[0] = true;
 
        vector<int> num_up(N-1);
        vector<int> num_down(N-1);
 
        for (int z = 1; z < N; z++) {
            for (int cnd = 0; true; cnd++) {
                assert(cnd < N);
                if (used[cnd]) continue;
                // get from Q.back() to P[i]
                // just check this scenario in linear time...
                Q.push_back(cnd);
                used[cnd] = true;
                if ([&]() -> bool {
                    //cerr << "checking sequence" << ' '; for (int i : Q) { cerr << P[i] << '-' << i << ' '; } cerr << '\n';
 
                    for (int i = 0; i+1 < N; i++) {
                        num_up[i] = num_down[i] = 0;
                    }
                    for (int t = 0; t+1 < int(Q.size()); t++) {
                        int st = Q[t];
                        int en = P[Q[t+1]];
                        if (st < en) {
                            for (int i = st; i+1 <= en; i++) {
                                if (num_up[i]) return false;
                                num_up[i]++;
                            }
                        } else if (st > en) {
                            for (int i = st; i-1 >= en; i--) {
                                if (num_down[i-1]) return false;
                                num_down[i-1]++;
                            }
                        }
                    }
 
                    reset_par();
                    for (int i = 0; i < N; i++) {
                        merge(i, P[i]);
                    }
                    for (int i = 0; i+1 < N; i++) {
                        if (num_up[i] || num_down[i]) {
                            if (!merge(i, i+1)) {
                                return false;
                            }
                        }
                    }
 
                    vector<bool> is_main(N);
                    for (int i = 0; i < N; i++) {
                        is_main[i] = (get_par(P[0]) == get_par(i));
                    }
 
                    vector<bool> has_edge(N);
                    reset_par();
                    for (int i = 0; i < N; i++) {
                        if (!used[i]) {
                            merge(i, P[i]);
                            has_edge[i] = has_edge[P[i]] = true;
                        }
                    }
                    for (int i = 0; i+1 < N; i++) {
                        if (num_up[i] ^ num_down[i]) {
                            merge(i, i+1);
                            has_edge[i] = has_edge[i+1] = true;
                        }
                    }
 
                    vector<bool> is_dead(N);
                    for (int i = 0; i < N; i++) {
                        is_dead[i] = is_main[i] && (get_par(P[0]) != get_par(i));
                    }
 
                    for (int i = 0; i+1 < N; i++) {
                        if (is_dead[i] || is_dead[i+1]) continue;
                        merge(i, i+1);
                    }
                    for (int i = 0; i < N; i++) {
                        if (has_edge[i] && get_par(i) != get_par(P[0])) {
                            return false;
                        }
                    }
 
                    return true;
                }()) {
                    break;
                } else {
                    Q.pop_back();
                    used[cnd] = false;
                }
            }
        }
 
       return Q;
    }
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a,b;
    string s,t;
    vector<int> p={1,0,2};
    Solution so;
    auto d=so.findPermutation(p);
    wt(d);
    vector<string> sv;
    vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    // Solution so;
    // rd(a,k);
    // auto ans = so.;
    // wt(ans);
    cout<<'\n';
    return 0;
}
#endif
