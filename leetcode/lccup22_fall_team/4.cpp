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
    int Leetcode(vector<string>& ws) {
    	string s="helloleetcode";
    	map<char,int> mp;
    	each(x,s)mp[x]++;
    	map<char,int> m1;
    	each(t,ws){
    		each(c,t)m1[c]++;
    	}
    	for(auto&[x,y]:mp){
    		if(!m1.count(c)||m1[c]<y) return -1;
    	}
    	multiset<pair<int,int>> s;
    	map<int,int> m2;
    	int n=sz(ws);
    	f0(n){
    		for(int j=0;j<sz(ws[i]);++j){
    			int t=i*100+j;
    			int c=j*(sz(ws[i])-j-1);
    			if(mp.count(ws[i][j]))
    			{
    				s.insert({c,t});
    				m2[t]=c;
    			}
    		}
    	}
    	int ans=0;

    	while(!s.empty()) {
    		auto it=s.begin();
    		int c=it->first, x=(it->second)/100,y=(it->second)%100;
    		if(mp.count(ws[x][y])){
    			mp[ws[x][y]]--;
    			if(mp[ws[x][y]]==0) mp.erase(ws[x][y]);
    			ans+=c;
    			string &s1=ws[x];
    		    for(int i=0;i<sz(s1);++i){
    			    int t=x*100+i;
    			    int c=m2[t];
    			    auto it1=s.find({c,t});
    			    s.erase(it1);
    			    m2.erase(t);
    		    }
    		    s1=s1.erase(s1.begin()+x);
    		    for(int i=0;i<sz(s1);++i){
    		    	int t=x*100+i;
    			    int c=m2[t];
    			    if(mp.count(s1[i])){
    			    	s.insert({c,t});
    			    	m2[t]=c;
    			    }
    			    
    		    }
    		    s1.erase(s1.begin()+x);

    		}
    		if(mp.empty())break;
    		// s.erase(it);
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
