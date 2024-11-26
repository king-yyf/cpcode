#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;
int n, m, k;

class Solution {
public:
    long long minimumMoves(vector<int>& a, int k, int mx) {
        int s=Sm(a);
        if(s==0) {
        	return 2*mx;
        }
        n=sz(a);
        ll c=1e18;
        vector<int> p;
        f0(n)if(a[i]==1)p.push_back(i);
        m=sz(p);
        vector<ll> pre(m+1);
        f0(m)pre[i+1]=pre[i]+p[i];

        auto get=[&](int l, int r) {
        	int md=(l+r)/2;
        	int c1=md-l+1;
        	ll s1=p[md]*1ll*c1-pre[md+1]+pre[l];
        	int c2=r-md;
        	ll s2=pre[r+1]-pre[md+1]-p[md]*1ll*c2;
        	return s1+s2;
        };

        f0(m){
        	// init at p[i]
        	ll cu=0;
        	k--;
        	if(k>0&&p[i]-1>=0&&a[p[i]-1]){
        		cu++;
        		k--;
        	}
        	if(k>0&&p[i]+1<n&&a[p[i]+1]){
        		cu++;
        		k--;
        	}
        	if(k>0) {
        		int d=min(k,mx);
        		cu+=2*d;
        		k-=d;
        	}
        	if(k>0) {
        		int l=0,r=n,t=n;
        		ll mn=1e18;
        		while(l<=r){
        			int md=(l+r)/2;
        			int l1=i,r1=m,t1=l1;
        			while(l1<=r1) {
        				int m1=(l1+r1)/2;
        				if(p[m1]-p[i]<=md){
        					t1=m1;
        					r1=m1;
        				}else{
        					l1=m1+1;
        				}
        			}
        			int cnt1=t1-i+1;
        			l1=i+1,r1=t1;
        			if(t1>i && p[i]+1<n&&a[p[i]+1]){
        				cnt1--;
        				l1++;
        			}
        			int l2=0,r2=i,t2=r2;
        			while(l2<=r2){
        				int m2=(l2+r2)/2;
        				if(p[i]-p[m2]<=md){
        					t2=m2;
        					l2=m2;
        				}else{
        					r2=m2-1;
        				}
        			}
        			int cnt2=i-t2+1;
        			l2=t2,r2=i-1;
        			if(t2<i&&p[i]-1>=0&&a[p[i]-1]){
        				cnt2--;
        				r2--;
        			}
        			if(cnt1+cnt2>=k) {
        				t=md;
        				r=md;
        				ll s1=0;
        				if(r2>=l2){
        					s1+=p[i]*1ll*(r2-l2+1)- (pre[r2+1]-pre[l2]);
        				}
        				if(r1>=l1){
        					s1+=pre[r1+1]-pre[l1]-(p[i]*1ll*(r1-l1+1));
        				}
        				cmn(mn,s1);
        			}else{
        				l=md+1;
        			}
        		}
        		c+=mn;
        	}
        }
        return c;
    }
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a,b;
    string s,t;
    vector<string> sv;
    vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    // Solution so;
    // rd(a,k);
    // auto ans = so.;
    // wt(ans);
    cout<<'\n';
    return 0;
}
#endif
