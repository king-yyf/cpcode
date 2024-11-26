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

template<typename T>
struct Dijkstra {
    using E = pair<T, int>;
    int n;
    vector<vector<E>> g;    // cost, to
    Dijkstra(int N) : n(N), g(N) {}

    void add_edge(int u, int v, T cost) {
        g[u].emplace_back(cost, v);
    }

    void add_bidir_edge(int u, int v, T cost) {
        add_edge(u, v, cost);
        add_edge(v, u, cost);
    }

    vector<T> dijkstra(int s) {  // unreachable : -1
        vector<T> d(n, T(-1)); 
        priority_queue<E, vector<E>, greater<E>> q;
        d[s] = 0;
        q.emplace(0, s);
        while (!q.empty()) {
            auto [cost, u] = q.top();
            q.pop();
            if (d[u] < cost) continue;
            for (auto &[c, v] : g[u]) {
                if (d[v] == T(-1) || d[u] + c < d[v]) {
                    d[v] = d[u] + c;
                    q.emplace(d[v], v);
                }
            }
        } 
        return d;
    }
};

template <typename T, class LF, class RF>
void monoStack(vector<T> &a, vector<int> &lt, vector<int> &rt, LF f1, RF f2) {
    int n = a.size();
    lt.assign(n, -1), rt.assign(n, n);
    stack<int> sk;
    for (int i = 0; i < n; ++i) {
        while(!sk.empty() && f1(a[i],a[sk.top()])) {
            rt[sk.top()] = i;
            sk.pop();
        }
        sk.push(i);
    }
    sk = stack<int>();
    for (int i = n - 1; i >= 0; --i) {
        while (!sk.empty() && f2(a[i],a[sk.top()])) {
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



void ac_yyf(int tt) {
    rd(n,m);
    vector<int> a(n);
    rd(a);

    Dijkstra<ll> d(n);

    f0(n-1){
    	d.add_edge(i,i+1,abs(a[i]-a[i+1]));
    }

    vector<int> l,r;
    gt_gt_eq(a,l,r);


    vector<ar3> v; 

    f0(n){
    	if(r[i]<n){
    		v.push_back({abs(a[i]-a[r[i]]),i,r[i]});
    	}
    }
    sort(all(v),[&](auto&x,auto &y){
    	return x[0]<y[0];
    });

    cmn(m,sz(v));
    f0(m){
    	d.add_edge(v[i][2],v[i][0],v[i][1]);
    }

    auto ds=d.dijkstra(n-1);
    wt(ds[n-1],nl);
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
