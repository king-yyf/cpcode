#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define fr(i,a,b) for (int i=(a);i<(b);i++)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define yn(cond) if (cond) cout<<"Yes\n"; else cout << "No\n";
#define YN(cond) if (cond) cout<<"YES\n"; else cout << "NO\n";
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<A>& x) {wt(x);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

vector<int> potentialTree(int n, vector<vector<int>> &es) {
    vector<vector<int>> g(n);
    for(auto&e:es){
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    vector<int> p(n), cnt(n), ans(n);
    
    function<void(int, int)> dfs = [&](int u, int fa) {
        for (auto &v: g[u]) if (v != fa) {
            dfs(v, u);
            cnt[u]++;
            if (p[v] > 0) p[u]++;
        }
        if (cnt[u] == 0) p[u] = u % 2;
    }; 

    auto reroot = [&](int u, int v) {
        if (u == -1 || v == -1) return;
        cnt[u]--;
        p[u] = cnt[u] == 0 ? u % 2 : p[u] -= (p[v] > 0);
        p[v] = cnt[v] == 0 ? (p[u] > 0) : p[v] + (p[u] > 0);
        cnt[v]++;
    }; 

    function<void(int, int)> dfs2 = [&](int u, int fa) {
        reroot(fa,u);
        ans[u] = p[u];
        for (auto &v : g[u]) if (v != fa){      
            dfs2(v, u);
        }
        reroot(u,fa);   
    };

    dfs(0, -1);
    dfs2(0,-1);
    return ans;
}

int main() {
    int t,n;
    cin>>t;
    while(t--){
        cin>>n;
        vector<vector<int>> es(n-1,vector<int>(2));
        f0(n-1){
            cin>>es[i][0]>>es[i][1];
        }
        cout<<"\n";
        auto c=potentialTree(n,es);
        cout<<"\n";
        potentialTree1(n,es);
    }
    return 0;
}
