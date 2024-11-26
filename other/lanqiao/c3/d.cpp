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
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
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
const int N = 1000 + 5;

int n, m, q;
int x, y, k;
string s, t;

ll f[N][N][5];

void ac_yyf(int tt) {
    rd(n,m,q);
    vector<vector<int>> a(n,vector<int>(m));
    f0(n)f2(j,m)rd(a[i][j]);
    const ll inf=1e18;
    f0(n)f2(j,m)f2(k,q+1)f[i][j][q]=-inf;
    f[0][0][q]=a[0][0];
    for(int i=1;i<m;++i){
    	int d=gcd(a[0][i],a[0][i-1]);
    	if(d==1){
    		f2(j,q) {
    			f[0][i][j]=f[0][i-1][j+1]+a[0][i];
    		}
    	}else{
    		f2(j,q+1){
    			f[0][i][j]=f[0][i-1][j]+a[0][i];
    		}
    	}
    }
    f1(n-1) {
    	int d=gcd(a[i][0],a[i-1][0]);
    	if(d==1){
    		f2(j,q) {
    			f[i][0][j]=f[i-1][0][j+1]+a[i][0];
    		}
    	}else{
    		f2(j,q+1){
    			f[i][0][j]=f[i-1][0][j]+a[i][0];
    		}
    	}
    }
    for(int i=1;i<n;++i){
    	for(int j=1;j<m;++j){
    		int d=gcd(a[i][j],a[i-1][j]);
    		if(d==1) {
    			for(int k=0;k<q;++k){
    				cmx(f[i][j][k],f[i-1][j][k+1]+a[i][j]);
    			}
    		}else{
    			for(int k=0;k<=q;++k){
    				cmx(f[i][j][k],f[i-1][j][k]+a[i][j]);
    			}
    		}

    		d=gcd(a[i][j],a[i][j-1]);
    		if(d==1) {
    			for(int k=0;k<q;++k){
    				cmx(f[i][j][k],f[i][j-1][k+1]+a[i][j]);
    			}
    		}else{
    			for(int k=0;k<=q;++k){
    				cmx(f[i][j][k],f[i][j-1][k]+a[i][j]);
    			}
    		}
    	}
    }

    ll c=-inf;
    f0(q+1)cmx(c,f[n-1][m-1][i]);
    if(c<0){
    	wt(-1,nl);return;
    }
    wt(c);
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
