#ifdef LOCAL
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
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
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

class Solution {
public:
    int distinctSequences(int n) {
        vector<vector<ll> > f(7,vector<ll>(n+1));
        for(int i=1;i<=6;++i){
            f[i][1]=1;
        }

        vector<vector<int>> g(7);
        for(int i=1;i<=6;++i){
            for(int j=1;j<=6;++j){
                int t=gcd(i,j);
                if(t==1 && i!=j) g[i].push_back(j);
            }
        }
        for(int i=2;i<=n;++i){
            for(int j=1;j<=6;++j){
                for(auto&x:g[j]){
                    f[j][i]=(f[x][i-1]+f[j][i])%mod;
                    f[j][i]=(f[j][i]-f[j][i-2])%mod;
                }

                // if(i>2) {
                //     for(int k=1;k<=6;++k){
                //         if(gcd(k,j)==1&&k!=j)
                //         f[j][i]=(f[j][i]-f[j][i-2])%mod;
                //     }
                // }
            }

        }

        wt(f);

        vector<int> ff(n+1);

        f1(6){
            for(int j=1;j<=n;++j){
                ff[j]=(ff[j]+f[i][j])%mod;
            }
        }

        long long t=0;
        int b=1,d=n;
        while(d>0){
            t=t+ff[d]*b;
            d-=2;
        }
        return t;
    }
};

#ifdef LOCAL
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
    while(1){
        try{
            // 测试leetcode时，需要修改rd中的参数，
            // 比如 fun(vector<int>&a,int k),写为 rd(v);rd(k);
            rd(n);
            auto ans = so.distinctSequences(n);
            wt(ans);wt("\n");
        } catch (std::exception& e){ break;}
    }
    return 0;
}
#endif



