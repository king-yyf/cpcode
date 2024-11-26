#include <bits/stdc++.h>
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
// const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;


// #include<bits/stdc++.h>
// using namespace std;
#define LL long long
#define N 100005
 
int M[N<<2];
int cnt[N<<2];
int a[N];
int cal(int rt,int l,int r,int h)
{
    if(l==r)return M[rt]>h?1:0;
    if(M[rt<<1]<=h)return cal(rt<<1|1,(l+r)/2+1,r,h);
    else return cal(rt<<1,l,(l+r)>>1,h)+cnt[rt]-cnt[rt<<1];
}
 
void update(int rt,int l,int r,int pos,int h)
{
    if(l==r)
    {
        M[rt]=h;
        cnt[rt]=1;
        return ;
    }
    int m=(l+r)>>1;
    if(pos<=m) update(rt<<1,l,m,pos,h);
    else update(rt<<1|1,m+1,r,pos,h);
    M[rt]=max(M[rt<<1],M[rt<<1|1]);
    cnt[rt]=cnt[rt<<1]+cal(rt<<1|1,(l+r)/2+1,r,M[rt<<1]);
}
 
int main()
{
    int t;
    cin>>t;
    while(t--){
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        
    }
    while(m--)
    {
        int l,h;
        scanf("%d%d",&l,&h);
        update(1,1,n,l,h);
        printf("%d\n",cnt[1]);
        update(1,1,n,l,a[l]);
    }
    }
}

int lengthOfLIS(vector<int>&nums) {
    vector<int> res;
    for (int i = 0; i < nums.size(); ++i) {
        auto it = upper_bound(res.begin(), res.end(), nums[i]);
        if (it == res.end()) res.push_back(nums[i]);
        else *it = nums[i];
    }
    return res.size();
}

void ac_yyf(int tt) {
    rd(n,k);
    auto get=[&](int x){
    	if(x==7)return 0;
    	else if(x==4)return 1;
    	else if(x==8)return 2;
    	return 3;
    };
    rd(s);
    f1(n){
    	update(1,1,n,i,a[i]);
    	a[i]=get(s[i-1]-'0');
    }


    auto chk=[&](int x, int y) {
    	int m=y-x+1;
    	vector<int> c;
    	for(int i=x;i<=y;++i)c.push_back(a[i]);
    		int t=lengthOfLIS(c);
    	if(m-t<=k)return 1;
    	return 0;

    	// for(int i=x;i<=)
    };
    int l=k,r=n,c=l;
    while(l<=r){
    	int md=(l+r)/2;
    	bool o=0;
    	for(int i=0;i+md<=n;++i){
    		int x=i,y=i+md-1;
    		if(chk(x,y)){
    			o=1;
    			break;
    		}
    	}
    	if(o){
    		c=md;
    		l=md+1;
    	}else r=md-1;
    }
    wt(c,'\n');
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
