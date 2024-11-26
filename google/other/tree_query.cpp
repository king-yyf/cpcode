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
#define fi first
#define se second
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

const int mod = 1e9+7; // 998244353;
const double PI = acos(-1.0);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;


vector<int> treeQuerys(vector<int> &a, vector<vector<int>> &es, vector<vector<int>> &qs) {
    int n = a.size(), m = qs.size();
    vector<vector<int>> g(n), s(n);
    vector<priority_queue<int, vector<int>, greater<int>>> p(n);

    for(auto& e: es) {
    	g[e[0]].push_back(e[1]);
    	g[e[1]].push_back(e[0]);
    }

    function<void(int, int)> dfs = [&](int u, int fa) {
        p[u].push(a[u]);
        for (auto &v : g[u]) {
            if (v == fa) continue;
            dfs(v, u);
            auto q = p[v];
            while(!q.empty()) {
                p[u].push(q.top()); 
                q.pop();
                if(p[u].size() > 20) p[u].pop();
            }
        }
    };

    dfs(0, -1);

    for (int i = 0; i < n; ++i) {
        while(p[i].size()) {
            s[i].push_back(p[i].top());
            p[i].pop();
        }
        sort(rall(s[i]));
    }

    vector<int> ans(m);
    for (int i = 0; i < m; ++i) {
        int v = qs[i][0], k = qs[i][1];
        ans[i] = s[v][k - 1];
    }
    return ans;
}


void solve(int tt) {
    rd(n,q);
    vector<int> a(n);
    f0(n){
    	rd(x);a[i]=x;
    }
    vector<vector<int>> qs,es;
    f0(n-1){
    	rd(x,y);
    	x--,y--;
    	es.push_back({x,y});
    }
    f0(q){
    	rd(x,y);
    	x--;
    	qs.push_back({x,y});

    }
    auto ans=treeQuerys(a,es,qs);
    wt(ans);
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
