#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

int bct(long long x){return __builtin_popcountll(x);}
int lg2(int x){return x==0?0:31-__builtin_clz(x);} //x>=0, floor(log2(x)) 
long long fbs(function<bool(long long)> f, long long& lb, long long rb) {  // first true binary search
    while(lb<rb) {
        long long mb=(lb+rb)/2;
        f(mb)?rb=mb:lb=mb+1; 
    } 
    return lb;
}
long long lbs(function<bool(long long)> f, long long& lb, long long rb) {  // last true binary search
    while(lb<rb) {
        long long mb=(lb+rb+1)/2;
        f(mb)?lb=mb:rb=mb-1; 
    } 
    return lb;
}

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) { cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    bool f=1;
    each(a, x) if(f==1) {wt(a); f=0;} else {cout<<' ';wt(a);}
}
const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n,m,x,y,k,q;
int a[N],b[N];

void solve(){
    cin>>n;
    f0(n)cin>>a[i];
    f0(n)cin>>b[i];
    cin>>q;
    vector<tuple<int,int,int>> p;
    vector<int> ans(q);
    f0(q){
        cin>>x>>y;
        x--,y--;
        p.push_back({x,y,i});
    }
    sort(all(p));
    // vector<int> c(n);
    set<int> s1,s2;
    int i=0,j=0;
    map<int,int> mp,m2;
    for(auto &[x,y,k]:p){
        while(i<=x) {
            s1.insert(a[i]);
            i++;
        }
        if(s1.size()==s2.size()){
            auto it=mp.rbegin(),it1=m2.rbegin();
            mp[x]=it->second;
            m2[x]=it1->second;
            continue;
        }

        while(j<n) {
            if(!s1.count(b[j])) {
                mp[x]=-1;
                break;
            }
            s2.insert(b[j]);
            j++;
            if(s2.size()==s1.size()) {
                mp[x]=j-1;
                while(j<n&&s2.count(b[j])){
                    j++;
                }
                m2[x]=j-1;
                break;
            }
        }
        if(s1.size()!=s2.size()) 
        mp[x]=-1;
    }

    for(auto &[x,y,k]:p){
        int t=mp[x],f=m2[x];
        if(t!=-1 && f!=-1 &&y>=t&&y<=f)ans[k]=1;
    }
    f0(q){
        if(ans[i])wt("Yes\n");
        else wt("No\n");
    }

}
int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout<<fixed<<setprecision(20);
    solve();
    return 0;
}
