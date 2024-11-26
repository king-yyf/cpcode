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

struct DSU {
    vector<int> p, siz;
    DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) { return siz[get(x)]; }
    vector<vector<int>> groups() {
        vector<vector<int>> res(p.size());
        for (int i = 0; i < p.size(); i++) res[get(i)].push_back(i);
        res.erase(
            remove_if(res.begin(), res.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
};


void ac_yyf(int tt) {
    rd(n,k);
    vector<int> a(n);
    rd(a);
    vector<array<int,2>> es(n-1);
    for(int i=0;i<n-1;++i){
    	cin>>es[i][0]>>es[i][1];
    	es[i][0]--,es[i][1]--;
    }
    int l=1,r=(*max_element(a.begin(), a.end())),res=-1;
    while(l<=r){
    	int md=(l+r)/2;
    	DSU d(n);
    	vector<vector<int>> g(n);
    	for(auto&e:es){
    		if(a[e[0]]<=md&&a[e[1]]<=md){
    			d.merge(e[0],e[1]);
    			g[e[0]].push_back(e[1]);
    			g[e[1]].push_back(e[0]);
    		}
    	}
    	int ans,t;
    	auto bfs=[&](int rt) {
    		vector<bool> p(n);
    		queue<int> q;
    		q.push(rt);
    		p[rt]=true;
    		while(sz(q)) {
    			auto u=q.front();q.pop();
    			t=u;
    			for(int v:g[u]){
    				if(!p[v]){
    					q.push(v);
    					p[v]=true;
    				}
    			}
    		}
    		p=vector<bool>(n,false);
    		q.push(t);p[t]=true;
    		while(sz(q)){
    			m=sz(q);
    			f0(m){
    				int u=q.front();q.pop();
    				for(int v:g[u]){
    					if(!p[v]){
    						q.push(v);
    						p[v]=true;
    					}
    				}
    			}
    			ans++;
    		}

    	};
    	bool o=0;
    	vector<int> vis(n);
    	f0(n){
    		int x=d.get(i);
    		if(vis[x]) continue;
    		if(d.size(x)<=k)continue;
    		ans=0;
    		bfs(x);
    		vis[x]=1;
    		if(ans>k){
    			o=1;break;
    		}
    	}
    	if(o){
    		res=md;
    		r=md-1;
    	}else l=md+1;
    }
    cout<<res<<"\n";
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
