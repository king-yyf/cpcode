#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2;
int n, m, k;
const int mod=1e9+7;

template <typename T>
vector<int> kmp_table(const T &s) {
    int n = s.size(), k = 0;
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        while (k > 0 && !(s[i] == s[k])) k = p[k - 1];
        if (s[i] == s[k]) k++;
        p[i] = k;
    }
    return p;
}
template <typename T>
vector<int> kmp(const T &s, const T &t) {  // return s在t中所有出现下标
    vector<int> res, p = kmp_table(s);
    int n = s.size(), m = t.size(), k = 0;
    for (int i = 0; i < m; ++i) {
        while (k && (k == n || !(t[i] == s[k]))) k = p[k - 1];
        if (t[i] == s[k]) k++;
        if (k == n) res.push_back(i - n + 1);
    }
    return res;
}
using LL=long long;
struct Matrix
{
    LL m[N][N];
} ;
Matrix A;
Matrix I = {1, 0, 0, 1};
Matrix multi(Matrix a,Matrix b)
{
    Matrix c;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            c.m[i][j]  =0;
            for(int k=0; k<N; k++)
            {
                c.m[i][j] =(c.m[i][j]+a.m[i][k] * b.m[k][j]%mod)%mod;
            }
        }
    }
    return c;
}
Matrix power(Matrix A,LL n)
{
    Matrix ans = I, p = A;
    while(n>0)
    {
        if(n & 1)
        {
            ans = multi(ans,p);
            n--;
        }
        n >>= 1;
        p = multi(p,p);
    }
    return ans;
}

class Solution {
public:
    int numberOfWays(string s, string t, long long k) {
        int n=sz(s);
        string s1=s+s;
        auto p=kmp(t,s1);
        int x=0,y=0;
        each(c,p)if(c<n)x++;
        y=n-x;
        ll p1,p2;
        if(s==t){
        	p1=1,p2=0;
        }else {
        	p1=0,p2=1;
        }
        A.m[0][0]=x-1;
	    A.m[0][1]=x;
	    A.m[1][0]=y;
	    A.m[1][1]=y-1;
	    Matrix T=power(A,k);
        ll c1=(T.m[0][0]*p1+T.m[0][1]*p2)%mod;
        return c1;
    }
};

#ifdef sigma-yyf
int main(){
    Solution so;
    string s="ababab",t="ababab";
    int k=1;
    auto c=so.numberOfWays(s,t,k);
    wt(c,nl);
    return 0;
}
#endif
