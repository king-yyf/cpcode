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
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst ? (r=md-1):(l=md+1);} else fst ? (l=md+1):(r=md-1);}
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

int m, q;
int x, y, k;
string  t;

#define pp pair<int,int>
const ll mod=998244353;
const int maxn=2e6+2;
const ll inf=0x3f3f3f3f3f3f3f3fLL;
#define lson (x<<1)
#define rson ((x<<1)|1)
int gcd(int a,int b){while(b){int t=a%b;a=b;b=t;}return a;}
int lcm(int a,int b){return a*b/gcd(a,b);}
typedef unsigned long long ull;

ull bit[maxn];
string s;
struct node{
    int l,r;
    ull sum1,sum2;
}my[maxn<<2];
int n;
void pushup(int x){
    my[x].sum1=my[lson].sum1+my[rson].sum1;
    my[x].sum2=my[lson].sum2+my[rson].sum2;
}
void build(int x,int l,int r){
    my[x].l=l;my[x].r=r;
    if(my[x].l==my[x].r){
        my[x].sum1=bit[l-1]*(s[l-1]-'a');
        my[x].sum2=bit[n-l]*(s[l-1]-'a');
        return;
    }
    int mid=(l+r)>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
    pushup(x);
}
ull one,two;
void update(int x,int pos,int val){
    if(my[x].l==my[x].r){
        my[x].sum1=bit[pos-1]*val;
        my[x].sum2=bit[n-pos]*val;
        return;
    }
    int mid=(my[x].l+my[x].r)>>1;
    if(pos<=mid)
        update(lson,pos,val);
    else
        update(rson,pos,val);
    pushup(x);
}
void query(int x,int l,int r){
    if(my[x].l>=l&&my[x].r<=r){
        one+=my[x].sum1;
        two+=my[x].sum2;
        return;
    }
    int mid=(my[x].l+my[x].r)>>1;
    if(l<=mid)query(lson,l,r);
    if(r>mid)query(rson,l,r);
}

void ac_yyf(int tt) {
    rd(n,k,s);
    s+=string(k,'a');
    int m=n,len=n;
    n=sz(s);
    build(1,1,n);

    while(k--){
        one=0;two=0;
        int x=1,y=len;
        query(1,1,len);
        if((x-1)>(n-y))two*=bit[(x-1)-(n-y)];
        else one*=bit[(n-y)-(x-1)];
        if(one==two){
             update(1,len,s[len-1]);
             s[len]=s[len-1];
             len++;
        }else{
            len/=2;
        }
    }
    wt(s.substr(0,len),nl);
}
const unsigned HASH_P = unsigned(-13337); // both P and (P - 1) / 2 are prime.

int main() {
    int T = 1;
    bit[0]=1;
    for(int i=1;i<maxn;++i)
        bit[i]=bit[i-1]*HASH_P;

    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}



