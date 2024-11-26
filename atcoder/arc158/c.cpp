#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define yn(cond) cout << ((cond) ? "Yes" : "No") << "\n";
#define YN(cond) cout << ((cond) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
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
const double PI = acos(-1.0);
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

void ac_yyf(int tt) {
	cin >> n;
	vector<long long> a(n);

	auto get=[&](long long x){
		long long s=0;
		while(x){
			s+=x%10;x/=10;
		}
		return s;
	};
	long long s=0,c=0;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		s+=2*n*get(a[i]);
	}

	// if(tt==1){
	// 	vector<int> cc(10);
	// 	auto sum=[&](int a, int b){
	// 		int c=0,ans=0;
	// 		for(int i=0;i<5;++i){
	// 			c=(a%10+b%10+c)>9?1:0;
	// 			cc[i]+=c;
	// 			ans+=c;
	// 			a/=10,b/=10;
	// 		}
	// 		return ans;
	// 	};

	// 	int s=0;
	// 	for(int i=0;i<n;++i){
	// 		for(int j=0;j<n;++j){
	// 			int x=a[i],y=a[j];
	// 			int c=sum(x,y);
	// 			s+=c;
	// 			dbg(i,j,c,'\n');
	// 		}
	// 	}
	// 	dbg("s=",s,'\n');
	// 	wt(cc);
	// }

	int m=18;
	vector<vector<int>> p(m,vector<int>(10));

	for(int i=0;i<n;++i){
		long long x=a[i];
		int k=0;
		while(x){
			int d=x%10;
			p[k++][d]++;
			x/=10;
		}
	}
	// for(int i=0;i<4;++i){
	// 	wt(p[i]);
	// }

	long long ans=s;
	// wt(ans,'\n');
	s=0;


	for(int i=0;i<n;++i){
		//a[i]的进位总数

		vector<int> b(m);
		long long x=a[i];
		int k=0;
		while(x){
			int d=x%10;
			b[k++]=d;
			x/=10;
		}
		long long c=0;
		long long lst=0;
		vector<long long> cnt(m);
		for(int j=0;j<m;++j){
			//b[j]
			long long c1=0,c2=0;
			for(int k=0;k<10;++k){
				if(b[j]+k<10){
					if(b[j]+k==9){
						c2+=p[j][b[j]]*1ll*p[j][k];
					}
				}else{
					c2+=p[j][b[j]]*1ll*p[j][k];
				}
			}
			// dbg(c1,c2,'\n');
			c1=c2;
			cnt[j]=c2;
			c+=c1;
		}
		
		s+=c;
	}
	
	// for(int i=0;i<m;++i){
	// 	auto &v=p[i];
	// 	long long c1=0;
	// 	for(int j=0;j<10;++j){
	// 		for(int k=0;k<10;++k){
	// 			int x=v[j],y=v[k];
	// 			if(j+k<10){
	// 				if(j+k==9&&c>0){
	// 					c1+=x*1ll*y;
	// 				}
	// 			}else{
	// 				int d=j+k-10;
	// 				c1+=x*1ll*y;
	// 			}
	// 		}
	// 	}
	// 	// dbg("i=",i,"c=",c,'\n');
	// 	s+=c;
	// 	c=c1;
	// }

	// dbg(ans,s,9*s,'\n');

	// cout<<s<<'\n';
	wt(ans-9*s,'\n');
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
