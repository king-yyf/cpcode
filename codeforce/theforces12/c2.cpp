#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define yn(o) cout << ((o) ? "Yes" : "No") << "\n";
#define YN(o) cout << ((o) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
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
const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

long long get(ll x){
	return x*(x+1)/2;
}

void ac_yyf(int tt) {
    rd(n,x);
    if(n==2){
    	if(x==1){
    		wt("1 4 2 3\n");
    	}else if(x==2){
    		wt("2 3 1 4\n");
    	}else if(x==3){
    		wt("3 2 1 4\n");
    	}else{
    		wt("4 1 2 3\n");
    	}
    	return;
    }

    if(n==3){
    	if(x==1){
    		wt("1 6 2 5 3 4\n");
    	}else if(x==2){
    		wt("2 5 4 3 6 1\n");
    	}else if(x==3){
    		wt("3 4 2 5 1 6\n");
    	}else if(x==4){
    		wt("4 3 5 2 6 1\n");
    	}else if(x==5){
    		wt("5 2 3 4 1 6\n");
    	}else{
    		wt("6 1 5 2 4 3\n");
    	}
    	return;
    }

    long long s=get(2*n),s1;



    vector<int> a(2*n+1),b(2*n+1);
    int p=2*n+1;
    auto chk=[&](){
    	f1(2*n)b[i]=a[i];
    	sort(all(b));
    	for(int i=1;i<=2*n;++i)
    		if(b[i]!=i)return 0;
    	for(int i=1;i<=2*n;i+=2){
    		if(a[i]+a[i+1]!=p)return 0;
    	}
    	int s1=a[2]+a[3];
    	for(int i=2;i<2*n;i+=2){
    		if(a[i]+a[i+1]!=s1)return 0;
    	}
    	return 1;
    };

    bool o=0;
    
    for(int i=1;i<=2*n;++i){
		if(i==x||i+x==2*n+1)continue;
		s1=s-x-i;
		if(s1%(n-1)!=0) continue;
		int d=s1/(n-1);
		a[1]=x,a[2*n]=i;a[2*n-1]=p-i;
		a[2]=p-x;
		for(int i=3;i<2*n-1;++i){
			if(i%2==1){
				a[i]=d-a[i-1];
			}else{
				a[i]=p-a[i-1];
			}
		}
		if(chk()){
			f1(2*n){
				cout<<a[i]<<' ';
			}
			cout<<nl;
			return;
		}
	}
	wt("-1\n");

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
