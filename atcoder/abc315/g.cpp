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
int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;


ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}

ll lcm(ll a, ll b) {
    return a / gcd(a,b) * b;
}

ll extend_gcd(ll a,ll b,ll&x,ll&y) {
    if(!b) {
        x = 1;
        y = 0;
        return a;
    }
    ll xt = 0, yt = 0;
    ll d = extend_gcd(b, a % b, xt, yt);
    x = yt;
    y = xt - yt * (a/b);
    return d;
}

ll cal(ll a,ll b,ll n) {    //计算ax+by == n的非负整数解组数
	// dbg(a,b,n,nl);
    ll x = 0,y = 0,d;
    d = extend_gcd(a,b,x,y);
    if(n % d != 0) {
        return 0;
    }
    x *= n / d, y *= n / d;
    ll LCM = lcm(a,b);
    // cmn(LCM,N);
    ll t1 = LCM / a, t2 = LCM / b;
    // cmn(t1,N);
    // cmn(t2,N);

    // dbg(x,y,t1,t2,LCM,nl);

    if(x<1) {
        ll num = (1-x) / t1;
        x += num * t1;
        y -= num * t2;
        if(x<1) {
            y -= t2;
            x += t1;
        }
    }
    if(y<1) {
        ll num = (1-y) / t2;
        y += num * t2;
        x -= num * t1;
        if(y<1) {
            y += t2;
            x -= t1;
        }
    }
    ll ans = x > 0 && y > 0;
    if(ans) {
        ans += min((x-1) / t1, ((n-1) / b - y) / t2);
        ans += min((y-1) / t2, ((n-1) / a - x) / t1);
    }
    if(n%b==0 && n/b<=N)ans--;
    // else if(n%a==0 && n/a<=N)ans--;
    return ans;
}

void ac_yyf(int tt) {
    ll x;
    vector<long long> v(3);
    rd(n,v,x);
    N=n;
    ll ans=0;
    sort(rall(v));
    ll a=v[1],b=v[2];
    int d=gcd(a,b);
    f1(n){
    	ll t=x-v[0]*i;
    	if(t<=0)break;
    	if(t%d!=0)continue;
    	ans+=cal(a,b,t);
    	// break;
    	// dbg("i=",i,"ans=",ans,nl);
    }
    wt(ans);
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
