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

const ll inf=1e18;

struct S {
    ll sum;
    ll mxp, mxs, mxans;
    ll mnp, mns, mnans;

    S(int x = 0) : sum(x), mxp(std::max(0, x)), mxs(std::max(0, x)), mxans(max(0, x)), mnp(std::min(0, x)), mns(std::min(0, x)), mnans(min(0, x)) {}
};

S op(S a,  S b) {
    S res;
    res.sum = a.sum + b.sum;
    res.mxp = std::max(a.mxp, a.sum + b.mxp);
    res.mxs = std::max(b.mxs, b.sum + a.mxs);
    res.mnp = std::min(a.mnp, a.sum + b.mnp);
    res.mns = std::min(b.mns, b.sum + a.mns);
    res.mxans = max({a.mxans, b.mxans, a.mxs + b.mxp});
    res.mnans = min({a.mnans, b.mnans, a.mns + b.mnp});
    return res;
}
S e() {
    return S();
}

void ac_yyf(int tt) {
    rd(n);
    vector<int> a(2*n);
    rd(a);
    int mx=Mx(a);
    if(mx<=0){
        wt(mx,nl);
        return;
    }
    
    vector<S> ll1(n), lr(n + 1), rl(n), rr(n + 1);
    S l1(0), l2, r1, r2;
    f0(n) {
        ll1[i] = l1 = op(l1, S(a[i])); 
        lr[N - 1 - i] = l2 = op(S(a[n - 1 - i]), l2); 
        rl[i] = r1 = op(r1, S(a[i + n])); 
        rr[N - 1 - i] = r2 = op(S(a[2 * n - 1 - i]), r2);
    }
    long long c=-1e18;
    long long s=Sm(a);
    f0(n) {
        S tmp = op(op(rl[i], lr[i + 1]), op(ll1[i], rr[i + 1]));
        cmx(c, tmp.mxans);
        cmx(c, s - tmp.mnans);
    }
    wt(c,nl);
}

int main() {
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
