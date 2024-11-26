#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define fr(i,a,b) for (int i=(a);i<(b);i++)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

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
const double PI = acos(-1.0);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

void solve(int tt) {
    rd(n,m);
    vector<int> a(n);
    rd(a);
    each(x,a){
    	for(int i=0;i<m;++i){
    		if(x&(1<<i))cout<<1;
    		else cout<<0;
    	}
    	cout<<"\n";
    }

    auto get=[&](int x, int y){
    	int c=0;
    	for(int i=0;i<m;++i){
    		if((x&(1<<i))==(y&(1<<i)))c=c|(1<<i);
    	}
    	return c;
    };
    int s=0;
    for(int i=0;i<n;++i){
    	for(int j=i;j<n;++j){
    		int s1=a[i];
    		for(int k=i+1;k<=j;++k){
    			s1=get(s1,a[k]);
    		}
    		// dbg("i=","j=",s1,'\n');
    		s+=s1;
    	}
    }
    cout<<"s="<<s<<"\n";

    long long s1=Sum(a);
    // long long s1=0;


    vector<vector<int>> p(n+1,vector<int>(m));
    vector<vector<int>> q(n+1,vector<int>(m));

    for(int i=0;i<m;++i){
    	for(int j=0;j<n;++j){
    		if(a[j]&(1<<i)){
    			 p[j+1][i]=p[j][i];
    			 // p[j+1][i]=p[j+1][1]%2;
    		}
    		else {
    			p[j+1][i]=p[j][i]+1;
    			// p[j+1][i]=p[j+1][1]%2;
    		}
    	}
    }

    for(int i=0;i<m;++i){
    	for(int j=1;j<=n;++j){
    		if(p[j][i]%2==1){
    			 q[j][i]=q[j-1][i];
    		}
    		else {
    			q[j][i]=q[j-1][i]+1;
    		}
    	}
    }

     f0(m){
    	for(int j=0;j<=n;++j){
    		cout<<p[j][i]<<" ";
    	}
    	cout<<"\n";
    }
    cout<<"\n";

    f0(m){
    	for(int j=0;j<=n;++j){
    		cout<<q[j][i]<<" ";
    	}
    	cout<<"\n";
    }
    cout<<"\n";

    for(int i=0;i<m;++i){
    	dbg("i=",i,'\n');
    	for(int j=0;j<n-1;++j){
    		int c=0,t=0;
    		if((a[j]&(1<<i))==0) c++;
    		t=q[n][i]-q[j+2][i];
    		if(q[j+1][i]%2==c){
    			t=n-j-1-t;
    		}
    		// dbg("j=",j,"t=",t,"t1=",t1,'\n');
    		s1+=t*(1<<i);
    	}
    	
    }
    cout<<s1<<"\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
