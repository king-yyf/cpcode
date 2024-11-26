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

int get(vector<int> &a, int k){
	unordered_map<ll, int> mp;
	int n=sz(a);
	ll c=0;
	int s=n+1;
	f0(n){
		c+=a[i];
		if(c==k){
			cmn(s,i+1);
		}
		ll s1=c-k;
		if(mp.count(s1)){
			cmn(s,i-mp[s1]);
		}
		mp[c]=i;
	}
	return s;
}

class Solution {
public:
    int minSizeSubarray(vector<int>& a, int k) {
        n=sz(a);
        ll s=Sm(a);
        ll c2=k/s;
        k%=s;

        ll c=0;
        int l=n-1,r=0;
        f0(n){
        	c+=a[i];
        	if(c>=k){
        		if(c-a[0]>=k)i--;
        		l=i;break;
        	}
        }
        c=0;
        for(int i=n-1;i>=0;--i){
        	c+=a[i];
        	if(c>=k){
        		if(c-a[n-1]>=k)i++;
        		r=i;break;
        	}
        }

        // wt(a);
        // dbg("l=",l,"r=",r,nl);

        vector<int> c1;
        c1.reserve(2*n);
        for(int i=r;i<n;++i)
        	c1.push_back(a[i]);
        for(int i=0;i<=l;++i)
        	c1.push_back(a[i]);

        wt(c1);

        auto p=get(c1,k);
        if(p>sz(c1))return -1;
        return c2*n+p;
    }
};

#ifdef sigma-yyf
int main(){
    Solution so;
    vector<int> a{1,2,3};
    int k=5;
    auto c=so.minSizeSubarray(a,k);
    wt(c,nl);
    return 0;
}
#endif
