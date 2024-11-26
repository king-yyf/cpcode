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
    vector<int> longestRepeating(string s, string qs, vector<int>& ds) {
        int k=sz(qs),n=sz(s);
        vector<int> c(k),l(n),r(n);
        f1(n){
        	if(i>0&&s[i]==s[i-1]) l[i]=l[i-1]+1;
        	else l[i]=1;
        }
        for(int i=n-1;i>=0;--i){
        	if(i<n-1&&s[i]==s[i+1])r[i]=r[i+1]+1;
        	else r[i]=1;
        }
        map<int,int> mp;
        multiset<int> st;
        f1(n){
        	if(i>0&&s[i]==s[i-1])continue;
        	mp[i]=l[i]+r[i]-1;
        	st.insert(l[i]+r[i]-1);
        }
        mp[-1]=mp[n+1]=0;
        f1(k){
        	int x=ds[i];
        	char t=s[x],q=qs[i];
        	if(s[x]==q){
        		c[i]=*(st.rbegin());
        		continue;
        	}
        	s[x]= q;
        	auto it=mp.upper_bound(x);
        	it--;
        	int p=it->first,d=it->second;
        	auto pre=it,nxt=it;
        	pre--;
        	nxt++;
        	st.erase(st.find(d));
        	if(d==1){
        		int cnt=0;
        		if(pre->first>=0&&s[pre->first]==q && nxt->first<n&&s[nxt->first]==q){
        			cnt=pre->second+1+nxt->second; 
        			int a=pre->first, b=it->first, e=nxt->first;
        			st.erase(st.find(pre->second));
        			st.erase(st.find(nxt->second));
        			mp.erase(a);mp.erase(b);mp.erase(e);
        			mp[a]=cnt;
        			
        			st.insert(cnt);
        		}else if(pre->first>=0&&s[pre->first]==q){
        			cnt=pre->second+1; 
        			int a=pre->first, b=it->first;
        			st.erase(st.find(pre->second));
        			st.insert(cnt);
        			mp.erase(a);mp.erase(b);
        			mp[a]=cnt;
        			
        		}else if(nxt->first<n&&s[nxt->first]==q){
        			cnt=nxt->second+1; 
        			int a=nxt->first, b=it->first;
        			st.erase(st.find(nxt->second));
        			st.insert(cnt);
        			mp.erase(a);mp.erase(b);
        			mp[b]=cnt;
        		}
        	}else if(x==p){
        		if(pre->first>=0&&s[pre->first]==q){
        			cnt=pre->second+1; 
        			int a=pre->first, b=it->first;
        			st.erase(st.find(pre->second));
        			st.erase(st.find(d));
        			st.insert(cnt);
        			st.insert(d-1);
        			mp.erase(a);mp.erase(b);
        			mp[a]=cnt;
        			mp[p+1]=d-1;
        		}
        	}else if(x==p+d-1){
        		if(nxt->first<n&&s[nxt->first]==q){
        			cnt=nxt->second+1; 
        			int a=nxt->first, b=it->first;
        			st.erase(st.find(nxt->second));
        			st.erase(st.find(d));
        			st.insert(cnt);
        			st.insert(d-1);
        			mp.erase(a);mp.erase(b);
        			mp[x]=cnt;
        			mp[p]=d-1;
        		}
        	}else {
        		st.erase(d);
        		mp.erase(it);
        		st.insert(x-p);
        		st.insert(d-x+p-1);
        		mp[p]=x-p;
        		mp[x+1]=d-x+p-1;
        		mp[x]=1;
        	}

        	c[i]=*(st.rbegin());

        }
        return c;
    }
};