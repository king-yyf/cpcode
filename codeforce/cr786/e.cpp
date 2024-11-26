#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
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
    bool f=1;
	each(a, x) if(f==1) {wt(a); f=0;} else {cout<<' ';wt(a);}
}
const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n,m,x,y,k;
int a[N],b[N];
void solve(){
	cin>>n;
	mst(a,0);
	f1(n){
		cin>>a[i];
		b[i]=a[i];
	}
	sort(b+1,b+1+n);
	int ans=(b[1]+1)/2+(b[2]+1)/2;
	f1(n){
		
		if(i>1&&i<n){
			// vector<int> v{a[i-1],a[i+1],(a[i]+1)/2};
			// sor(v);
			int t=max(a[i-1],a[i+1]);
			ans=min(ans,t);
		}
		if(i>1){
			x=a[i-1],y=a[i];
			int c=(x+y+2)/3;
			ans=min(ans,c);
		}
		// cout<<"i="<<i<<", ans="<<ans<<"\n";

	}
	wt(ans,'\n');
}

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> s1,s2;
        each(s,logs){
        	int p=s.find(' ');
        	if(s[p+1]>='0'&&s[p+1]<='9') s2.push_back(s);
        	else s1.push_back(s);
        }
        sort(all(s1),[&](auto x,auto y){
        	int p1=x.find(' '),p2=y.find(' ');
        	string s=x.substr(p1+1),t=y.substr(p2+1);
        	if(s!=t) return s<t;
        	return x.substr(0,p1)<y.substr(0,p2);
        });
        vector<string> ans(all(s1));
        each(s,s2)ans.push_back(s);
        return ans;
    }
};

int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	// cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve();
	}
	return 0;
}
