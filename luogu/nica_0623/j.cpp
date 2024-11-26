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

void ac_yyf(int tt) {
    string t;
    rd(t);
    n=sz(t);
    bool ok=1;
    // vector<vector<int>> p(100)

    long long s2=0;
    for(int i=0;i+2<=n;++i){
        int a1=t[i]-'0',a2=t[i+1]-'0';
        if(a2%a1!=0)s2++;
    }
    for(int i=0;i+3<=n;++i){
        string s=t.substr(i,3);
        int s11=stoi(s.substr(0,1));
        int s22=stoi(s.substr(1,1));
        int s33=stoi(s.substr(2,1));
        int s23=stoi(s.substr(1,2));
        
        bool o=0;
        if(s22%s11==0||s33%s11==0||s23%s11==0)o=1;
        if(s33%s22==0)o=1;
        if(!o)s2++;
    }

    for(int i=0;i+4<=n;++i){
        string s=t.substr(i,4);
        bool o=0;
                    int s11=stoi(s.substr(0,1));
                    int s22=stoi(s.substr(1,1));
                    int s33=stoi(s.substr(2,1));
                    int s44=stoi(s.substr(3,1));

                    int s12=stoi(s.substr(0,2));
                    int s23=stoi(s.substr(1,2));
                    int s34=stoi(s.substr(2,2));

                    int s123=stoi(s.substr(0,3));
                    int s234=stoi(s.substr(1,3));

                    if(s22%s11==0||s33%s11==0||s44%s11==0||s23%s11==0||s34%s11==0||s234%s11==0)o=1;
                    if(s33%s22==0||s44%s22==0||s34%s11==0)o=1;
                    if(s44%s33==0)o=1;
                    if(s34%s12==0)o=1;
                    // if()

                    if(o==0){
                        s2++;
                    }
    }

   wt(n*1ll*(n-1)/2-s2,nl);
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
