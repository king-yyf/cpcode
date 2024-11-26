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

int n, m, q;
int x, y, k;
string s, t;

void ac_yyf(int tt) {
    int d;
    rd(n,d);
    vector<int> b(n),c(n),a(n);
    rd(b,c);
    if(b[0]!=c[0]) {
    	wt("NO\n");
    	return;
    }
    vector<int> vis(n);

    priority_queue<int> q1;
    priority_queue<int, vector<int>, greater<int>> q2; 

    a[0]=b[0];
    q1.push(a[0]);
    q2.push(a[0]);
    vis[0]=1;
    f1(n-1) {
    	int mx=q1.top(),mn=q2.top();
    	if(b[i]<mx || c[i]>mn || c[i]>b[i]){
    		wt("NO\n");
    		return;
    	}
    	if(b[i]>mx) {
    		a[i]=b[i];
    		q1.push(a[i]);
    		q2.push(a[i]);
    		vis[i]=1;
    	}
    	if(c[i]<mn){
    		if(vis[i]){
    			wt("NO\n");
    			return;
    		}
    		vis[i]=1;
    		a[i]=c[i];
    		q1.push(a[i]);
    		q2.push(a[i]);
    	}
    }

    vector<int> p(n,n);
    for(int i=n-1;i>=0;--i){
    	if(vis[i]){
    		p[i]=i;
    	}else{
    		if(i<n-1)p[i]=p[i+1];
    	}
    }

    int lst=a[0];
    f1(n-1) {
    	if(vis[i]) {
    		lst=a[i];
    		continue;
    	}
    	int t=p[i];
    	if(t==n) {
    		a[i]=a[i-1];
    		lst=a[i];
    		continue;
    	}

    	int x=lst,y=a[t];

    	if(x>y) {
    		ll df=x-y;
    		int p2=t-i;
    		ll z=df/p2;
    		a[i]=lst+z;
    		cmn(a[i],b[i]);
    		cmx(a[i],c[i]);
    	}else{
    		ll df=y-x;
    		int p2=t-i;
    		ll z=df/p2;
    		a[i]=lst+z;
    		cmn(a[i],b[i]);
    		cmx(a[i],c[i]);
    	}

    	lst=a[i];
    }

    vector<int> p1(n),p2(n);
    p1[0]=p2[0]=a[0];

    f1(n-1){
    	p1[i]=max(p1[i-1],a[i]);
    	p2[i]=min(p2[i-1],a[i]);
    }

    // wt(a);

    // wt(b);
    // wt(p1);

    // wt(c);
    // wt(p2);


    if(p1!=b||p2!=c){
    	wt("NO\n");
    		return;
    }

    f0(n-1){
    	if(abs(a[i]-a[i+1])>d){
    		wt("NO\n");
    		return;
    	}
    }

    wt("YES\n");
    wt(a);

}
int main() {
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
