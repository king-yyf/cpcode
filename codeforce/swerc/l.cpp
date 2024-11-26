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

ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {
        x = 1; y = 0;
        return a;
    }
    int d = exgcd(b, a % b, y, x);
    y -= (a/b) * x;
    return d;
}

void ac_yyf(int tt) {
    rd(n,s,q);
    // dbg(n,s,q);
    int s1=count(all(s),'+'),s2=n-s1;
    while(q--){
    	rd(x,y);
    	if(x==y){
    		if(x==0||s1==s2){
    			cout<<"YES\n";
    			continue;
    		}else{
    			cout<<"NO\n";
    		}
    		
			continue;
    	}
    	if(s1==0||s1==n){
    		cout<<"NO\n";
    		continue;
    	}
    	long long k=2*s1-n;

    	long long x1=x+y,y1=y-x,t=k*y,x2,y2;
    	long long gd=gcd(x1,y1);
    	if(t%gd!=0){
    		cout<<"NO\n";
    		continue;
    	}
    	exgcd(x1,y1,x2,y2);
        long long q1=y1/gd,q2=x1/gd;

    	x2*=(t/gd),y2*=(t/gd);
        
        // if(x2<0&&y2<0){
        //     x2=-x2,y2=-y2;
        // }

        dbg(x2,y2,s1,s2,q1,q2,'\n');

        // if(x2<0){
        //     x2=x2+(-x2)*q1;
        //     y2=y2+x2*q2;
        // }
        // if(y2<0){

        // }

        // x2=x2-(x2/q1)*q1;y2=y2-(y2/q2)*q2;

        dbg(x2,y2,s1,s2,'\n');

    	bool o=0;

        if(0<=x2&&x2<=s1&&y2>=0&&y2<=s2)o=1;
        YN(o);
    }
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
