#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
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

int n,m,x,y,k,q;
void solve(int tt){
	rd(n);

	// for(int i=3;i<=9;++i){
	// 	vector<int> a;
	// 	vector<int> b;
	// 	int t=0;
	// 	f2(j,i) a.push_back(j+1);
	// 	do{
	// 		int s=0;
	// 		f2(j,i){
	// 			s+=lcm(j+1,a[j]);
	// 		}
	// 		if(s>t){
	// 			t=s;
	// 			b=a;
	// 		}
	// 	}while(next_permutation(all(a)));
	// 	dbg("i=",i,"t=",t,'\n');
	// 	wt(b);

	// 	vector<int> c;
	// 	f2(j,i) c.push_back(j+1);

	// 	if(i%2==0){
	// 		for(int j=0;j<i;j+=2) swap(c[j],c[j+1]);
	// 	}else{
	// 		c[0]=1,c[1]=3,c[2]=2;
	// 		for(int j=3;j<i;j+=2){
	// 			swap(c[j],c[j+1]);
	// 		}
	// 	}
	// 	int s=0;
	// 	f2(j,i){
	// 		s+=lcm(j+1,c[j]);
	// 	}
	// 	dbg("s=",s,'\n');
	// }
	vector<int> a(n);
	f0(n)a[i]=i+1;
	if(n==1){
		cout<<1<<"\n";
		return;
	}
	if(n%2==0){
		for(int i=0;i<n;i+=2)swap(a[i],a[i+1]);
	}else{
		a[0]=1,a[1]=3,a[2]=2;
		for(int i=3;i<n;i+=2){
			swap(a[i],a[i+1]);
		}
	}
	wt(a);
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve(case_i);
	}
	return 0;
}
