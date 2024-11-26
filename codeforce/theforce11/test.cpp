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
const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

long long arith_seq_sum(long long a1, long long d, long long n) {
    return a1 * n + n * (n - 1) * d / 2;
}

/*
n=5
0 1 0 1 0 1 0 1

0 0 1 1 0 0 1 1

0 0 0 0 1 1 1 1


1: 2
1: 3
1: 2
3个1: 1

001
010
011
100
101
110
111

3*x-2 + 3(x-2)-2 + 3(x-4)-2


3x-2 3x-8 3x-14







*/

vector<int> get(int n){
	long long ans = 0;
    int x = 31 - __builtin_clz(n);
    vector<int> a(6);
    for (int i = 0; i <= x; i++){
        int c = 1 << i, cnt = 0;
        int p = (n + 1) / c;
        cnt = (p / 2) * c;
        int d = (n + 1) % c;
        if (p % 2 != 0) cnt += d;
        // ans = (ans + cnt) % 1000000007;
        a[i]=cnt;
    }
    return a;
}

// 0 2 10 14 38 48 88 104 192 218 330 366 510 560 736 800 1136 1218 1594 1694 2118 2240 2712 2856 3408 3578 4186 4382 5054 5280
void ac_yyf(int tt) {
    for(int i=1;i<=30;++i){
    	vector<int> a(i);
    	for(int j=0;j<i;++j)a[j]=j;
    	int s=0;
    	vector<int> b(6);
    	for(int l=1;l<=i;++l){
    		for(int j=0;j+l<=i;++j){
    			int k=j+l-1;
    			int c=0;
    			for(int p=j;p<=k;++p)c^=a[p];
    				for(int t=0;t<6;++t){
    					b[t]+=((c>>t)&1);
    				}
    				s+=c;
    		}
    	}
    	auto p=get(i-1);
    	dbg(i,s,nl); wt(b); wt(p);wt(nl);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
