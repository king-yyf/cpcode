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

template <class T, T (*op)(T, T)>
class ST {
 public:
  int n;
  vector<vector<T>> mat;
 
  ST(const vector<T>& a) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = op(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
 
  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return op(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};
int op(int x,int y) {return max(x,y);}



int maxCoins(int n,vector<vector<int>> &a){
    int mx=0;
    sort(all(a),[&](auto &x, auto &y){
        if(x[1]!=y[1]) return x[1]<y[1];
        return x[0]<y[0];
    });
    for(int i=0;i<n;++i)
        mx=max(mx,a[i][2]);
    vector<int> c;
    for(int i=0;i<n;++i)
        c.push_back(a[i][2]);
    ST<int,op> s1(c);
    for(int i=0;i<n;++i){
        int l=0,r=i-1,t=-1;
        while(l<=r){
            int md=(l+r)/2;
            if(a[md][1]<=a[i][0]){
                t=md;
                l=md+1;
            }else r=md-1;
        }
        if(t>-1){
            int d=s1.get(0,t);
            mx=max(mx,d+a[i][2]);
        }
    }
    return mx;
}

int main(){
    int n=5;
    vector<vector<int>> a{{1,3,4},{2,3,5},{3,4,2},{5,8,9},{2,8,10}};
    auto c=maxCoins(n,a);
    wt(c);
    
    return 0;
}
