#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
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

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) { cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    for (int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];
}
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

int n,x,y;

typedef long long ll;

vector<bool> subset_sum(const vector<int> &a,int tgt){
    int n=a.size();
    int amax=n;
    int brk=0,sbrk=0;
    while(brk<n&&sbrk+a[brk]<=tgt){
        sbrk+=a[brk];
        brk++;
    }
    if(brk==n&&sbrk!=tgt)
        return {};
    vector<int> dp(amax*2,-1);
    vector<vector<int>> prv(n,vector<int>(amax*2,-1));
    int offset=tgt-amax+1;
    dp[sbrk-offset]=brk;
    for(int i=brk;i<n;i++){
        vector<int> dp2=dp;
        vector<int> &prv_cur=prv[i];
        for(int j=amax-1;j>=0;j--)
            if(dp2[j+a[i]]<dp2[j]){
                prv_cur[j+a[i]]=-2;
                dp2[j+a[i]]=dp2[j];
            }
        for(int j=amax*2-1;j>=amax;j--)
            for(int k=dp2[j]-1;k>=max(dp[j],0);k--)
                if(dp2[j-a[k]]<k){
                    prv_cur[j-a[k]]=k;
                    dp2[j-a[k]]=k;
                }
        swap(dp,dp2);
    }
    if(dp[amax-1]==-1)
        return {};
    vector<bool> ans(n);
    int i=n-1,j=amax-1;
    while(i>=brk){
        int p=prv[i][j];
        if(p==-2){
            ans[i]=!ans[i];
            j-=a[i];
            i--;
        }else if(p==-1){
            i--;
        }else{
            ans[p]=!ans[p];
            j+=a[p];
        }
    }
    while(i>=0){
        ans[i]=!ans[i];
        i--;
    }
    return ans;
}

void solve(){
	cin>>n>>x>>y;

	long long s=(1ll+n)*n/2;
	if(s<x+y||s%(x+y)!=0){
		wt("IMPOSSIBLE\n");
		return;
	}
	int t=s/(x+y);

	t=t*min(x,y);
	vector<int> a;
	f1(n)a.push_back(i);
	// shuffle(all(a));

	auto c=subset_sum(a,t);
	wt(c);
	if(c.empty()){
		wt("IMPOSSIBLE\n");
		return;
	}
	vector<int> d,b;
	f0(n){
		if(c[i]==0)b.push_back(i+1);else d.push_back(i+1);
	}
	wt("POSSIBLE\n");
	
	if(x<=y){
		wt(sz(d),'\n');
		wt(d);
		
	}else{
		wt(sz(b),'\n');
		wt(b);
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
        cout << "Case #" << case_i << ": ";
		solve();
	}
	return 0;
}
