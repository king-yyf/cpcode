#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize(3)
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#pragma GCC diagnostic error "-fwhole-program"
#pragma GCC diagnostic error "-fcse-skip-blocks"
#pragma GCC diagnostic error "-funsafe-loop-optimizations"
#pragma GCC diagnostic error "-std=c++17"

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

const int mod = 998244353; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 1e6 + 5;
struct w {
    int x;  int y;
    bool operator < (const w& o) const {
        return x!=o.x ? x<o.x : y<o.y;
    }
};

int n,m,x,y,k,q;
int tr[N];

void add(int x,int c){
	for(int i=x;i<=m;i+=i&-i) tr[i]+=c;
}

int ask(int c){
	int s=0;
	for(int i=c;i>0;i-=i&-i)s+=tr[i];
	return s;
}

void read(int &x)//'&'表示引用，也就是说x是一个实参，在函数中改变了x的值就意味着在外面x的值也会被改变
{
    x=0;//归零（这就是潜在bug，有可能传进来时x没有归零）
    char s=getchar();//读入第一个字符
    while(s<'0'||s>'9')//不是数字字符
    {
        s=getchar();//继续读
    }
    while(s>='0'&&s<='9')//是字符（一旦不是字符就意味着输入结束了）
    {
        x=x*10+s-'0';
        s=getchar();
    }
}


// int mp[N];

vector<int> a[1000004];
void solve(){
	rd(n,k);
	set<int> s;
	f0(n){
		read(m);
		a[i].resize(m);
		f2(j,m){
			read(x);
			a[i][j]=x;
			s.insert(x);
		}
	}
	s.insert(k);
	unordered_map<int, int> mp;
	m=sz(s);
	int i=1;
	for(auto&x:s){
		mp[x]=i++;
	}
	
	long long c=0;
	int z=mp[k];
	int mx=0,p=0;
	for(int i=0;i<n;++i){
		for(auto&d:a[i]){
			if(d>=k){
				c=(c+p)%mod;
			}
			else{
				if(mx+d<k)continue;
				if(mp.count(k-d)){
					x=mp[d],y=mp[k-d];
					c=(c+ask(m)-ask(y-1))%mod;
				}else{
					auto it=s.lower_bound(k-d);
					y=mp[*it];
					x=mp[d];
					c=(c+ask(m)-ask(y-1))%mod;
				}
				
			}
		}
		p+=sz(a[i]);
		for(auto&d:a[i]){
			mx=max(mx,d);
			add(mp[d],1);
		}
	}
	printf("%lld\n", c);
}
int main(){
	// ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	// cout<<fixed<<setprecision(20);
	int T=1;
	// cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve();
	}
	return 0;
}
