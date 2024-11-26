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

long long arith_seq_sum(long long a1, long long d, long long n) {
    return a1 * n + n * (n - 1) / 2 * d;
}
#define int long long
void spiralOrder(vector<vector<int>>& mx) {
    int m = mx.size(), n = m ? mx[0].size() : 0;
    int u = 0, d = m - 1, l = 0, r = n - 1, p = 0;
    while (u <= d && l <= r) {
        for (int i = l; i <= r; ++i) mx[u][i] = ++p;
        if (++u > d) break;
        for (int i = u; i <= d; ++i) mx[i][r] = ++p;
        if (--r < l) break;
        for (int i = r; i >= l; --i) mx[d][i]=++p;
        if (--d < u) break;
        for (int i = d; i >= u; --i) mx[i][l]=++p;
        ++l;
    }
}

void ac_yyf(int tt){
    ll n,m,x;
    rd(n,m,x);
    if(n*1ll*m<=100) {
        vector<vector<int>> f(n,vector<int>(m));
        spiralOrder(f);
        f0(n)f2(j,m)if(f[i][j]==x){
            wt(i+1,' ',j+1,nl);
            return;
        }
    }
    int t=min(n,m);

    if(n==1) {
        wt("1 ",x,nl);
        return;
    }

    if(m==1) {
        wt(x, " 1",nl);
        return;
    }

    int g=(t+1)/2;
    ll a1=n+n+m+m-4;
    ll a2=n-2+n-2+m-2+m-2-4;
    ll d=a2-a1;

    if(x<=a1){
        if(x<=m){
            wt("1 ",x,nl);
        }else if(x<=m+n-1){
            wt(x-m+1,' ',m,nl);
        }else if(x<=m+n-1+m-1){
            ll d=x-(m+n-1);
            wt(n,' ',m-d,nl);
        }else{
            ll d=x-(m+n-1+m-1);
            // dbg(d,n,m);
            wt(n-d,' ',1,nl);
        }
        return;
    }
    ll s=0;
    auto c=b_search<ll>(1,g,0,[&](ll t1){
        ll s1=arith_seq_sum(a1,d,t1);
        return s1<x;
    });
    s=arith_seq_sum(a1,d,c);

    // if(x==n*1ll*m&&(t&1)){
    //     wt(c+1,' ',c+1,nl);
    //     return;
    // }

    // x在第c+1圈。

    ll left=x-s;

    // 第c+1圈的第一个数字为 s+1
    // 第c+1圈的长宽分别为n1,m1

    int n1=n-2*c;
    int m1=m-2*c;

    if(left<=m1) {
        wt(c+1,' ',left+c,nl);
    }else if(left<=m1+n1-1) {
        ll d=left-m1;
        wt(c+1+d,' ',m-c,nl);
    }else if(left<=m1+n1-1+m1-1){
        ll d=left-(m1+n1-1);
        wt(n-c,' ',m-c-d,nl);
    }else{
        ll d=left-(m1+n1-1+m1-1);
        wt(n-c-d,' ',c+1,nl);
    }

    // dbg(a1,a2,nl);
}
signed main() {
    int T = 1, fun_type = 0;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << (ac_yyf(cas) ? "Alice" : "Bob") << '\n';
        // cout << (ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
