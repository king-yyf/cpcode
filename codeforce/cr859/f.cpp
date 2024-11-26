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
	int x1,y1,x2,y2;
	string d;
    rd(n,m,x1,y1,x2,y2,d);

    auto go=[&](int x, int y, string &d){
    	int x1,y1;
    	if(d=="DR"){
    		int a=n-x,b=m-y;
    		// if(tt==1){
    		// 	dbg("a=",a,"b=",b,"x=",x,"y=",y,"d=",d,'\n');
    		// }
    		if(a==b){
    			x1=n,y1=m;
    			d="UL";
    		}
    		else if(a<b){
    			x1=n,y1=y+a;
    			d="UR";
    		}else{
    			x1=x+b,y1=m;d="DL";
    		}
    	}else if(d=="DL"){
    		int a=n-x,b=y-1;
    		// if(tt==1){
    		// 	dbg("a=",a,"b=",b,"x=",x,"y=",y,"d=",d,'\n');
    		// }
    		if(a==b){
    			x1=n,y1=1;
    			d="UR";
    		}
    		else if(a<b){
    			x1=n,y1=y-a;
    			d="UL";
    		}else{
    			x1=x+b,y1=1;
    			d="DR";
    		}
    	}else if(d=="UR"){
    		int a=x-1,b=m-y;
    		// if(tt==1){
    		// 	dbg("a=",a,"b=",b,"x=",x,"y=",y,"d=",d,'\n');
    		// }
    		if(a==b){
    			x1=1,y1=m;
    			d="DL";
    		}
    		else if(a<b){
    			x1=1,y1=y+a;
    			d="DR";
    		}else{
    			x1=x-m,y1=m;
    			d="UL";
    		}
    	}else{
    		int a=x-1,b=y-1;
    		// if(tt==1){
    		// 	dbg("a=",a,"b=",b,"x=",x,"y=",y,"d=",d,'\n');
    		// }
    		if(a==b){
    			x1=1,y1=1;
    			d="DR";
    		}
    		else if(a<b){
    			x1=1,y1=y-a;
    			d="DL";
    		}else{
    			x1=x-b,y1=1;
    			d="UR";
    		}
    	}
    	pair<int,int> p{x1,y1};
    	return p;
    };

    int t=n*m;
    set<pair<int,int>> s1,s2,s3,s4;
    int c=0;
    auto chk=[&](int x, int y, int x1, int y1) {
    	int mn=min(x,x1);
    	int mx=max(x,x1);
    	if(x==x1&&y==y1&&(x!=x2||y!=y2)) return false;
    	if(x==x2&&y==y2)return true;
    	if(x1==x2&&y1==y2)return true;
    	bool o=1;
    	if(!(x2>=mn&&x2<=mx))o=0;
    	ll a=(x2-x)*1ll*(y1-y2);
    	long long  b=(x1-x2)*1ll*(y2-y);
    	if(!(a==b))o=0;
    	return o;
    };
    string dd;
    bool o=0;
    x=x1,y=y1;

    f0(t*4){
    	dd=d;
    	auto [x1,y1]=go(x,y,d);
    	if(chk(x,y,x1,y1)) {
    		o=1;
    		break;
    	}
    	x=x1,y=y1;
        bool o1=0,o2=0;
    	if(((x==1&&y==1)||(x==1&&y==m)||(x==n&&y==1)||(x==n&&y==m))){
    		o1=1;
    	}
    	if(dd=="DR"){
    		if(s1.count({x1,y1})){
    			o2=1;break;
    		}
    		s1.insert({x1,y1});
    	}else if(dd=="DL"){
    		if(s2.count({x1,y1})){
    			o2=1;break;
    		}
    		s2.insert({x1,y1});
    	}else if(dd=="UL"){
    		if(s3.count({x1,y1})){
    			o2=1;break;
    		}
    		s3.insert({x1,y1});
    	}else{
    		if(s4.count({x1,y1})){
    			o2=1;break;
    		}
    		s4.insert({x1,y1});
    	}
        if(o1&&o2){
            wt("-1\n");return ;
        }
    	c++;
    }
    // if(!o){
    // 	cout<<"-1\n";return;
    // }
    if(!o){
    	wt("-1\n");
    }
    else wt(c,'\n');
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
