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
#define ln "\n";
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class A> void rd(vector<A>& v);  // read vector
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
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;
struct w {
    int x;  int y;
    bool operator < (const w& o) const {
        return x!=o.x ? x<o.x : y<o.y;
    }
};

string intToA(int n, int radix) {
    string ans = "";
    do {
        int t = n % radix;
        if (t >= 0 && t <= 9) ans += t + '0';
        else ans += t - 10 + 'a';
        n /= radix;
    } while(n);
    reverse(ans.begin(), ans.end());
    return ans;
}

int n,m,x,y,k,q;
void solve(){
	cin>>n>>x;

	if(n<=1){
		cout<<"0\n";
		return;
	}

	ll a=0,b=1;
	

	string ss=intToA(n,x);
	int k=0;
	int one=0,zo=0;
	for(auto&c:ss){
		k+=c-'0';
		if(c=='0')zo++;
		else if(c=='1')one++;
	}
	vector<int> v;
	for(int i=sz(ss)-1;~i;--i){
		if(ss[i]>'0') v.push_back(sz(ss)-1-i);
	}
	int t=0;
	int p=v.back();
	// dbg(ss);wt('\n');
	// wt(v);

	if(zo==sz(ss)-1&&one==1){
		cout<<p<<"\n";
		f0(p){
			cout<<"2 b\n";
		}
		return;
	}

	cout<<p+k<<"\n";

	// for(int j=sz(v)-1;)
	// deg(ss)
	// wt(v);
	for(auto& x:v){
		int c=x-t;
		for(int i=0;i<c;++i){
			cout<<"2 b\n";
		}
		int s1=ss[sz(ss)-1-x]-'0';
		for(int i=0;i<s1;++i)
			cout<<"1 a\n";
		t=x;
	}

}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve();
	}
	return 0;
}
