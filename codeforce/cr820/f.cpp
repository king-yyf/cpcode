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
	int w,m;
    rd(s,w,m);
    vector<vector<int>> a(10);

    int n=sz(s);

    vector<int> pre(n+1);
    f0(n)pre[i+1]=pre[i]+(s[i]-'0');

    int p=0;

    for(int i=0;i<n;++i){
    	p+=s[i]-'0';
    	if(i>=w-1){
    		if(i>w-1){
    			p-=(s[i-w]-'0');
    		}
    		a[p%9].push_back(i-w+1);
    	}
    }
    // dbg("------\n");
    // for(int i=0;i<9;++i){
    // 	cout<<"i="<<i<<": ";
    // 	wt(a[i]);
    // }
    // dbg("------\n");

    while(m--){
    	int l,r;

    	rd(l,r,k);
    	int s1=pre[r]-pre[l-1];
    	s1=s1%9;
    	int l1=-1,l2=-1;
    	for(int i=0;i<9;++i){
    		for(int j=0;j<9;++j){
    			if((i*s1+j)%9==k){
    				if(i==j){
    					vector<int> &v=a[i];
    					if(sz(v)<2) continue;
    					else{
    						int x1=v[0],x2=v[1];
    						x1++,x2++;
    						if(l1==-1){
    							l1=x1,l2=x2;
    						}else if(x1<l1){
    							l1=x1,l2=x2;
    						}else if(x1==l1&&l2>x2){
    							l2=x2;
    						}
    					}
    				}else{
    					vector<int> &v1=a[i];
    					vector<int> &v2=a[j];
    					if(sz(v1)&&sz(v2)){
    						int x1=v1[0],x2=v2[0];
    						x1++,x2++;
    						if(l1==-1){
    							l1=x1,l2=x2;
    						}else if(x1<l1){
    							l1=x1,l2=x2;
    						}else if(x1==l1&&l2>x2){
    							l2=x2;
    						}
    					}
    				}
    			}
    		}
    	}
    	cout<<l1<<" "<<l2<<"\n";
    }

}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
