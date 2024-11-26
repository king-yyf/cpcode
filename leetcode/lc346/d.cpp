#include <bits/stdc++.h>
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
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

vector<vector<int>> modifiedGraphEdges(int n, vector<vector<int>>& edges, int source, int destination, int target) {
    vector<vector<pair<int, int>>> e(n);
    int len = edges.size();
    vector<vector<int>> res, ans;
    int nil = 1e9 + 10;
    auto cmp = [&](const auto &x, const auto &y)->bool{
        return x.first > y.first;
    };
    auto cal = [&](int source, int destination)->int{
        vector<int> vis(n, nil);
        vis[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
        q.push({0, source});
        while(!q.empty()){
            auto d = q.top().first, u = q.top().second;
            q.pop();
            if(vis[u] < d) continue;
            for(auto [v, tmp_d] : e[u]){
                if(vis[v] > d + tmp_d){
                    vis[v] = d + tmp_d;
                    q.push({vis[v], v});
                }
            }
        }
        // for(auto c : vis) cout<<c<<' ';
        // cout<<endl;
        return vis[destination];
    };
    for(auto& s : edges){
        if(s[2] != -1){
            e[s[0]].push_back({s[1], s[2]});
            e[s[1]].push_back({s[0], s[2]});
        }
    } 
    if(cal(source, destination) < target) return ans;
    bool ok = false;
    if(cal(source, destination) == target) ok = true;
    for(int i = 0; i < len; ++i){
        if(!ok){
            if(edges[i][2] == -1){
                e[edges[i][0]].push_back({edges[i][1], 1});
                e[edges[i][1]].push_back({edges[i][0], 1});
                int tmp = cal(source, destination);
                // cout<<tmp<<' ';
                if(tmp == nil){
                    res.push_back({edges[i][0], edges[i][1], 1});
                }
                else if(tmp > target){
                    res.push_back({edges[i][0], edges[i][1], 1});
                }
                else{
                    res.push_back({{edges[i][0], edges[i][1], 1 + target - tmp}});
                    ok = true;
                }
            }
            else res.push_back(edges[i]);
        }
        else{
            if(edges[i][2] == -1){
                res.push_back({edges[i][0], edges[i][1], nil});
            }
            else res.push_back(edges[i]);
        }
    }
    if(!ok) return ans;
    return res;                          
}

void ac_yyf(int tt) {
    int s,t,L;
    rd(n,m,L,s,t);
    vector<vector<int>> es(m);
    f0(m){
    	int u,v,w;
    	cin>>u>>v>>w;
    	if(w==0)w--;
    	es[i]={u,v,w};
    }
    auto ans=modifiedGraphEdges(n,es,s,t,L);
    if(sz(ans)==0){
    	cout<<"NO\n";
    }else{
    	cout<<"YES\n";
    	for(auto v:ans){
    		dbg(v[0],v[1],v[2]);
    	}
    }
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
