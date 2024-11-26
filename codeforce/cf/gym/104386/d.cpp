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
#define yes cout << "Yes\n"
#define YES cout << "YES\n"
#define no cout << "No\n"
#define NO cout << "NO\n"
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
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

const char nl = '\n';
const int N = 1e6 + 5,MX=1e6;


int n, m, q;
int x, y, k;
string s, t;

// mint f[N];
// 
// void ac_yyf(int tt) {
//     vector<int> a(25);
//     for(int i=1;i<25;++i){
//         int t=int(pow(i,1.0/3));
//         if(i%t==0) a[i]=1;
//     }
//     wt(a);
// }

ll get(ll x){
    return (x+1)*(x)/2;
}

ll cbt(ll x) {
    ll p=cbrtl(x)-1;
    while(p*p*p<=x)p++;
    p--;
    return p;
}

ll dp(ll x) {
    if(x==0) return 0;
    if(x<=7) return x;

    // dbg("x=",x,nl);

    ll p=cbt(x);

    ll c=3*get(p-1)+4*p-4;
    c+=(x-p*p*p)/p+1;
    return c;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int T = 1;

    // f[0]=0; f[1]=7;

    // for(int i=2;i<=MX;++i) {
    //     f[i]=f[i-1]+4+3*i;
    // }
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        // ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
        ll l,r;
        rd(l,r);
        wt(dp(r)-dp(l-1),nl);
    }
    return 0;
}
