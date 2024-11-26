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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
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
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

bool ac_yyf(int tt) {
    int na,ma,nb,mb,nc,mc;
    rd(na,ma);
    vector<string> a(na);
    rd(a);
    rd(nb,mb);
    vector<string> b(nb);
    rd(b);
    rd(nc,mc);
    vector<string> c(nc);
    rd(c);


   


    auto fff=[&](vector<string> c) {
    	int n=sz(c),m=sz(c[0]);
    	int xmn=1e8,xmx=-1,ymn=1e8,ymx=-1;
	    f0(n)f2(j,m){
	    	if(c[i][j]=='#'){
	    		cmn(xmn,i);
	    		cmx(xmx,i);
	    		cmn(ymn,j);
	    		cmx(ymx,j);
	    	}
	    }
	    vector<string> x;
	    for(int i=xmn;i<=xmx;++i){
	    	string t;
	    	for(int j=ymn;j<=ymx;++j)
	    		t+=c[i][j];
	    	x.push_back(t);
	    }
	    return x;
    };


    c=fff(c);

    // each(x,c)wt(x,nl);

     int xb=12,yb=ma+12;


    for(int i=0;i<=na+nb+20;++i){
    	for(int j=0;j<=ma+mb+20;++j) {

    		

    		int len=max(i+na,xb+nb)-min(i,xb);

    		vector<string> t(len);
    		int mlen=max(j+ma,yb+mb)-min(j,yb);

    		for(int x=min(i,xb);x<max(i+na,xb+nb);++x){
    			string ps(mlen,'.');
    			for(int y=min(j,yb);y<max(j+ma,yb+mb);++y){
    				bool o=0;
    				if(x>=i&&x<i+na&&y>=j&&y<j+ma&&a[x-i][y-j]=='#')o=1;
    				if(x>=xb&&x<nb+xb&&y>=yb&&y<yb+mb&&b[x-xb][y-yb]=='#')o=1;
    				if(o)ps[y-min(j,yb)]='#';
    			}
    			t[x-min(i,xb)]=ps;
    		}


    		{
    			int n=sz(t),m=sz(t[0]);
		    	int xmn=1e8,xmx=-1,ymn=1e8,ymx=-1;
			    f0(n)f2(j,m){
			    	if(t[i][j]=='#'){
			    		cmn(xmn,i);
			    		cmx(xmx,i);
			    		cmn(ymn,j);
			    		cmx(ymx,j);
			    	}
			    }
			    vector<string> x;
			    for(int i=xmn;i<=xmx;++i){
			    	string t1;
			    	for(int j=ymn;j<=ymx;++j)
			    		t1+=t[i][j];
			    	x.push_back(t1);
			    }

			    // dbg("i=", i,"j=", j);
	    		// wt(nl);
	    		// each(xx,x)wt(xx,nl);
	    		// wt(nl);

			    if(x==c)return 1;
    		}
		    
		   
    		
    	}
    }


    int xa=nb,ya=mb;

/*
    for(int i=0;i<=na+nb;++i){
    	for(int j=0;j<=ma+mb;++j) {

    		int len=max(i+nb,xa+na)-min(i,xa);

    		vector<string> t(len);
    		int mlen=max(j+mb,ya+ma)-min(j,ya);

    		for(int x=min(i,xa);x<max(i+nb,xa+na);++x){
    			string ps(mlen,'.');
    			for(int y=min(j,ya);y<max(j+mb,ya+ma);++y){
    				bool o=0;
    				if(x>=i&&x<i+nb&&y>=j&&y<j+mb&&b[x-i][y-j]=='#')o=1;
    				if(x>=xa&&x<na+xa&&y>=ya&&y<ya+ma&&a[x-xa][y-ya]=='#')o=1;
    				if(o)ps[y-min(j,yb)]='#';
    			}
    			t[x-min(i,xb)]=ps;
    		}


    		{
    			int n=sz(t),m=sz(t[0]);
		    	int xmn=1e8,xmx=-1,ymn=1e8,ymx=-1;
			    f0(n)f2(j,m){
			    	if(t[i][j]=='#'){
			    		cmn(xmn,i);
			    		cmx(xmx,i);
			    		cmn(ymn,j);
			    		cmx(ymx,j);
			    	}
			    }
			    vector<string> x;
			    for(int i=xmn;i<=xmx;++i){
			    	string t1;
			    	for(int j=ymn;j<=ymx;++j)
			    		t1+=t[i][j];
			    	x.push_back(t1);
			    }

			    dbg("i=", i,"j=", j);
	    		wt(nl);
	    		each(xx,x)wt(xx,nl);
	    		wt(nl);

			    if(x==c)return 1;
    		}
		    
		   
    		
    	}
    }
*/

    // {
    // 	int l=1e8,r=-1,u=1e8,d=-1;
	//     f0(na)f2(j,ma){
	//     	if(a[i][j]=='#'){
	//     		cmn(l,j);
	//     		cmx(r,j);
	//     		cmn(u,i);
	//     		cmx(d,i);
	//     	}
	//     }
	//     vector<string> x1;
	//     for(int i=u;i<=d;++i){
	//     	string t;
	//     	for(int j=l;j<=r;++j)
	//     		t+=a[i][j];
	//     	x1.push_back(t);
	//     }
	//     a=x1;
	//     na=sz(a),ma=sz(a[0]);
    // }

    // {
    // 	int l=1e8,r=-1,u=1e8,d=-1;
	//     f0(nb)f2(j,mb){
	//     	if(b[i][j]=='#'){
	//     		cmn(l,j);
	//     		cmx(r,j);
	//     		cmn(u,i);
	//     		cmx(d,i);
	//     	}
	//     }
	//     vector<string> x1;
	//     for(int i=u;i<=d;++i){
	//     	string t;
	//     	for(int j=l;j<=r;++j)
	//     		t+=b[i][j];
	//     	x1.push_back(t);
	//     }
	//     b=x1;
	//     nb=sz(b),mb=sz(a[0]);
    // }

    // int l=1e8,r=-1,u=1e8,d=-1;
    // f0(nc)f2(j,mc){
    // 	if(c[i][j]=='#'){
    // 		cmn(l,j);
	//     		cmx(r,j);
	//     		cmn(u,i);
	//     		cmx(d,i);
    // 	}
    // }
    // vector<string> x;
    // for(int i=u;i<=d;++i){
    // 	string t;
    // 	for(int j=l;j<=r;++j)
    // 		t+=c[i][j];
    // 	x.push_back(t);
    // }

    // nc=sz(x),mc=sz(x[0]);

    // for(int i=-na;i<=na+nb;++i){
    // 	for(int j=-ma;j<=ma+mb;++j){
    // 		int la=j,ra=j+ma,ua=i,da=i+na;
    // 		int lb=0,rb=mb,ub=0,db=nb;
    // 		int nn=max(ra,rb)-min(la,lb);
    // 		int mm=max(da,db)-min(ua,ub);
    // 		if(nn==nc&&mm==mc){
    // 			vector<string> y(nn,string(mm,'.'));
    // 			for(int l=min(ua,ub);l<max(da,db);++l) {
    // 				for(int k=min(la,lb);k<max(ra,rb);++k){
    // 					bool o=0;
    // 					if(l>=ua&&l<da&&k>=la&&k<=ra&&a[k-i][l-j]=='#')o=1;
    // 					if(l>=0&&l<mb&&k>=0&&k<=nb&&b[k][l]=='#')o=1;
    // 					if(o){
    // 						y[k-min(la,lb)][l-min(ua,ub)]='#';
    // 					}
    // 				}
    // 			}
    // 			if(y==x){
    // 				return 1;
    // 			}
    // 		}
    // 	}
    // }
    // return 0;

    return 0;
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
