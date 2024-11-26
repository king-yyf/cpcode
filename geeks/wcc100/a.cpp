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

vector<int> findMin(int n, int q, vector<int> &a, vector<int> &b, vector<int> &qs) {
    vector<long long > p;
    for (int i = 0; i < n; ++i) {
        if (a[i]>=b[i])p.push_back(a[i]-b[i]);
    }
    sort(p.rbegin(), p.rend());
    n=p.size();
    for (int i= 1; i < n; ++i)
    	p[i] += p[i-1];
    vector<int> ans(q, -1);
    for (int i = 0 ;i < q; ++i) {
    	auto it = lower_bound(p.begin(), p.end(),qs[i]);
    	if(it!=p.end()){
    		ans[i]=it-p.begin()+1;
    	}
    }
    return ans;
}

vector<int> checkIfPossible(int n) {
	vector<int> a{
		 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912
	};
	vector<int> b = {
		1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323,4782969,14348907,43046721,129140163,387420489
	};
	double c=log2(3.0);
	int n1=a.size(), m=b.size();
	for(int i=0;i<n1;++i){
		for(int j=0;j<m;++j){
			 double x=log2(a[i]*1.0)+log2(b[j]*1.0)/c;
			 if(abs(n-x)<1e-6){
			 	return {a[i],b[j]};
			 }
		}
	}
	return {-1};
}



long long findMaxSnacks(int n, int m, vector<vector<int>> &edges) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int x = edges[i][0] - 1, y = edges[i][1] - 1;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> siz(n), d(n);
    function<void(int, int)> dfs = [&](int u, int fa) {
        siz[u] = 1;
        for (int v : g[u]) if (v != fa) {
            d[v] = d[u] + 1;
            dfs(v, u);
            siz[u] += siz[v];
        }
    };
    dfs(0, -1);
    for (int i = 0; i < n; ++i) {
        d[i] = siz[i] - d[i] - 1;
    }
    wt(d);
    sort(d.rbegin(), d.rend());
    wt(d);
    return accumulate(d.begin(), d.begin() + n - m, 0ll);
}


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    // double x=log2(1e9),y=log2(3);
    // double z=x+x/y;
    // dbg(x,x/y,z,nl);

    // double x1=33554432,x2=14348907;
    // dbg(log2(x1),log2(x2)/y,nl);

    // {
    // 	long long y=1e9;
	// long long x=1;
	// while(x<=y){
	// 	cout<<x<<",";
	// 	x*=2;
	// }
	// wt(nl);
	// x=1;
	// while(x<=y){
	// 	cout<<x<<",";
	// 	x*=3;
	// }
    // }

    int n=5,m=2;
    vector<vector<int>> es{
        {1,2},{2,3},{3,4},{4,5}
    };

    // int n=5,m=3;
    // vector<vector<int>> es{
    // 	{1,2},{1,3},{3,4},{3,5}
    // };

    // int n=7,m=3;
    // vector<vector<int>> es{
    // 	{1,2},{1,3},{1,4},{2,5},{2,6},{3,7}
    // };

    auto ans=findMaxSnacks(n,m,es);
    wt(ans,nl);

    return 0;
}
