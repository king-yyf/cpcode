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
    rd(n,m);
    vector<int> op(n);
    rd(op);
    if(m==1 &&n>0){
    	wt(1,nl);return ;
    }


    // int l=0,r=0,p=0;

    // // vector<long long> v;

    // // set<ll> s;
    // // v.push_back(-1);
    // // f0(n){

    // // }



    vector<int>p(m),a;
    x=0,y=0;
    
  
    f0(n){
    	if(op[i]>0){
    		int pos=op[i]-1;
    		if(p[pos]==0){
    			a.push_back(pos+1);
    			p[pos]=1;
    		}
    	}
    	else if(op[i]==-2)x++;
    	else y++;
    }

    a.push_back(-1);
    sort(all(a));
    a.push_back(-2);


    long long c=0;

    int m1=sz(a);
    f0(m1){
        int t=a[i];
        if(i==0){
            cmx(c,min(x+m1-2,m));
        }else if(i==m1-1){
            cmx(c,min(y+m1-2,m));
        }else{
            cmx(c,1+min(y+i-1,t-1)+min(x+m1-i-2,m-t));
        }
    }

    wt(c,nl);
    








    // cmn(x,m);cmn(y,m);

    // if(sz(a)==0){
    // 	wt(max(x,y),nl);
    // 	return;
    // }

    // int c=sz(a),d=0,m1=sz(a);
    // d=m1+min(m-m1,y);
    // cmx(c,d);
    // d=m1+min(m-m1,x);
    // cmx(c,d);


    // // wt(a);


    // // int j=-1;
    // // for(int i=1;i<m;++i) {
    // // 	while(j+1<m1&&a[j+1]<=i)j++;
    // // 	int r=i+1-(j+1);
    // // 	d=m1+min(x,r);


    // // 	int r1=m-1-i-(m1-(j+1));
    // // 	d+=min(r1,y);

    // // 	dbg(i,j,c,d,x,y,m1+min(x,r),min(r1,y),nl);

    // // 	cmx(c,d);
    	
    // // }
    // sort(all(a));

    // f0(sz(a)){
    // 	int t=a[i];
    // 	int r=t-i;
    // 	d=m1+min(x,r);
    // 	r=m-t-(m1-1-i);
    // 	d+=min(r,y);
    // 	cmx(c,d);
    // }
    // cmx(c,x);
    // cmx(c,y);
    // wt(c,nl);
    
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
