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
const int N = 505;


template <typename T>
struct PrefixSum2D {
    int n, m;
    vector<vector<T>> a;
    PrefixSum2D(int N, int M) : n(N), m(M), a(N + 1, vector<T>(M + 1, 0)){}
    PrefixSum2D(vector<vector<T>> &A) {
        n = A.size(), m = A[0].size();
        a.assign(n + 1, vector<T>(m + 1, 0));
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j)
                a[i + 1][j + 1] = a[i][j + 1] + a[i + 1][j] - a[i][j] + A[i][j];
    }
    T sum(int x1, int y1, int x2, int y2) { // sum[x1..x2, y1..y2]
        return a[x2 + 1][y2 + 1] - a[x2 + 1][y1] - a[x1][y2 + 1] + a[x1][y1];
    }
};

template <typename T>
struct PrefixDiff2D {
    int n, m;
    vector<vector<T>> a;
    PrefixDiff2D(int N, int M) : n(N), m(M), a(N, vector<T>(M, 0)){}
    PrefixDiff2D(vector<vector<T>> &A) {
        n = A.size(), m = A[0].size();
        a.assign(n, vector<T>(m, 0));
        for (int i = 0; i < n; ++i) 
            for (int j = 0; j < m; ++j)
                add(i, j, i, j, a[i][j]);
    }
    void add(int x1, int y1, int x2, int y2, T c) { // sum[x1..x2, y1..y2]
        a[x1][y1] += c;
        if (y2 + 1 < m) a[x1][y2 + 1] -= c;
        if (x2 + 1 < n) a[x2 + 1][y1] -= c;
        if (x2 + 1 < n && y2 + 1 < m) a[x2 + 1][y2 + 1] += c;
    }
    void get() { // 求操作完成后的矩阵
        for (int i = 1; i < n; ++i) a[i][0] += a[i - 1][0];
        for (int j = 1; j < m; ++j) a[0][j] += a[0][j - 1];
        for (int i = 1; i < n; ++i) for (int j = 1; j < m; ++j)
            a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
    }
};


ios::sync_with_stdio(false); 
cin.tie(nullptr);
cout << fixed << setprecision(10);

int diff[N][N];

class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& qs) {
        mst(diff,0);
        vector<vector<int>> g(n,vector<int> (n));
        for(auto&q:qs){
            int x1=q[0],x2=q[1],y1=q[2],y2=q[3];
            for(int i=x1;i<=x2;++i){
                diff[i][y1]++,diff[i][y2+1]--;
            }
        }
        f0(n){
            for(int j=1;j<=n;++j) diff[i][j]+=diff[i][j-1];
        }
        f0(n)f2(j,n)g[i][j]=diff[i][j];
        return g;
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
    rd(a);
    // auto ans = so.;
    // wt(ans);wt("\n");
    return 0;
}
#endif

