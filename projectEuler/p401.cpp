#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://projecteuler.net/problem=401


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
const char nl = '\n';



const int mod = 1e9;

using i128 = __int128;
i128 read(){
    __int128 x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)&&ch!='-')ch=getchar();
    if(ch=='-')f=-1;
    while(isdigit(ch))x=x*10+ch-'0',ch=getchar();
    return f*x;
}

void print(i128 x){
    if(x<0)putchar('-'),x=-x;
    if(x>9)print(x/10); 
    putchar(x%10+'0');
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    auto f = [&](ll n) {
		i128 x = n;
		i128 s = x * (x + 1) / 2;
		auto y = 2 * x + 1;

		auto d = s / 3;
		if (d * 3 == s) return ((d % mod) * y) % mod;
		return (s % mod) * (y / 3) % mod;
    };

    long long n = 1e15;
    long long s = 0;
    int t = sqrtl(n);

    for (ll i = 1; i <= t; ++i) {
    	auto x = (n / i) % mod;
    	auto y = i * i % mod;
    	s += x * y % mod;
    }

    for (ll j = 1; j <= n / (t + 1); ++j) {
    	auto x = n / j, y  = n / (j + 1);
    	long long s0 = 0;
    	auto s1 = f(x);
    	auto s2 = f(y);
    	if (s1 < s2) s1 += mod;
    	s0 += s1 - s2;
    	s += (j * s0) % mod;
    }
    s %= mod;

    cout << s << "\n";
    return 0;
}
