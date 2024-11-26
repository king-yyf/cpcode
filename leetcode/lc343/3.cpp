#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const int N = 2e5 + 5;

template<typename T>
struct Dijkstra {
    using E = pair<T, int>;
    int n;
    vector<vector<E>> g;    // cost, to
    Dijkstra(int N) : n(N), g(N) {}

    void add_edge(int u, int v, T cost) {
        g[u].emplace_back(cost, v);
    }

    void add_bidir_edge(int u, int v, T cost) {
        add_edge(u, v, cost);
        add_edge(v, u, cost);
    }

    vector<T> dijkstra(int s) {  // unreachable : -1
        vector<T> d(n, T(-1)); 
        priority_queue<E, vector<E>, greater<E>> q;
        d[s] = 0;
        q.emplace(0, s);
        while (!q.empty()) {
            auto [cost, u] = q.top();
            q.pop();
            if (d[u] < cost) continue;
            for (auto &[c, v] : g[u]) {
                if (d[v] == T(-1) || d[u] + c < d[v]) {
                    d[v] = d[u] + c;
                    q.emplace(d[v], v);
                }
            }
        } 
        return d;
    }
};


class Solution {
public:
    int minimumCost(vector<int>& sr, vector<int>& tr, vector<vector<int>>& ss) {
        unordered_map<pair<int,int>,int>mp;
        unordered_map<int,pair<int,int> > m2;
        int t=0;
        if(sr==tr)return 0;
        mp[{sr[0],sr[1]}]=t++;
        m2[0]={sr[0],sr[1]};
        mp[{tr[0],tr[1]}]=t++;
        m2[1]={tr[0],tr[1]};

        for(auto&e:ss){
        	if(!mp.count({e[0],e[1]})) {
        		m2[t]={e[0],e[1]};
        		mp[{e[0],e[1]}]=t++;
        	}
        	if(!mp.count({e[2],e[3]})) {
        		m2[t]={e[2],e[3]};
        		mp[{e[2],e[3]}]=t++;
        	}
        }

        vector ds(t,vector<int>(t)); 


        Dijkstra<ll> g(t);
        auto get=[&](pair<int,int>  x, pair<int,int>  y){
        	return abs(x.first-y.first)+abs(x.second-y.second);
        };

        f0(t){
        	for(int j=i+1;j<t;++j){
        		ds[i][j]=ds[j][i]=get(m2[i],m2[j]);
        	}
        }

         for(auto&e:ss){
         	
         	pair<int,int>  p1={e[0],e[1]},p2={e[2],e[3]};
         	int i=mp[p1],j=mp[p2];
         	if(e[4]<ds[i][j]){
         		ds[i][j]=e[4];
         	}
         	
        	// g.add_bidir_edge(0,mp[{e[0],e[1]}],get(s,{e[0],e[1]}));
        	// g.add_bidir_edge(0,mp[{e[2],e[3]}],get(s,{e[2],e[3]}));
        	// g.add_bidir_edge(mp[{e[0],e[1]}],1,get(p,{e[0],e[1]}));
        	// g.add_bidir_edge(mp[{e[2],e[3]}],1,get(p,{e[2],e[3]}));
        	// g.add_bidir_edge(mp[{e[0],e[1]}],mp[{e[2],e[3]}],e[4]);
        }

        f0(t){
        	f2(j,t){
                if(i!=j)
        		g.add_edge(i,j,ds[i][j]);
        	}
        }

        auto d=g.dijkstra(0);
        return d[1];

    }
};

#ifdef sigma-yyf
int main(){
    Solution so;
    int n,k=3,m,x;
    long long l,r;
    string s,t;
    vector<int> v,a,b; 
    vector<string> sv;
    vector<vector<int>> vv;
    ListNode* head = nullptr, *l1,*l2;
    TreeNode* root = nullptr,*p,*q;
    cout<<"\n";
    // 测试leetcode时，需要修改rd中的参数，
    // 比如 fun(vector<int>&a,int k),写为 rd(v);rd(k);
    // rd(root);
    // auto ans = so.;
    // wt(ans);wt("\n");
    return 0;
}
#endif

