#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
#define f1(e) for(int i=0;i<(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,b,e) for(int i=(b);i<(e);++i)
#define f4(i,b,e,s) for(int i=(b); (s)>0?i<(e):i>(e); i+=(s))
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 10;

class Solution {
public:
    long long maximumSubsequenceCount(string t, string p) {
        int n=sz(t);
        vector<int> s1(n+1),s2(n+1);
        int x=0,y=0;
        f1(n) {
        	x+=t[i]==p[0];
        	y+=t[i]==p[1];
        	s1[i+1]=s1[i]+(t[i]==p[0]);
        	s2[i+1]=s2[i]+(t[i]==p[1]);  	
        }
        if(p[0]==p[1]){
        	long long c=x+1;
        	return c*(c-1)/2;
        }
        long long a=0,b=0;
        f1(n){
        	if(t[i]==p[0]){
        		a+=s2[n]-s2[i+1];
        	}
        	if(t[i]==p[1]){
        		b+=s1[i+1]-s1[0];
        	}
        }
        return max(a+x,b+y);
};