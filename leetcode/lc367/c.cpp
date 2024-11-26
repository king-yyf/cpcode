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

template<typename T, bool max_mode = false>
struct ST {
    static int lg(unsigned x) { return x == 0 ? -1 : 31 - __builtin_clz(x);}
    int n = 0;
    vector<T> a;
    vector<vector<int>> mat;
    ST(const vector<T> &A = {}) { if (!A.empty()) build(A);}
    int op(int x, int y) const {
        return (max_mode ? a[y] < a[x] : a[x] < a[y]) ? x : y; // when `a[x] == a[y]`, returns y.
    }
    void build(const vector<T> &A) {
        a = A, n = int(a.size());
        int max_log = lg(n) + 1;
        mat.resize(max_log);
        for (int k = 0; k < max_log; k++) mat[k].resize(n - (1 << k) + 1);
        for (int i = 0; i < n; i++) mat[0][i] = i;
        for (int k = 1; k < max_log; k++)
            for (int i = 0; i <= n - (1 << k); i++)
                mat[k][i] = op(mat[k - 1][i], mat[k - 1][i + (1 << (k - 1))]);
    }
    int get_idx(int x, int y) const {  // 0 <= x < y <= n
        int k = lg(y - x);
        return op(mat[k][x], mat[k][y - (1 << k)]);
    }
    T get_val(int x, int y) const { return a[get_idx(x, y)];}
};

class Solution {
public:
    vector<int> findIndices(vector<int>& a, int x, int y) {
        n=sz(a);
        if(n==1){
        	if(x==0&&y==0)return {0,0};
        	return {-1,-1};
        }
        ST<int,true> s1;ST<int> s2;
        s1.build(a);s2.build(a);
        for(int i=x;i<n;++i){
        	int j=i-x;
        	int mx=s1.get_val(0,j+1),mn=s2.get_val(0,j+1);
        	int u=abs(mx-a[i]),v=abs(mn-a[i]);
        	dbg("i=",i,"j=",j,"mx=",mx,"mn=",mn,"a[i]=",a[i],u,v,nl);
        	if(u>=y){
        		int k= s1.get_idx(0,j+1);
        		return {k,i};
        	}
        	if(v>=y){
        		int k= s2.get_idx(0,j+1);
        		return {k,i};
        	}
        }
        return {-1,-1};
    }
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a{5,1,4,1},b;
    string s,t;
    vector<string> sv;
    vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    Solution so;
    // rd(a,k);
    auto ans = so.findIndices(a,2,4);
    // wt(ans);
    cout<<'\n';
    return 0;
}
#endif
