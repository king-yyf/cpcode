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

struct SCC {
    int n, cnt = 0;
    vector<pair<int, int>> edges;
    vector<int> low, dfn, ids, in, out;
    explicit SCC(int n) : n(n), low(n), dfn(n, -1), ids(n){}
    void add_edge(int from, int to) { edges.push_back({from, to}); }

    void scc_ids() {
        vector<int> start(n + 1), elist(edges.size()), visited;
        for (auto &e : edges) 
            start[e.first + 1]++;
        for (int i = 1; i <= n; ++i) 
            start[i] += start[i - 1];
        auto counter = start;
        for (auto &e : edges)
            elist[counter[e.first]++] = e.second;
        int now_dfn = 0;
        visited.reserve(n);
        auto dfs = [&](auto self, int v) -> void {
            low[v] = dfn[v] = now_dfn++;
            visited.push_back(v);
            for (int i = start[v]; i < start[v + 1]; i++) {
                auto to = elist[i];
                if (dfn[to] == -1) {
                    self(self, to);
                    low[v] = min(low[v], low[to]);
                } else {
                    low[v] = min(low[v], dfn[to]);
                }
            }
            if (low[v] == dfn[v]) {
                while (true) {
                    int u = visited.back();
                    visited.pop_back();
                    dfn[u] = n, ids[u] = cnt;
                    if (u == v) break;
                }
                cnt++;
            }
        };
        for (int i = 0; i < n; i++) if (dfn[i] == -1) dfs(dfs, i);
        in.assign(cnt, 0);
        for (auto& x : ids) {
            x = cnt - 1 - x;
            in[x]++;
        }
    }

    vector<vector<int>> scc(bool cal_degree = false) {
        scc_ids();
        vector<vector<int>> groups(cnt);
        for (int i = 0; i < cnt; ++i) groups[i].reserve(in[i]);
        for (int i = 0; i < n; i++) groups[ids[i]].push_back(i);
        if (cal_degree) {
            in.assign(cnt, 0), out.assign(cnt, 0);
            for (auto &[from, to]: edges) {
                int x = ids[from], y = ids[to];
                if (x != y) in[y]++, out[x]++;
            }
        }
        return groups;
    }
};


class Solution {
public:
    vector<int> countVisitedNodes(vector<int>& es) {
    	n=sz(es);
        SCC g(n);
        f0(n)g.add_edge(i,es[i]);
        auto p=g.scc();
	    vector<int> ans(n);
	    int m=sz(p);
	    vector<int> c(m);
	    for(int i=m-1;i>=0;--i){
	    	if(i==m-1){
	    		c[i]=sz(p[i]);
	    		for(auto&x:p[i]){
	    			ans[x]=sz(p[i]);
	    		}
	    	}else{
	    		for(auto&x:p[i]){
	    			ans[x]=sz(p[i])+c[i+1];
	    		}
	    		c[i]=sz(p[i])+c[i+1];
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
