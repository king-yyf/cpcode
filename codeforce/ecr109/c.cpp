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
    cin >> n>>m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    vector<char> c(n);
    for (int i = 0; i < n; ++i) {
        cin>>c[i];
    }
    set<int> l0,l1,r0,r1;
    for(int i=0;i<n;++i){
    	if(c[i]=='L') {
    		if(i%2==0){
    			l0.push_back(a[i]);
    		}else{
    			l1.push_back(a[i]);
    		}

     	}else{
     		if(i%2==0){
    			r0.push_back(a[i]);
    		}else{
    			r1.push_back(a[i]);
    		}
     	}
    }

    vector<int> ans(n,-1);
    for (int i = 0; i < n; ++i) {
    	if(ans[i]!=-1) continue;
        if(c[i]=='L') {
        	if(i%2==0){
        		auto p=r0.lower_bound(a[i]);
        		if(p==r0.end()) {
        			if(r0.size()==0){
        				auto p1=l0.upper_bound(a[i]);
        				if(p1==l0.end()){

        				}else{
        					
        				}
        			}else{

        			}
        		}else if(p==r0.begin()) {
        			auto p1=l0.upper_bound(a[i]);
        			if(p1==l0.end()) {
        				auto pos=*r0.rbegin();
        				r0.erase(r0.rbegin());
        				if(a[i]>m-pos){
        					int np=2*m-a[i]-pos;
        					ans[i]=ans[pos]=a[i]+np/2;
        				}else{
        					int np=m-pos-a[i];
        					ans[i]=ans[pos]=a[i]+(m-np)/2;
        				}

        			}else{
        				ans[i]=ans[*p1]=a[i]+(*p1-a[i])/2;
        				l0.erase(p1);
        			}
        		} else {

        		}
        	}else{
        		
        	}
        }else{
        	if(i%2==0){
        		
        	}else{
        		
        	}
        }
        l0.erase(a[i]);
    }
    wt(ans);
    
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
