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
        vector<T> d(n, T(-1e9)); 
        priority_queue<E> q;
        d[s] = 0;
        q.emplace(0, s);
        while (!q.empty()) {
            auto [cost, u] = q.top();
            q.pop();
            if (d[u] > cost) continue;
            for (auto &[c, v] : g[u]) {
                if (d[u] + c > d[v]) {
                    d[v] = d[u] + c;
                    q.emplace(d[v], v);
                }
            }
        } 
        return d;
    }
};

void ac_yyf(int tt) {
    cin>>n;
    vector<vector<char>> g(n,vector<char>(3));
    f0(n)rd(g[i]);
    // Dijkstra<int> d(n*3+1);
    // int s=n*3;
    auto get=[&](int x,int y){
    	return x*3+y;
    };

    vector<vector<int>> f(n,vector<int> (3,-1e9));

    for(int i=0;i<3;++i){
    	if(g[n-1][i]=='#'){
    		// d.add_edge(s,get(n-1,i),0);
    		f[n-1][i]=0;
    	}
    	if(g[n-1][i]=='c'){
    		f[n-1][i]=1;
    		// d.add_edge(s,get(n-1,i),1);
    	}
    }
    for(int i=n-1;i>0;--i){
    	for(int j=0;j<3;++j){
    		if(g[i][j]!='*'){
    			for(int k=-1;k<=1;++k){
    				int x=i-1,y=j+k;
    				if(j>=0&&j<3){
    					if(g[x][y]=='#'){
    						f[x][y]=max(f[x][y],f[i][j]);
    					}
    					if(g[x][y]=='c'){
    						f[x][y]=max(f[x][y],f[i][j]+1);
    					}
    				}
    			}
    		}
    	}
    }

    // auto p=d.dijkstra(s);
    int mx=0;
    f0(n)f2(j,3)cmx(mx,f[i][j]);
    // for(auto&x:p)cmx(mx,x);
    	wt(mx,'\n');
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
