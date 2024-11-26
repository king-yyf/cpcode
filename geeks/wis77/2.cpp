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

const int mod = 1e9+7; // 998244353;
const double PI = acos(-1.0);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};

bool minimumPlatform2(vector<int> &a,vector<int> &b,vector<int> &d,int p){
    int n=a.size();
    int mx=0;
    for(auto&x:d)
        mx=max(mx,x);
    vector<vector<pair<int,int>>> v(mx+1);
    for(int i=0;i<n;++i){
        v[d[i]].push_back({a[i],b[i]});
    }

    auto get=[&](vector<pair<int,int>> &c){
        vector<pair<int,int>> t;
        for(auto&x:c){
            t.push_back({x.first,1});
            t.push_back({x.second,-1});
        }
        sort(t.begin(), t.end());
        int ans=0,q=0;
        for(auto&it:t){
            q+=it.second;
            ans=max(ans,q);
        }
        return ans;
    };

    bool o=1;
    for(int i=0;i<=mx;++i){
        auto &e=v[i];
        int res=get(e);
        if(res>p){
            o=0;break;
        }
    }
    return o;
}

int main() {
    vector<int> a{900, 940, 950, 1100, 1500, 1800};
    vector<int> b{910, 1200, 1120, 1130, 1900, 2000};
    vector<int> d{1, 2, 2, 1, 3, 4};
    int p=2;
    cout<<minimumPlatform2(a,b,d,p)<<"\n";
    return 0;
}
