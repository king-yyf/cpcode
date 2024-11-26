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
    int countHillValley(vector<int>& a) {
        int n=a.size();
        int c=0;
        for(int i=1;i<n-1;++i){
        	if(a[i]==a[i-1])continue;
        	int j=i;
        	while(j>=0&&a[j]==a[i])j--;
        	if(j<0)continue;
        	int k=i;
        	while(k<n&&a[k]==a[i])k++;
        	if(k>=n)continue;

        	if(a[i]>a[j]&&a[i]>a[k]) c++;
        	else if(a[i]<a[j]&&a[i]<a[k])c++;
        }
        return c;
    }
};