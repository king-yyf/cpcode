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
    rd(n);
    int x1=0,x2=0;
    int y1=0,y2=0;
    int p=0;
    set<pair<int,int>> s1,s2,s3,s4;
    f0(n){
    	rd(x,y);
    	if(x==0&&y==0){
    		p++;
    	}else if(x==0){
    		if(y>0)y1++;
    		else y2++;
    	}else if(y==0){
    		if(x>0)x1++;else x2++;
    	}else {
    		if(x>0){
    			if(y>0){
    				int t=gcd(x,y);
    				x/=t;
    				y/=t;
    				s1.insert({x,y});
    			}else{
    				y=-y;
    				int t=gcd(x,y);
    				x/=t;
    				y/=t;
    				s2.insert({x,y});
    			}
    		}else{
    			if(y>0){
    				x=-x;
    				int t=gcd(x,y);
    				x/=t;
    				y/=t;
    				s3.insert({x,y});
    			}else{
    				x=-x,y=-y;
    				int t=gcd(x,y);
    				x/=t;
    				y/=t;
    				s4.insert({x,y});
    			}
    		}
    	}
    }
    if(p>0){
    	cout<<p<<"\n";
    	return ;
    }
    if(x1>1)x1=1;
    if(y1>1)y1=1;
    if(x2>1)x2=1;
    if(y2>1)y2=1;
    int ans=p+x1+y1+x2+y2+sz(s1)+sz(s2)+sz(s3)+sz(s4);
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
