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

const int N = 1e5 + 5;
bool st[N];
int primes[N], cnt; // primes[]存储所有素数
void getPrimes(int n) {
    st[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!st[i]) 
            primes[cnt++] = i;
        for (int j = 0; primes[j] * i <= n; ++j) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) 
                break;
        }
    }
}
bool init=false;

class Solution {
public:
    long long countPaths(int n, vector<vector<int>>& es) {
        if(!init){
        	init=1;
        	getPrimes(100000);
        }
        vector<vector<int>> g(n);
	    for (auto &e: es) {
	        g[e[0]].push_back(e[1]);
	        g[e[1]].push_back(e[0]);
	    }
	    long long ans = 0;
	    vector<int> down(n), up(n), pa(n);
	    function<void(int, int)> dfs = [&](int u, int fa) {
	        for (int v : g[u]) if (v != fa) {
	            dfs(v, u);
	            pa[v] = u;
	            if (st[v + 1]) down[u] += down[v] + 1;
	        }
	    };
	    dfs(0, -1);
	    function<void(int, int)> dfs2 = [&](int u, int fa) {
	        int d = st[u + 1] ? down[u] + 1: 0;
	        if (fa != -1 && st[fa + 1]) up[u] += up[fa] + down[fa] + 1 - d;
	        for (int v : g[u]) if (v != fa) {
	            dfs2(v, u);
	        }
	    };
	    dfs2(0, -1);
	    for (int i = 0; i < n; ++i) {
	        if (!st[i + 1]) {
	            ans += (down[i] + 1ll) * (up[i] + 1ll) - 1;
	            long long sum = down[i];
	            for (auto & v : g[i]) if (v != pa[i]) {
	                if (st[v + 1]) {
	                    sum -= down[v] + 1;
	                    ans += sum * (down[v] + 1);
	                }
	            }
	        }
	    }
	    return ans;
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
