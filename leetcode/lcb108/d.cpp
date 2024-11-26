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

/*

32
32
[[17,29],[29,16],[19,20],[18,9],[16,7],[20,25],[22,19],[4,9],[14,17],[6,23],[2,2],[20,1],[8,7],[4,7],[14,14],[10,10],[1,27],[18,23],[6,30],[8,18],[26,23],[25,8],[5,6],[3,4]]

[866,94,1,0,0]
*/

class Solution {
public:
    vector<long long> countBlackBlocks(int n, int m, vector<vector<int>>& g) {
        vector<long long> c(5);
        set<pair<int,int>> s;
        // map<pair<int,int>,int> mp;
        for(auto&e:g){
        	int x=e[0],y=e[1];
        	s.emplace(x,y);
            // mp[{x,y}]++;
        }
        for(auto&[x,y]:s){
        	// int x=e[0],y=e[1];
        	if(x+1<n&&y+1<m){
        		int c1=(s.count({x,y}))+(s.count({x+1,y}))+(s.count({x,y+1}))+(s.count({x+1,y+1}));
        		c[c1]++;
        	}
        	if(x-1>=0&&y-1>=0){
        		int c1=(s.count({x,y}))+(s.count({x-1,y}))+(s.count({x,y-1}))+(s.count({x-1,y-1}));
        		c[c1]++;
        	}
        	if(x+1<n&&y-1>=0){
        		int c1=(s.count({x,y}))+(s.count({x+1,y}))+(s.count({x,y-1}))+(s.count({x+1,y-1}));
        		c[c1]++;
        	}
        	if(x-1>=0&&y+1<m){
        		int c1=(s.count({x,y}))+(s.count({x-1,y}))+(s.count({x,y+1}))+(s.count({x-1,y+1}));
        		c[c1]++;
        	}
        }
        ll s1=0;

        f1(4)c[i]/=i;
        f1(4)s1+=c[i];
        c[0]=(n-1ll)*(m-1ll)-s1;
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
