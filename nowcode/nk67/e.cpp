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

/*
接下来n天的价格以同等概率为a[i]或b[i],采取最有
*/
void ac_yyf(int tt) {
    rd(n);
    vector<int> a(n),b(n);
    rd(a);rd(b);

    // int mn=1e9,mx=-1;
    // f0(n){
    // 	if(a[i]>b[i])swap(a[i],b[i]);
    // 	mn=min(mn,b[i]);
    // 	mx=max(mx,a[i]);
    // }

    // // vector<double> c(n+1,1e9);
    // double s=0;
    // for(int i=n-1;i>=0;--i){
    // 	if(a[i]>mn){
    // 		c[i]=a[i+1];
    // 	}else{
    // 		s+=a[i]+b[i];
    // 	c[i]=s/2.0/(n-i);
    // 	}
    	
    // }
    // // wt(c);

    // double ans=0;
    // double k=0.5;
    // f0(n){
    // 	if(b[i]<c[i+1]){
    // 		ans+=k*a[i];
    // 		break;
    // 	}
    // 	if(a[i]<c[i+1]){
    // 		ans+=k*a[i];
    // 	}
    // 	k/=2;
    // }

    // vector<double> dp(n+1);
    // dp[1]=

    
    vector<array<int,2>> c;
    double mn=1e9;

    f0(n){
    	if(a[i]>mn)continue;
    	c.push_back({a[i],b[i]});
    	mn=min((a[i]+b[i])/2.0,mn);
    }
    n=sz(c);
    double ans=0;
    double k=0.5;
    f0(n){
    	if(i<n-1)ans+=k*c[i][0];
    	else ans+=k*(c[i][0]+c[i][1]);
    	k/=2;
    }
    // vector<double> dp(n+1);
    // int lst=1;
    // dp[1]=(c[0][0]+c[0][1])/2.0;
    // double k=0.5;
    // for(int i=1;i<n;++i){
    // 	dp[i+1]=dp[i]-k*c[i-1][1] + k*(c[i][0]);
    // 	// dbg(dp[i],k,c[i-1][1],i,c[i][0],c[i][1],'\n');
    // 	k/=2;
    // }
    // // wt(dp);
    // double ans=1e9;
    // for(int i=1;i<=n;++i)ans=min(ans,dp[i]);
    cout<<ans<<"\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
