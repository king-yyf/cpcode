#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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



typedef long long ll;
vector<vector<ll>>adj;
const ll K=20;
const ll N=1e5;
vector<ll>A;
ll anc[N+1][K],mxe[N+1][K],dp[N+1];
void dfs(ll src,ll p,ll d){
    dp[src]=d;
    anc[src][0]=p;
    mxe[src][0]=max(A[src],A[p]);
    for(ll i=1;i<K;i++){
        anc[src][i]=anc[anc[src][i-1]][i-1];
        mxe[src][i]=max(mxe[src][i-1],mxe[anc[src][i-1]][i-1]);
    }
    for(auto & x:adj[src]){
        if(x==p)continue;
        dfs(x,src,d+1);
    }
} 

bool isBitSet(int d, int i){
    return (d>>i)&1;
}

bool query(ll u,ll d){
    if(d==0)return true;
    ll ma=0;
    ll st=A[u];
    for(ll i=K-1;i>=0;i--){
        if(isBitSet(d,i)){
            ma=max(ma,mxe[u][i]);
            u=anc[u][i];
        }
    }
    if(ma<=st)return 1;
    return 0;
}
ll node(ll u,ll d){
    if(d==0)return u;
    for(ll i=K-1;i>=0;i--){
        if(isBitSet(d,i)){
            u=anc[u][i];
        }
    }
    return u;
}

class Solution {
public:
    int numberOfGoodPaths(vector<int>& a, vector<vector<int>>& es) {
        int n=a.size();
        adj.assign(n+1,{});
        A.assign(n+1,0);
        for(int i=1;i<=n;++i)A[i]=a[i-1];
        for(auto&e:es){
            adj[e[0]+1].push_back(e[1]+1);
            adj[e[1]+1].push_back(e[0]+1);
        }
        vector<vector<int>> V(n+1);
        dfs(1,1,0);
        for(ll i=1;i<=n;i++){
            ll dep=dp[i];
            ll l=0,r=dep,ans,mid;
            while(l<=r){
                mid=(l+r)/2;
                if(query(i,mid)){
                    l=mid+1;
                    ans=mid;
                }
                else {
                    r=mid-1;
                }
            }
            ll p=node(i,ans);
            V[p].push_back(i);
          }
          
          ll ans=0;
          for(ll i=1;i<=n;i++){
            map<ll,ll>mp;
            if(V[i].size()<=1)continue;
            for(auto & x:V[i]){
                mp[A[x]]++;
            }
            for(auto & x:mp){
                ll c=x.second;
                ans+=(c*(c-1))/2;
            }
          }
          return ans+n;

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
    rd(root);
    // auto ans = so.;
    // wt(ans);wt("\n");
    return 0;
}
#endif
