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
	vector<int> a(n);
	rd(a);
	map<int,int>mp;
	each(x,a)mp[x]++;
	set<int> s1,s2,s3;
	each(x,a){
		if(mp[x]==1){
			s1.insert(x);
		}else if(mp[x]%2==0){
			s2.insert(x);
		}else{
			s3.insert(x);
		}
	}

	string s(n,'A');

	// for(auto&x:s1)cout<<x<<" ";cout<<"\n";

	if(sz(s1)%2==0){
		cout<<"YES\n";
		int m=sz(s1);
		int k=0;
		for(int i=0;i<n;++i){
			if(s1.count(a[i])&&k<m/2) {
				s[i]='B';
				k++;
			}
		}
		cout<<s<<"\n";
		return;
	}

	int mx=0;
	int c;
	for(auto&[x,y]:mp){
		if(y>mx){
			mx=y;
			c=x;
		}
	}

	// dbg("y="/,y,c,'\n');

	if(mx<=2){
		cout<<"NO\n";
		return;
	}

	cout<<"YES\n";


	int m=sz(s1);
		int k=0;
		for(int i=0;i<n;++i){
			if(s1.count(a[i])&&k<m/2) {
				s[i]='B';
				k++;
			}
		}

		for(int i=0;i<n;++i){
			if(a[i]==c) {
				s[i]='B';
				break;
			}
		}
cout<<s<<"\n";


}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	// cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve(case_i);
	}
	return 0;
}
