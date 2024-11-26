#include<bits/stdc++.h>
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


long long minTime(int n, vector<int> &a, vector<int> &b) {
    map<int,vector<int> > mp;
    for(int i=0;i<n;++i){
        mp[b[i]].push_back(a[i]);
    }
    int m=sz(mp);
    vector<vector<long long >> dp(m+1,vector<long long >(2));

    int lst=0;

    auto abs=[&](long long x){
        if(x>=0)return x;
        return -x;
    };
    int i=0;
    
    long long lt,rt;
    for(auto&p:mp){
        auto &v=p.second;
        sort(all(v));
        long long t=v.back()-v[0];
        if(i==0){
            dp[1][0]=min(2*t+abs(v[0]),abs(v.back())+t);
            dp[1][1]=min(2*t+abs(v.back()),abs(v[0])+t);
        }else{
            dp[i+1][0]=min(dp[i][0]+min(2*t+abs(v[0]-lt),abs(v.back()-lt)+t),dp[i][1]+min(2*t+abs(v[0]-rt),abs(v.back()-rt)+t));
            dp[i+1][1]=min(dp[i][0]+min(2*t+abs(v.back()-lt),abs(v[0]-lt)+t),dp[i][1]+min(2*t+abs(v.back()-rt),abs(v[0]-rt)+t));
        }
        lt=v[0],rt=v.back();
        i++;
    }
    long long ans=min(dp[m][0]+abs(lt),dp[m][1]+abs(rt));

    return ans;
}

int main(){
    
    vector<int> a{-1, 9, 4, 9, -10, 0, 4, 5, -9};
    vector<int> b{2, 4 ,3, 3, 2, 4, 3, 3, 1};
    int n=sz(a);
    auto c=minTime(n,a,b);
    wt(c);
    
    return 0;
}
