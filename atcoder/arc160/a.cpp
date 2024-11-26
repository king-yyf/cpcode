#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
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
#define yes cout << "Yes\n"
#define YES cout << "YES\n"
#define no cout << "No\n"
#define NO cout << "NO\n"
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
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

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

void ac_yyf(int tt) {
    cin >> n>>k;
    vector<int> a(n);
    vector<int> pos(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    	a[i]--;
    	pos[a[i]]=i;
    }

    int i=0;
    while(i<n){
    	int x=1;
    	if(a[0]==i){
    		x=1+n*(n-1)/2;
    	}
    	if(k<=x){
    		break;
    	}
    	k-=x;
    	i++;
    }

    // dbg("i=",i,nl);
    // return;

    if(a[0]!=i){
    	for(int j=pos[i];j>=0;--j){
    		dbg(a[j]+1);
    	}
    	for(int j=pos[i]+1;j<n;++j){
    		dbg(a[j]+1);
    	}
    	return ;
    }
    vector<int> p(n);
    p[0]=i;
    int t=i;
    vector<int> vis(n);vis[t]=1;

    int d=1+n*(n-1)/2;

    for(int i=1;i<n;++i){
    	for(int j=0;j<n;++j){
    		if(vis[j])continue;
    		int x=1;
    		if(a[i]==j){
    			int lft=n-(i+1);
    			x=i+1+lft*(lft+1)/2;
    		}
    		if(k<=x){
    			if(a[i]!=j){
    				for(int _=0;_<i;++_){
    					dbg(p[_]+1);
    				}
    				for(int _=pos[j];_>=i;--_)
    					dbg(a[_]+1);
    				for(int _=pos[j]+1;_<n;++_)
    					dbg(a[_]+1);
    				return;
    			}
    			p[i]=j;
    			vis[j]=1;
    			break;
    		}
    		k-=x;
    	}
    }
    f0(n){
    	dbg(p[i]+1);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
