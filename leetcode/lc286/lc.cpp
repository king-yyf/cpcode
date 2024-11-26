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

// long long  qpow(long long m, long long k, long long p) {
//     long long res = 1 % p, t = m;
//     while (k) {
//         if (k&1) res = res * t % p;
//         t = t * t % p;
//         k >>= 1;
//     }
//     return res;
// }

class Solution {
public:
	struct W{
		int x,y,z;
		bool operator <(const&W o)const{
			return x<o.x;
		}
	};
    int maxValueOfCoins(vector<vector<int>>& a, int k) {
        int s=0,n=a.size();
        vector<vector<int>> dp(n+1,vector<int>(k+1)),sm(n);
        for(int i=0;i<n;++i){
        	sm[i].push_back(0);
        	for(int j=0;j<a[i].size();++j){
        		sm[i].push_back(sm[i].back()+a[i][j]);
        	}
        }
        for(int i=0;i<n;++i){
        	for(int j=1;j<=a[i].size();++j){
        		for(int l=1;l<=j;++l){
        			dp[i+1][j]=max(s[i][l],dp[i-1][j-l]);
        		}
        	}
        }
        return s;
    }
};