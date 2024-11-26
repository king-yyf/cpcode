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

class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& a, vector<vector<int>>& b) {
        vector<pair<int,int>> c1,c2;

        auto get=[&](vector<vector<int>>& a,vector<pair<int,int>>& c1) ->bool{
        	int n=sz(a);
        vector<set<int>> g(k+1);
        vector<int> d(k+1);
        f0(n){
        	int x=a[i][0],y=a[i][1];
        	if(!g[x].count(y)){
        		g[x].insert(y);
        		d[y]++;
        	}
        	
        }
        // for(auto&[x,v]:g){
        // 	for(auto&c:v) {
        // 		d[c]++;
        // 	}
        // }
        queue<pair<int,int> > q;
        
        int t=0;
        f1(k){
        	if(d[i]==0){
        		q.push({i,0});
        	}
        }
        set<int> s1;
        while(sz(q)){
        	auto [x,y]=q.front();
        	c1.push_back({x,y});
        	s1.insert(x);
        	q.pop();
        	for(auto&v:g[x]){
        		if(--d[v]==0){
        			q.push({v,y+1});
        		}
        	}
        }
        if(sz(s1)<k) return false;
        return true;

        };


        auto b1=get(a,c1);
        if(!b1) return {};
        auto b2=get(b,c2);
        if(!b2) return {};

        sort(all(c1),[&](auto x,auto y){
        	return x.se<y.se;
        });

        sort(all(c2),[&](auto x,auto y){
        	return x.se<y.se;
        });

        vector<int> row(k+1),col(k+1);

        int t=0;

        for(auto&[x,y]:c1){
        	row[x]=t++;
        }

        t=0;

        for(auto&[x,y]:c2){
        	col[x]=t++;
        }

        vector<vector<int>> ans(k,vector<int>(k));

        f1(k){
        	ans[row[i]][col[i]]=i;
        }
        return ans;
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



