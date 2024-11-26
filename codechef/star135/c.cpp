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
constexpr int N = 2e5 + 5;
int n, m, q;
int x, y, k;
string s, t;

template <typename T, class LF, class RF>
void monoStack(vector<T> &a, vector<int> &lt, vector<int> &rt, LF F1, RF F2) {
    int n = a.size();
    lt.assign(n, -1), rt.assign(n, n);
    stack<int> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && F1(a[i],a[sk.top()])) {
            rt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    sk = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && F2(a[i],a[sk.top()])) {
            lt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
}
template <typename T>  // 左右第一个更小的数，即以当前元素为最小值的区间
void le_le(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, less<T>(), less<T>());
}
template <typename T>  // 左右第一个更小的数，右侧是小于等于
void le_le_eq(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, less<T>(), less_equal<T>());
}
template <typename T> // 左右第一个更大的数，即以当前元素为最大值的区间
void gt_gt(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, greater<T>(), greater<T>());
}
template <typename T> // 左右第一个更大的数，右侧是大于等于
void gt_gt_eq(vector<T> &a, vector<int> &lt, vector<int> &rt) {
    monoStack(a, lt, rt, greater<T>(), greater_equal<T>());
}


void solve(int tt) {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    vector<int> lmx, rmx;
    gt_gt_eq(a, lmx, rmx);
    long long s1 = 0;
    for (int i = 0; i < n; ++i) {
    	int x1 = i - lmx[i], x2 = rmx[i] - i;
    	s1 += x1 * 1ll * x2 * (a[i] + 1);
    }
    map<int, vector<int>> mp;
    for (int i = 0; i < n; ++i) {
    	mp[a[i]].push_back(i);
    }
    for (auto &[k, v] : mp) {
    	long long s2 = n * 1ll * (n + 1) / 2;
    	int m = v.size();
    	for (int i = 0; i < m - 1; ++i) {
    		int d = v[i + 1] - v[i] - 1;
    		s2 -= d * 1ll * (d + 1) / 2;
    	}
    	if (v[0] > 0) s2 -= v[0] * 1ll * (v[0] + 1) / 2;
    	if (v[m - 1] < n - 1) {
    		s2 -= (n - v[m - 1]) * 1ll * (n - 1 - v[m - 1]) / 2;
    	}
    	s1 -= s2;
    }
    cout << s1 << "\n";
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
