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
95 23 30 83 17 91 40 83 62 87 43 21 100 78 62 96 2 8 44 69 5 15 88 71 65 55 29 81 30 56 85 72 85 36 81 49 42
95 23 30 83 17 91 40 83 62 87 43 21 100 78 62 96 2 8 44 69 5 15 88 71 65 55 29 81 30 56 85 72 85 36 81 49 42
*/
void ac_yyf(int tt) {
    cin >> n;
   vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    // wt(a);
    for(int i=0;i<n-1;++i){
    	// dbg(i,a[i],a[i+1],'\n');
    	if(a[i+1]%a[i]!=0)continue;
    	if(a[i]==1){
    		if(a[i-1]==2){
    			a[i]=3;
    			if(a[i+1]%3==0)a[i+1]++;
    		}else{
    			a[i]=2;
    		if(a[i+1]%2==0)a[i+1]++;
    		}
    		
    	} else if(a[i]==2){
    		if(i>0&&a[i-1]<=2){
    			a[i]=3;
    			if(a[i+1]%3==0)a[i+1]++;
    		}else{
    		    if(a[i+1]%2==0)a[i+1]++;
    		}
    	}else{
    		a[i+1]++;
    	}

    }
    wt(a);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    // f2(j,1000){
    // 	int n=rng(40)+1;
	//     vector<int> a(n);
	//     f0(n){
	//     	a[i]=rng((int)100)+1;
	//     }
	//     auto b=a;
	//     ac_yyf(a);
	//     bool o=1;
	//     f0(n-1){
	//     	if(a[i+1]%a[i]==0){
	//     		o=0;
	//     	}
	//     }
	//     if(o==0){
	//     	wt(b);wt(a);break;
	//     }
    // }

    // vector<int> a{37,75,91,34,82,66,80,100,12,40,35,13,18,71,55,10,84,1,1,86};
    // vector<int> b{37,75,91,34,82,66,80,100,12,40,35,13,18,71,55,10,84,2,2,87};

    // int n=sz(a);f0(n-1){
    // 	if(b[i+1]%b[i]==0){
    // 		dbg(i,b[i],b[i+1],'\n');
    // 	}
    // }

    // ac_yyf(a);


    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
