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

const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
class Solution {
  public:
    vector<vector<int>> chefAndWells(int n,int m,vector<vector<char>> &c){
        vector<vector<int>> f(n,vector<int>(m));
        queue<pair<int,int>> p;
        vector<vector<int>> s(n,vector<int>(m));
        for(int i=0;i<n;++i){
        	for(int j=0;j<m;++j){
        		if(c[i][j]=='W'){
        			p.push({i*1000+j,0});
        			s[i][j]=1;
        		}
        	}
        }



        while(!p.empty()){
        	int u=p.front().first,v=p.front().second;
        	p.pop();
        	int x=u/1000,y=u%1000;
        	for(int i=0;i<4;++i){
        		int nx=x+dx[i],ny=y+dy[i];
        		if(nx>=0&&nx<n&&ny>=0&&ny<m){
        			if(s[nx][ny]==1)continue;
        			if(c[nx][ny]=='N'){
        			    s[nx][ny]=1;
        			     continue;
        			}
        			
        			if(c[nx][ny]=='H') {
        				f[nx][ny]=(v+1)*2;
        				p.push({nx*1000+ny,v+1});
        				s[nx][ny]=1;
        			}
        			if(c[nx][ny]=='.'){
        			    p.push({nx*1000+ny,v+1});
        				s[nx][ny]=1;
        			}
        		}
        	}
        }

        for(int i=0;i<n;++i){
        	for(int j=0;j<m;++j){
        		if(c[i][j]=='H'&&f[i][j]==0){
        			f[i][j]=-1;
        		}
        	}
        }
        return f;

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