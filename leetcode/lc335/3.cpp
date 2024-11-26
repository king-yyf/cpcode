#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define yn(cond) cout << ((cond) ? "Yes" : "No") << "\n";
#define YN(cond) cout << ((cond) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI = acos(-1.0);
const int N = 2e5 + 5;

vector<pair<int,int>> getDivisors(int x) {
    vector<pair<int,int>> res;
    for (int i = 2, t = sqrt(x); i <= t; ++i) {
        if (x % i == 0) {
            int s = 0;
            while (x % i == 0) 
                x /= i, s++;
            res.emplace_back(i,s);
        }
    }
    if (x > 1) res.emplace_back(x,1);
    return res;
}
class Solution {
public:
    int findValidSplit(vector<int>& a) {
        map<int,int> mp,m2;
        int n=sz(a);
        vector<vector<pair<int,int>> > g(n);
        f0(n) {
        	if(m2.count(a[i])){
        		g[i]=g[m2[a[i]]];
        	}
           	else {
           		g[i]=getDivisors(a[i]);
           		m2[a[i]]=i;
           	}

        	for(auto &[x,y]:g[i]){
        		mp[x]+=y;
        	}
        }
        int t=0,c=-1;
        set<int> s;
        f0(n-1){
        	for(auto &[x,y]:g[i]){
	    		s.insert(x);
	    		mp[x]-=y;
	    		if(mp[x]==0){
	    			mp.erase(x);
	    			t++;
	    		}
	    	}
	    	if(s.size()==0||t==s.size()||mp.size()==0){
	    		c=i;break;
	    	}
        }
        return c;
    }
};

#ifdef sigma-yyf
int main(){
    Solution so;
    int n,k=3,m,x;

    vector<int> a{4,7,8,15,3,5};
    auto p=so.findValidSplit(a);
    wt(p);
    // 测试leetcode时，需要修改rd中的参数，
    // 比如 fun(vector<int>&a,int k),写为 rd(v);rd(k);
    // rd(root);
    // auto ans = so.;
    // wt(ans);wt("\n");
    return 0;
}
#endif
