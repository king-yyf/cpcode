#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

// https://yukicoder.me/problems/no/2495

/*
三个数组，从每个数组中选择一个子集，得到 sa,sb,sc，
设sa,sb,sc大小分别为 na,nb,nc
求 sum(sa)*nb+sum(sb)*nc+sum(sc)*na的最大值

+ 1<=数组长度<=1e5
+ -3e3<=a[i],b[i],c[i]<=3e3
*/

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

void ac_yyf(int tt) {
    int n,m,l;
    rd(n,m,l);
    vector<long long> a(n),b(m),c(l);
    rd(a,b,c);
    sort(rall(a));
    sort(rall(b));
    sort(rall(c));
    vector<long long> s,t,u;
    psum(s,a);
    psum(t,b);
    psum(u,c);

    auto get=[&](int i,int j, int k){
    	return s[i]*j+t[j]+k+u[k]*i;
    };

    auto b2 = [&](int i, int j) {
        int l3 = 0, r3 = l;
        while (r3 - l3 >= 3) {
            int ml3 = l3 + (r3 - l3) / 3;
            int mr3 = r3 - (r3 - l3) / 3;

            if (get(i, j, ml3) < get(i, j, mr3)) {
                l3 = ml3;
            } else {
                r3 = mr3;
            }
        }
        long long res = -1e18;
        f3(k, l3, r3 + 1) {
            cmx(res, get(i, j, k));
        }
        return res;
    };

    auto b1 = [&](int i) {
        int l2 = 0, r2 = m;
        while (r2 - l2 >= 3) {
            int ml2 = l2 + (r2 - l2) / 3;
            int mr2 = r2 - (r2 - l2) / 3;

            if (b2(i, ml2) < b2(i, mr2)) {
                l2 = ml2;
            } else {
                r2 = mr2;
            }
        }
        long long res = -1e18;
        f3(j, l2, r2 + 1) {
            cmx(res, b2(i, j));
        }
        return res;
    };

    int l1 = 0, r1 = n;
    while (r1 - l1 >= 3) {
        int ml1 = l1 + (r1 - l1) / 3;
        int mr1 = r1 - (r1 - l1) / 3;

        if (b1(ml1) < b1(mr1)) {
            l1 = ml1;
        } else {
            r1 = mr1;
        }

    }
    long long res = -1e18;
    f3(i, l1, r1 + 1) {
        cmx(res, b1(i));
    }
    wt(res,nl);
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
