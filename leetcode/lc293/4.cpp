#include<bits/stdc++.h>
using namespace std;
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

struct seg{//线段 
	double l,r,h;
	int d;
	seg(){}
	seg(double x1,double x2,double H,int c):l(x1),r(x2),h(H),d(c){}
	bool operator<(const seg &a)const{
		return h<a.h;
	}
}s[MAX];
 
void Upfather(int n,int left,int right){
	if(mark[n])sum[n]=hash[right+1]-hash[left];//表示该区间整个线段长度可以作为底边 
	else if(left == right)sum[n]=0;//叶子结点则底边长度为0(区间内线段长度为0) 
	else sum[n]=sum[n<<1]+sum[n<<1|1];
}
 
void Update(int L,int R,int d,int n,int left,int right){
	if(L<=left && right<=R){//该区间是当前扫描线段的一部分,则该区间下底边总长以及上下底边个数差更新 
		mark[n]+=d;//更新底边相差差个数 
		Upfather(n,left,right);//更新底边长 
		return;
	}
	int mid=left+right>>1;
	if(L<=mid)Update(L,R,d,n<<1,left,mid);
	if(R>mid)Update(L,R,d,n<<1|1,mid+1,right);
	Upfather(n,left,right);
}
 
int search(double key,double* x,int n){
	int left=0,right=n-1;
	while(left<=right){
		int mid=left+right>>1;
		if(x[mid] == key)return mid;
		if(x[mid]>key)right=mid-1;
		else left=mid+1;
	}
	return -1;
}

#ifdef LOCAL
int main(){
	
    return 0;
}
#endif

class CountIntervals {
:
	map<int,int> mp;
    CountIntervals() {
    	mp.clear();
    }
    
    void add(int l, int r) {
    	mp[l]++;mp[r]--
    }
    
    int count() {
    	
    }
};
