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
int x, y, k;
string s, t;



int visited[N],dfn[N],low[N],ins[N],stk[N],color[N],top=0,cnt,n,m,stamp=0;
vector<int> V[N],VC[N];
vector<int> scc[N];
 
map<int,vector<int>> blockedmap;  //stk,ins 可以重复利用,ins充当blockedset的作用 先用vector,不对就换set
vector<vector<int>> ans;  //存放结果
void tarjan(int u){
    dfn[u]=low[u]=++stamp;
    stk[++top]=u;
    ins[u]=1;
    for(int i=0;i<V[u].size();i++){
        int v=V[u][i];
        if(!dfn[v]){tarjan(v);low[u]=min(low[u],low[v]);}
        else if(ins[v])
            low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        cnt++; int y;
		do {
			y = stk[top--], ins[y] = 0;
			/*c[y] = cnt, */
			color[y] = cnt,scc[cnt].push_back(y);
		} while (u!= y);
    }
}
 
void stronglycomponent(){
    for(int i=1;i<=n;i++){
        if(!dfn[i]) tarjan(i);
    }
}
 
 
void unlock(int u){
    ins[u]=0;
    if(!blockedmap[u].empty()){
        for(auto e:blockedmap[u]){
            if(ins[e]) unlock(e);
        }
    }
    blockedmap[u].clear();
}
bool Findcycles(int start,int cur){
    //printf("f(%d,%d)\n",start,cur);
    bool f=false;// 是否找到环
    stk[++top]=cur;
    ins[cur]=1;
    for(auto e:VC[cur]){
        if(!visited[e]){
            if(e==start){
            //保存结果
                vector<int> path;
                for(int i=1;i<=top;i++)
                    path.push_back(stk[i]);
                ans.push_back(path);
                f=true;
            }
            else if(!ins[e]){
                //bool flag=Findcycles(start,e);  //不能合并写
                f=(Findcycles(start,e))||f;  //次序不能颠倒
            }
        }
 
    }
    if(f) unlock(cur);
    else{
        for(auto e:VC[cur]){
            if(!visited[e]) blockedmap[e].push_back(cur);
        }
    }
    --top;
    return f;
}


bool ac_yyf(int tt) {
    rd(n,m);
    memset(visited,0,sizeof(int)*(n+1));
    memset(dfn,0,sizeof(int)*(n+1));
    memset(low,0,sizeof(int)*(n+1));
    memset(ins,0,sizeof(int)*(n+1));
    memset(stk,0,sizeof(int)*(n+1));
    memset(color,0,sizeof(int)*(n+1));
    memset(visited,0,sizeof(int)*(n+1));
    blockedmap.clear();
    ans.clear();
    f0(n+1){
    	V[i].clear();VC[i].clear();scc[i].clear();
    }
    top=0,cnt=0,stamp=0;
    f0(m){
    	rd(x,y);
    	V[x].push_back(y);
    }
    stronglycomponent();
    for(int i=1;i<=n;i++){
        for(int j=0;j<V[i].size();j++){
            if(color[i]==color[V[i][j]]){
                VC[i].push_back(V[i][j]);
            }
        }
    }
    memset(ins,0,sizeof(int)*(n+1));
    int startindex=1;
    Findcycles(startindex,startindex);
    visited[startindex]=1;
    for(auto&e:ans){
    	int x=sz(e);
    	while(x%2==0)x/=2;
    	while(x%5==0)x/=5;
    	if(x==1){
    		return 1;
    	}
    }
    return 0;
}
int main() {
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        // ac_yyf(cas);
        cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
