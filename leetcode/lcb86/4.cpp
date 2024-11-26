#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define ln "\n";
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) {cout << x << " ";}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void wt(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void wt(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;
struct w {
    int x;  int y;
    bool operator < (const w& o) const {
        return x!=o.x ? x<o.x : y<o.y;
    }
};

const int MAXN = 1010;
int lg[MAXN];
void init() {
    lg[0] = -1;
    for (int i = 1; i < MAXN; ++i) {
        lg[i] = lg[i >> 1] + 1;
    }
}
template<int opt(int, int)>
struct ST {
    const static int MAXN = 200000;
    int u[MAXN][20], n;
    static int lg[MAXN];

    static void init() {
        lg[0] = -1;
        for (int i = 1; i < MAXN; ++i) {
            lg[i] = lg[i >> 1] + 1;
        }
    }

    void build(int a[], int n) {
        this->n = n;
        for (int i = 0; i < n; ++i) u[i][0] = a[i];
        for (int j = 1; (1 << j) <= n; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                u[i][j] = opt(u[i][j - 1], u[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int ask(int a, int b) {
        if (a > b) std::swap(a, b);
        int k = lg[b - a + 1];
        return opt(u[a][k], u[b - (1 << k) + 1][k]);
    }
};
// int op(int x,int y) {return max(x,y);}
// ST<op> s1;


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

int op(int x, int y) {
    return max(x, y);
}
class Solution {
public:
    int maximumRobots(vector<int>& a, vector<int>& b, long long t) {
        int n=sz(a);
        int c=0;
        ST<int,op> st(a);
        vector<long long> s(n+1);
        f0(n)s[i+1]=s[i]+b[i];
        f0(n){
        	int l=i,r=n-1,mx=-1;
        	while(l<=r){
        		int md=(l+r)/2;
        		long long p=st.get(i,md)+(md-i+1ll)*(s[md+1]-s[i]);
        		if(p<=t){
        			mx=md;
        			l=md+1;
        		}else{
        			r=md-1;
        		}
        	}
        	if(mx!=-1){
        		c=max(c,mx-i+1);
        	}
        }
        return c;
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



