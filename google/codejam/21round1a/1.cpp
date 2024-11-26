#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
#define f1(e) for(int i=0;i<(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,b,e) for(int i=(b);i<(e);++i)
#define f4(i,b,e,s) for(int i=(b); (s)>0?i<(e):i>(e); i+=(s))
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
const int N = 100 + 5;

int n,m,x,y,k;
string a[N];
int get(string s,string t){
	int n=s.size(),m=t.size();
	if(n>m)return 1;
	if(n<m) return -1;
	if(n==m){
		if(s>t)return 1;
		if(s<t) return -1;
	}
	return 0;
}
void solve(){
	cin>>n;
	f1(n)cin>>a[i];
	int c=0;
	for(int i=1;i<n;++i){
		string &s=a[i],&t=a[i-1];
		int f=get(s,t);
		if(f>0) continue;
		if(f==0){
			s+='0';
			c++;
			continue;
		}
		int m1=sz(s),m2=sz(t);
		if(m1<m2){
			string s1=t.substr(0,m1);
			if(s>s1){
				s+=string(m2-m1,'0');
				c+=m2-m1;
			}else if(s<s1){
				s+=string(m2-m1+1,'0');
				c+=m2-m1+1;
			} else {
				if(t.substr(m1)==string(m2-m1,'9')) {
					s+=string(m2-m1+1,'0');
					c+=m2-m1+1;
				}else {
					string s3=t;
					int j=m2-1;
					while(j>=0 &&s3[j]=='9')j--;
					s3[j]=char(s3[j]+1);
					for(int k=j+1;k<m2;++k)s3[j]='0';
					s=s3;
					c+=m2-m1;
				}
			}
		} else if(m1 == m2){
			s=s+'0';
			c++;
		}
	}
	cout<<c<<"\n";
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
