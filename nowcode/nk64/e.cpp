#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define fr(i,a,b) for (int i=(a);i<(b);i++)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define yn(cond) if (cond) cout<<"Yes\n"; else cout << "No\n";
#define YN(cond) if (cond) cout<<"YES\n"; else cout << "NO\n";
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<A>& x) {wt(x);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI = acos(-1.0);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> a;
    FenwickTree(int n) : n(n), a(n) {}
    FenwickTree(vector<T> &A) : FenwickTree((int)A.size()) {
        for (int i = 0; i < n; ++i) add(i, A[i]);
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    T ask(int x) {
        T ans = 0;
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T ask(int l, int r) { //sum[l..r]
        if (l > r) return 0;
        return ask(r) - ask(l - 1);
    }
};


void solve(int tt) {
    rd(n,m,k);
    vector<int> a(n);
    FenwickTree<int> f(n);
    rd(a);
    vector<int> c(n);
    f0(n){
    	if(a[i]==0){
    		c[i]=a[i]|1;
    		if(i>=k+1){
    			c[i-k-1]=c[i-k-1]|2;
    		}
    	}
    }
    f0(n){
    	if(c[i]>0){
    		f.add(i,1);
    	}
    }

    for(int _=0;_<m;++_){
    	cin>>x>>y;
    	x--;

    	if(y!=0) {
    		if(x<=n-2-k){
	    		if( (c[x]&1)==1 ){
	    			c[x]=c[x]^1;
	    			if(c[x]==0){
	    				f.add(x,-1);
	    			}
	    		}
	    	}
	    	if(x>=k+1){
	    		if ((c[x-k-1]>>1)&1){
	    			c[x-k-1]=c[x-k-1]^2;
	    			if(c[x-k-1]==0){
	    				f.add(x-k-1,-1);
	    			}
	    		}
	    	}
    	}else{
    		if(x<=n-2-k){
	    		if(c[x]==0){
    				f.add(x,1);
    			}
    			c[x]=c[x]|1;
	    	}
	    	if(x>=k+1){
	    		if(c[x-k-1]==0){
    				f.add(x-k-1,1);
    			}
    			c[x-k-1]=c[x-k-1]|2;
	    	}
    	}

    	// wt(c);

    	cout<<f.ask(n-2-k)<<"\n";
    	
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
