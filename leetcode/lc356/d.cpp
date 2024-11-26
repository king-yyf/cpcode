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
const int N = 2e5 + 5;
int n, m, k;

const int mod=1000000007;

void add(string &s) {
    int n=sz(s);
    for(int i=n-1;i>=0;--i){
        if(s[i]<'9'){
            s[i]=char(s[i]+1);
            for(int j=i+1;j<n;++j){
                s[j]='0';
            }
            break;
        }
    }
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

class Solution1 {
public:

    int get(string s){
        // sub(n);
        ll x=0;
        int n=sz(s);
        f0(n){
            x=((x*10)+s[i]-'0')%mod;
        }

        ll md=qpow(2,mod-2,mod);

        add(s);

        ll y=0;
        n=sz(s);

        f0(n){
            y=((y*10)+s[i]-'0')%mod;
        }

        long long c=(x*y)%mod;
        c=c*md%mod;

        return c;
    }
	
    int countSteppingNumbers(string l, string r) {
        ll c=get(r)-get(l);

        auto chk=[&](string s){
            n=sz(s);
            f0(n-1){
                if(abs(s[i+1]-s[i])!=1)return 0;
            }
            return 1;
        };

        if(chk(l))c--;
        c=(c%mod+mod)%mod;
        return c;
    }
};

class Solution{
public:
    int ans=0;
    void solve(int num,int n,int m){
        if(num>m) return;
        if(num>=n and num<=m) ans++;;
        
        
        int last=num%10;
        if(last==9)
        {
            solve(num*10+(last-1),n,m);
        }
        else if(last==0){
            solve(num*10+(last+1),n,m);
        }
        else{
            solve(num*10+(last+1),n,m);
            solve(num*10+(last-1),n,m);
        }
    }

    int steppingNumbers(int n, int m)
    {
        ans=0;
        // Code Here
         if(n==0) ans++;
        for(int i=1;i<=9;i++){
           
            solve(i,n,m);
        }
        return ans;
    }
};

#ifdef sigma-yyf
int main(){
    Solution so;
    f1(30){
       // string x=to_string(i);
       // add(x);
       // cout<<x<<' ';
       // for(int j=1;j<=i;++j){
       //  dbg(so.steppingNumbers(j,i));
       // }
        dbg(so.steppingNumbers(1,i));
       //  if(i%10==0)
       // cout<<'\n';
    }
    return 0;
}
#endif
