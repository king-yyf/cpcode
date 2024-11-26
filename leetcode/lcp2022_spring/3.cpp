#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

int bct(long long x){return __builtin_popcountll(x);}
int lg2(int x){return x==0?0:31-__builtin_clz(x);} //x>=0, floor(log2(x)) 
long long fbs(function<bool(long long)> f, long long& lb, long long rb) {  // first true binary search
    while(lb<rb) {
		long long mb=(lb+rb)/2;
		f(mb)?rb=mb:lb=mb+1; 
	} 
	return lb;
}
long long lbs(function<bool(long long)> f, long long& lb, long long rb) {  // last true binary search
	while(lb<rb) {
		long long mb=(lb+rb+1)/2;
		f(mb)?lb=mb:rb=mb-1; 
	} 
	return lb;
}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    bool f=1;
	each(a, x) if(f==1) {wt(a); f=0;} else {cout<<' ';wt(a);}
}
const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

#define M 1000005  
struct tree{  
    int left,right,sum,lazy;  
};  
tree g[M];  
int mp1[M];  
  
void pushDown(int i)  
{  
    if(g[i].lazy)  
    {  
        g[2*i].lazy=1;  
        g[2*i+1].lazy=1;  
        g[i].lazy=0;  
          
        g[2*i].sum=g[i].sum/(g[i].right-g[i].left+1)*(g[2*i].right-g[2*i].left+1);  
        g[2*i+1].sum=g[i].sum/(g[i].right-g[i].left+1)*(g[2*i+1].right-g[2*i+1].left+1);  
    }  
}  
  
void buildTree(int left,int right,int i)  
{  
    int mid;  
    g[i].lazy=0;  
    g[i].left=left;  
    g[i].right=right;  
    if(left==right)  
    {  
        g[i].sum=mp1[left];  
        return ;  
    }  
    mid=(left+right)/2;  
    buildTree(left,mid,2*i);  
    buildTree(mid+1,right,2*i+1);  
    g[i].sum=g[2*i].sum+g[2*i+1].sum;  
}  
  
void insert(int l,int r,int num,int i)  
{  
    if(g[i].lazy) pushDown(i);  
    if(l==g[i].left && g[i].right==r)  
    {  
        g[i].sum=(g[i].right-g[i].left+1)*num;  
        g[i].lazy=1;  
        return ;  
    }  
      
    int mid=(g[i].left+g[i].right)/2;  
    if(r<=mid)  
        insert(l,r,num,2*i);  
    else if(mid<l)  
        insert(l,r,num,2*i+1);  
    else  
    {  
        insert(l,mid,num,2*i);  
        insert(mid+1,r,num,2*i+1);  
    }  
    g[i].sum=g[2*i].sum+g[2*i+1].sum;  
      
}  
  
int search(int l,int r,int k)      
{      
    int mid;     
    if(g[k].lazy) pushDown(k);   
      
    if(l==g[k].left && r==g[k].right)          
        return g[k].sum;    
           
    mid=(g[k].left+g[k].right)/2;  
    
    if(r<=mid)           
        search(l,r,2*k);      
    else if(l>mid)       
        search(l,r,2*k+1);    
    else        
        return search(l,mid,2*k)+search(mid+1,r,2*k+1); 
    return 0;   
}      

class Solution {
public:
	vector<int> v;
	void dfs(TreeNode* root){
		if(!root) return;
		dfs(root->left);
		v.push_back(root->val);
		dfs(root->right);
	}
    int getNumber(TreeNode* root, vector<vector<int>>& ops) {
    	v.clear();
    	dfs(root);
    
    	map<int,int> mp;
    	int n=sz(v);
        int t=1;
        each(x,v){
            mp[x]=t++;
        }
    	for(int i=0;i<=n;++i){
            mp1[0]=0;
            g[i]={0,0,0,0};
        }
    	// mst(a,0);mst(d,0);mst(b,0);
        buildTree(1,n,1);  

    	for(auto&e:ops){
    		int t=e[0],l=mp[e[1]],r=mp[e[2]];
    		if(t==0){
    			insert(l,r,0,1);  
    		}else{
    			insert(l,r,1,1);  
    		}
    	}
    	return search(1,n,1);
    }
};