#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

int bct(long long x){return __builtin_popcountll(x);}
int lg2(int x){return x==0?0:31-__builtin_clz(x);} //x>=0, floor(log2(x)) 
long long fbs(function<bool(long long)> f, long long& lb, long long rb) {  // first true binary search
    while(lb<rb) {
		long long mb=(lb+rb)/2;
		f(mb)?rb=mb:lb=mb+1; 
	} 
	return lb;
}
long long lbs(function<bool(long long)> f, long long& lb, long long rb) {  // last true binary search
	while(lb<rb) {
		long long mb=(lb+rb+1)/2;
		f(mb)?lb=mb:rb=mb-1; 
	} 
	return lb;
}

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) { cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    for (int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];
}
const int mod = 1e9+7; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

long long MOD(long long a, long long m) {
    a %= m;
    return a >= 0 ? a : a + m;
}

long long inverse(long long a, long long m) {
    a = MOD(a, m);
    if (a <= 1) return a;
    return MOD((1 - inverse(m, a) * m) / a, m);
}

long long gcd(long long a, long long b) {
    a = abs(a), b = abs(b);
    while (b != 0) {
        a %= b;
        swap (a, b);
    }
    return a;
}
//扩展欧几里得，求x,y 使得 ax+by=gcd(a,b)
int exgcd(long long a, long long b, long long &x, long long &y) {
    if (!b){
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a/b) * x;
    return d;
}

long long fast (long long a, long long b, long long mod) {
    a %= mod;
    if (b < 0) a = inverse (a, mod), b = -b;
    long long ans = 1;
    while (b) {
        if (b & 1)ans = ans * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ans % mod;
}

const long long maxn = 50;
long long fac[maxn], facinv[maxn], inv[maxn];
void init() {
    fac[0] = 1;
    for (int i = 1; i < maxn; ++i)
        fac[i] = i * (fac[i - 1]) % mod;
    facinv[maxn - 1] = inverse(fac[maxn - 1], mod);
    for (int i = maxn - 2; i >= 0; --i){
        facinv[i] = facinv[i + 1] * (i + 1) % mod;
    }
    inv[1] = 1;
    for (int i = 2; i < maxn; i++)
        inv[i] = (mod - (long long) mod / i * inv[mod % i] % mod);
}
//求组合数 c[n,m]，调用之前需要先调用init().
long long com(int n, int m) {
    if (n < 0 || m < 0 || n < m)return 0;
    return fac[n] * facinv[m] % mod * facinv[n - m] % mod;
}


int n,m,x,y,k,q;
bool isp(string s,set<int> st){
	int n=sz(s);
	string t;
	for(int i=0;i<n;++i) if(!st.count(i)) t+=s[i];
	if(t=="") return 1;
	string s1=t;
	rev(t);
	return t==s1;
}
vector<vector<int>> res;
void dfs(vector<int>& nums, int u) {
    if (u >= nums.size()) {
        res.push_back(nums);
        return;
    }
    for (int i = u; i < nums.size(); ++i) {
        swap(nums[u], nums[i]);
        dfs(nums, u + 1);
        swap(nums[u], nums[i]);
    }
}

void solve(){
	cin>>n;
	string s;
	cin>>s;
	if(n<10){
		vector<int> a(n);
		f0(n)a[i]=i;
		res.clear();
		dfs(a, 0);
		long long c=0;
		long long cnt=res.size();
		for(auto&e:res){
			set<int> st;
			for(int i=0;i<n;++i){
				st.insert(e[i]);
				if(isp(s,st)) c++;
			}
		}
		long long xy=fast(cnt,mod-2,mod);
		// cout<<c<<" "<<cnt<<" ";
		cout<< (c * xy) % mod << "\n";
	}
	else{
		cout<< "0\n";
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
        cout << "Case #" << case_i << ": ";
		solve();
	}
	return 0;
}
