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
const int N = 2e5 + 5;

class Solution {
public:
    int takeCharacters(string s, int k) {
        int n=s.size();
        vector<int> p1(n+1),p2(n+1),p3(n+1);
        for (int i = 0; i < n; ++i) {
            p1[i+1]=p1[i]+(s[i]=='a');    
        }
        for (int i = 0; i < n; ++i) {
            p2[i+1]=p2[i]+(s[i]=='b');    
        }
        for (int i = 0; i < n; ++i) {
            p3[i+1]=p3[i]+(s[i]=='c');    
        }
        int c=-1;
        int l=0,r=n;
        while(l<=r){
            int md=(l+r)/2;
            bool o=0;
            for(int i=0;i<=md;++i){
                //l:i,r:md-i
                bool o1=1;
                int x1=p1[i],y1=p1[n]-p1[n-(md-i)];
                if(x1+y1<k)o1=0;
                x1=p2[i],y1=p2[n]-p2[n-(md-i)];
                if(x1+y1<k)o1=0;
                x1=p3[i],y1=p3[n]-p3[n-(md-i)];
                if(x1+y1<k)o1=0;
                if(o1){
                    o=1;break;
                }
            }
            if(o){
                c=md;
                r=md-1;
            }else l=md+1;
        }
        return c;
    }
};

#ifdef sigma-yyf
int main(){
    // Solution so;
    int n,k=3,m,x;
    long long l,r;
    string s,t;
    vector<int> v,a,b; 
    vector<string> sv;
    vector<vector<int>> vv;
    ListNode* head = nullptr, *l1,*l2;
    TreeNode* root = nullptr,*p,*q;
    // 测试leetcode时，需要修改rd中的参数，
    // 比如 fun(vector<int>&a,int k),写为 rd(v);rd(k);
    rd(a);
    // auto ans = so.dividePlayers(a);
    // wt(ans);wt("\n");
    return 0;
}
#endif