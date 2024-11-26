#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

using ll = long long;
#define ar(x) array<int,x> 
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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> T f_div(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0));}
template <class T> T c_div(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0));}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
#ifdef sigma-yyf
#define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    cerr << s << ": " << h, ((cerr << ", " << t), ..., (cerr << "\n"));
}
#else
#define dbg(...) void(0)
#endif
template<class Fun> class Y_comb {
    Fun _f;
public:
    template<class T> explicit Y_comb(T &&fun): _f(forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...As) {return _f(ref(*this), forward<Args>(As)...);}
};
template<class Fun> decltype(auto) y_comb(Fun &&fun) { return Y_comb<decay_t<Fun>>(forward<Fun>(fun));}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;
constexpr char nl = '\n';
constexpr int inf = 1'061'109'567;
constexpr ll infll = 2'000'000'000'000'000'000;
constexpr int N = 2e5 + 5;
int n, m, k;

struct BFS {
    static constexpr int unreachable = -1;

    BFS(int n = 0) : n(n), g(n) {}
    template <typename Edges>
    BFS(int n, const Edges& edges) : BFS(n) { for (const auto& [u, v] : edges) add_edge(u, v);}
    BFS(const vector<vector<int>>& g) : n(g.size()), g(g) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> bfs(const vector<int>& src) const {
        vector<int> dist(n, unreachable);
        queue<int> q;
        for (int v : src) {
            dist[v] = 0;
            q.push(v);
        }
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) if (dist[v] == unreachable) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return dist;
    }
    vector<int> bfs(int s) const { return bfs(vector<int>{ s });}

    vector<vector<int>> connected_components() const {
        vector<vector<int>> res;
        vector<int8_t> vis(n, false);
        for (int i = 0; i < n; ++i) if (not exchange(vis[i], true)) {
            auto& cmp = res.emplace_back();
            queue<int> q;
            q.push(i);
            while (q.size()) {
                int u = q.front();
                q.pop();
                cmp.push_back(u);
                for (int v : g[u]) if (not exchange(vis[v], true)) {
                    q.push(v);
                }
            }
        }
        return res;
    }
    int n;
    vector<vector<int>> g;
};

class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& qs) {
        if(n==2){
        	vector<int> tmp{0,1};
        	vector<vector<int>> c{tmp};
        	return c;
        }
        if(n==3){
        	vector<int> cnt(3);
        	for(auto&e:qs){
        		cnt[e[0]]++;
        		cnt[e[1]]++;
        	}
        	vector<int> tmp{0,1,2};
        	if(cnt[0]==2){
        		tmp={1,0,2};
        	}else if(cnt[2]==2){
        		tmp={1,2,0};
        	}
        	vector<vector<int>> c{tmp};
        	return c;
        }

        BFS g(n);
        vector<int> p(n);
        for(auto&e:qs){
    		g.add_edge(e[0],e[1]);
    		p[e[0]]++;
    		p[e[1]]++;
    	}

    	if(sz(qs)==n-1) {
    		vector<int> d;
	    	f0(n){
	    		if(p[i]==1){
	    			d.push_back(i);
	    		}
	    	}
	    	vector<vector<int>> c;
	    	c.assign(1,vector<int>(n));

	    	c[0][0]=d[0];
	    	c[0][n-1]=d[1];

	    	auto d1=g.bfs(d[0]);
	    	auto d2=g.bfs(d[1]);

	    	f0(n){
	    		if(d1[i]+d2[i]==n-1){
	    			c[0][d1[i]]=i;
	    		}
	    	}

	    	return c;
    	}



    	vector<int> d;
    	f0(n){
    		if(p[i]==2){
    			d.push_back(i);
    		}
    	}

    	auto d1=g.bfs(d[0]);
    	vector<pair<int,int>> pp;
    	f1(sz(d)){
    		pp.push_back({d1[d[i]],d[i]});
    	}
    	sort(all(pp),[&](auto &x,auto &y){
    		return x.first<y.first;
    	});
    	vector<vector<int>> c;

    	c.assign(pp[0].first+1,vector<int>(pp[1].first+1));

    	int n1=sz(c),m1=sz(c[0]);

    	c[0][0]=d[0];
    	c[0][m1-1]=pp[0].second;

    	vector<int> vis(n);
    	auto d2=g.bfs(c[0][m1-1]);
    	
    	f0(n) {
    		if(d1[i]+d2[i]==m1-1){
    			c[0][d1[i]]=i;
    			vis[i]=1;
    		}
    	}
    	
    	for(int i=1;i<n1;++i) {
    		for(int j=0;j<m1;++j) {
    			int t=c[i-1][j];
    			for(auto &x:g.g[t]) {
    				if(!vis[x]) {
    					vis[x]=1;
    					c[i][j]=x;
    				}
    			}
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
    vector<vector<int>> vv={
    	{0,1},{1,3},{2,3},{2,4}
    };
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    Solution so;
    // rd(a,k);
    int k=9;
    auto ans = so.constructGridLayout(k,vv);
    wt(ans);
    cout<<'\n';
    return 0;
}
#endif
