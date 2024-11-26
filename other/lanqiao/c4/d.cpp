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
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;
// 1,2,7,9,13,15,16,17


void ac_yyf(int tt) {
    ll s,q;
    int z;
    rd(x,y,z);
    rd(q);
    const int N=1e5;
    const ll M=1e12;
    vector<long long> a{3};
    vector<int> c{x,y,z};
    sort(all(c));
    x=c[0],y=c[1],z=c[2];
    if(y==1){
    	// dbg(x,y,z,"xxx1\n");
    	// return;
    	ll d=1;
    	ll n1=1;
    	for(;;n1++){
    		d*=z;
    		if(d>M)break;
    	}
    	n1++;
    	vector<long long> p(n1+1);
    	p[0]=1;
    	f1(n1)p[i]=p[i-1]*z;
    	f0(n1+1){
    		a.push_back(2+p[i]);
    	}

    }else if(x==1){
    	// dbg(x,y,z,"xxx2\n");
    	// return;
    	ll d1=1,d2=1;
    	int n1=1,n2=1;
    	for(;;n1++){
    		d1*=y;
    		if(d1>M) break;
    	}
    	for(;;n2++){
    		d2*=z;
    		if(d2>M) break;
    	}
    	n1++,n2++;
    	vector<long long> p1(n1+1),p2(n2+1);
    	p1[0]=p2[0]=1;
    	for(int i=1;i<=n1;++i)
    		p1[i]=p1[i-1]*y;
    	for(int i=1;i<=n2;++i)
    		p2[i]=p2[i-1]*z;

    	for(int i=0;i<=n1;++i){
    		for(int j=0;j<=n2;++j){
    			a.push_back(p1[i]+p2[j]+1);
    		}
    	}
    }else{
    	// dbg(x,y,z,"xxx3\n");
    	// return;
    	ll d1=1,d2=1,d3=1;
    	int n1=1,n2=1,n3=1;
    	for(;;n1++){
    		d1*=x;
    		if(d1>M) break;
    	}
    	for(;;n2++){
    		d2*=y;
    		if(d2>M) break;
    	}
    	for(;;n3++){
    		d3*=z;
    		if(d3>M) break;
    	}
    	n1++,n2++;n3++;
    	vector<long long> p1(n1+1),p2(n2+1),p3(n3+1);
    	p1[0]=p2[0]=p3[0]=1;
    	for(int i=1;i<=n1;++i)
    		p1[i]=p1[i-1]*x;
    	for(int i=1;i<=n2;++i)
    		p2[i]=p2[i-1]*y;
    	for(int i=1;i<=n3;++i)
    		p3[i]=p3[i-1]*z;

    	for(int i=0;i<=n1;++i){
    		for(int j=0;j<=n2;++j){
    			for(int k=0;k<=n3;++k){
    				a.push_back(p1[i]+p2[j]+p3[k]);
    			}
    		}
    	}
    }
    set<ll> t(all(a));
    // wt(sz(a));
    // f0(20){
    // 	wt(a[i],' ');
    // }
    wt(nl);
    n=sz(a);
    f0(q){
    	rd(s);
    	auto p=t.lower_bound(s);
    	ll l,r;
    	for(l=s;;){
    		if(!t.count(l))break;
    		else l++;
    	}
    	auto it=t.upper_bound(l);
    	r=(*it);
    	wt(l,' ',r-l,nl);
    } 
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
