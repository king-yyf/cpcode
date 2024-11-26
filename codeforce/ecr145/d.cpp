#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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
#define yn(o) cout << ((o) ? "Yes" : "No") << "\n";
#define YN(o) cout << ((o) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
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

const int mod = 1e9+7; // 998244353;
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

int lengthOfLIS(string & nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
        auto it = upper_bound(res.begin(), res.end(), nums[i]);
        if (it == res.end()) res.push_back(nums[i]);
        else *it = nums[i];
    }
    return res.size();
}
void ac_yyf(int tt) {
    rd(s);
    while(sz(s)&&s.back()=='1') s.pop_back();
    rev(s);
    while(sz(s)&&s.back()=='0') s.pop_back();
    rev(s);
    int x=lengthOfLIS(s);
    n=sz(s);
    vector p(n+1,vector<int> (2));
    f0(n){
        p[i+1][0]=p[i][0];
         p[i+1][1]=p[i][1];
        if(s[i]=='0'){
            p[i+1][0]++;
        }else p[i+1][1]++;
    }
    

    long long m1=1000000000000ll,m2=m1+1;

    int y=n-x;
    long long c=m2*y;
    for(int i=0;i<n-1;++i){
        if(s[i]=='1'&&s[i+1]=='0'){
            int s1=p[i+2][0];
            int s2=p[n][1]-p[i][1];
            if(s1+s2>x){
                y=n-(s1+s2);
                c=m1+y*m2;
                // c-=m2;
                // c--;
                break;
            }
        }
    }
    wt(c,'\n');
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
