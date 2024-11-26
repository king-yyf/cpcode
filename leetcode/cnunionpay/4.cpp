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
    int coopDevelop(vector<vector<int>>& ss) {
    	long long s=0;
    	vector<vector<int>> s1,s2,s3,s4;
    	for(auto&e:ss){
    		int t=sz(e)
    		if(t==1) s1.push_back(e);
    		else if(t==2) s2.push_back(e);
    		else if(t==3) s3.push_back(e);
    		else s4.push_back(e);
    	}

    	int n1=sz(s1);
    	map<int,int> mp;
    	f1(n1){
    		s+=(i+1-mp[s1[i][0]]);
    		s%=mod;
    		mp[s1[i]]++;
    	}
    	int n2=sz(s2);
    	map<int,int> m2;
    	f1(n2){
    		s+=(n1-mp[s2[i][0]]-mp[s2[i][1]]);
    		s+=(i+1-m2[s2[i][0]*10000+s2[i][1]]);
    		s%=mod;
    		m2[s2[i][0]*10000+s2[i][1]]++;
    	}
    	int n3=sz(s3);
    	mp<long long ,int> m3;
    	f1(n3){
    		int x=s3[i][0],y=s3[i][1],z=s3[i][2];
    		s+=(n1-mp[x]-mp[y]-mp[z]);
    		s+=(n2-m2[x*10000+y]-m2[x*10000+z]-m2[y*10000+z]);
    		s+=(i+1-m3[x*10000*10000+y*10000+z]);
    		s%=mod;
    		m3[x*10000*10000+y*10000+z]++;
    	}
    	int n4=sz(s4);
    	f1(n4){
    		
    	}
    }
};