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
int clg(ll x) {return x <= 1 ? 0 : 64 - __builtin_clzll(x - 1);}
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
// 1 ~ n 中第 k 位上 1 的个数, 0 <= n, 0 <= k <= 62
long long get(long long n, long long k){ 
    return (n + 1) / (1LL << k + 1) * (1LL << k) + max((n + 1) % (1LL << k + 1) - (1LL << k), 0LL);
}

long long  qpow(long long m, long long k, long long p) {
    long long res = 1 % p, t = m;
    while (k) {
        if (k&1) res = res * t % p;
        t = t * t % p;
        k >>= 1;
    }
    return res;
}

ll cal(ll n) {
    long long ans = 0;
    int x = 63 - __builtin_clzll(n);
    for (int i = 0; i <= x; i++){
        ll c = 1ll << i, cnt = 0;
        ll p = (n + 1) / c;
        cnt = (p / 2) * c;
        ll d = (n + 1) % c;
        if (p % 2 != 0) cnt += d;
        ans = (ans + cnt) % 1000000007;
    }
    return ans;
}

class Solution {
public:
    vector<int> findProductsOfElements(vector<vector<long long>>& qs) {
        n=sz(qs);
        vector<int> c(n);
        // dbg("fdjfd",nl);
        auto dd=[&](ll x){

        };
        f0(n){
            ll x1=qs[i][0],y1=qs[i][1],mod=qs[i][2];
            ll l1=0;
            ll l=0,r=1e15,a1=r;
            while(l<=r){
                ll md=(l+r)/2;
                ll d1=cal(md);
                if(d1>=x1+1){
                    a1=md;
                    l1=d1-x1;
                    r=md-1;
                }else l=md+1;
            }

            l=0,r=1e15;
            ll a2=r;
            ll l2=0;
            while(l<=r){
                ll md=(l+r)/2;
                ll d1=cal(md);
                if(d1>=y1+1){
                    a2=md;
                    r=md-1;
                    l2=d1-y1-1;
                }else l=md+1;
            }

            // if(a1==a2){
            //     ;
            //     // continue;
            // }

            

            l2=pct(a2)-l2;

            // dbg(a1,a2,l1,l2,nl);

            int d=clg(a2);

            if(a1==a2){
                int c1=1;
                int ccc=0,n2=pct(a1);
                for(int i=0;i<=d;++i){
                    if(a1>>i&1){
                        ccc++;
                        if(ccc>=n2-l1+1 && ccc<=l2){
                            c1=c1*1ll*((1ll<<i)%mod)%mod;
                        }
                    }
                }
                c[i]=c1;
                continue;
            }



            int c1=1;
            vector<int> pp(d+1);
            int cnt1=l1;
            for(int j=clg(a1);j>=0;--j){
                if(a1>>j&1){
                    cnt1--;
                    pp[j]++;
                }
                if(cnt1==0)break;
            }
            
            int cnt2=l2;
            for(int j=0;j<64;++j){
                if(a2>>j&1){
                    cnt2--;
                    pp[j]++;
                }
                if(cnt2==0)break;
            }
            // dbg(a1,a2,nl);
            for(int i=0;i<=d;++i){
                ll cu=1ll<<i;
                ll t=pp[i];
                if(a1+1<=a2-1){
                    ll x=a1+1,y=a2-1;
                    t+=get(y,i);
                    if(x>1)t-=get(x-1,i);
                }

                c1=c1*1ll*qpow(cu,t,mod);
                c1%=mod;
                
                // dbg(cu,t,nl);
            }
            c[i]=c1;
        }
        return c;
    }
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a,b;
    string s,t;
    vector<vector<long long>> qs{};
    int x,y,k;
    rd(x,y,k);
    qs.push_back({x,y,k});
    Solution so;
    auto d=so.findProductsOfElements(qs);
    wt(d[0],nl);
    vector<string> sv;
    vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    // Solution so;
    // rd(a,k);
    // auto ans = so.;
    // wt(ans);
    // cout<<'\n';
    return 0;
}
#endif
