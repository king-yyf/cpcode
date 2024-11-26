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

void ac_yyf(int tt) {
    // rd(n);
    // vector<int> a(n+1);
    // f1(n)a[i]=i;
    // f1(n){
    // 	cout<<
    // }

    // for(int i=4;i<=8;++i){
    // 	vector<int> a(i);
    // 	bool o=0;
    //     for(int j=0;j<i;++j)
    //     	a[j]=j+1;
    //     do{
    //     	set<int> s;
    //     	int s1=0;
    //     	f2(j,i){
    //     		s1+=a[j];
    //     		s.insert(s1%i+1);
    //     	}
    //     	if(sz(s)==i){
    //     		o=1;
    //     		dbg("i=",i);
    //     		wt(a);
    //     		break;
    //     	}
    //     }while(next_permutation(all(a)));
    //     if(o==0) dbg("i=",i,-1,nl);
    // }

	// for(int i=4;i<=20;i+=2){
	// 	vector<int> a(i);

	// 	// sort(rall(a));
	// 	long long s1=0;
	// 	set<int>ss;
	// 	f2(j,i){
	// 		s1+=a[j];
	// 		ss.insert(s1%i+1);
	// 	}
	// 	if(sz(ss)!=i){
	// 		dbg("i=",i,nl);
	// 	}

	// }

    rd(n);
    if(n==1){
    	wt("1\n");
    	return;
    }
    if(n&1){
    	wt("-1\n");
    	return;
    }


    int x=n,y=1;
    vector<int> a(n);
	for(int j=0;j<n;++j){
		if(j%2==0) {
			a[j]=x;x-=2;
		}
		else{
			 a[j]=y;y+=2;
		}
	}
		wt(a);
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
