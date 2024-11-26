#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
const int N=2e5+10;
int t,n,m,p;
typedef struct Node{
	int l,r;
	ll ki[2];
	ll sum[2];//sum[0]维护区间加和，sum[1]维护区间两两乘积 
	friend Node operator +(const Node &x,const Node &y){
		Node z;
		z.sum[0]=(x.sum[0]+y.sum[0]);
		z.sum[1]=((x.sum[1]+y.sum[1])+
				x.sum[0]*y.sum[0]);
		return z;
	} 
}Node;
Node tr[N*4];
int a[N];
void init_lazy(int u){
	tr[u].ki[0]=0;
	tr[u].ki[1]=1;
}
void pushup(int u){
	tr[u].sum[0]=(tr[u<<1].sum[0]+tr[u<<1|1].sum[0]);
	tr[u].sum[1]=((tr[u<<1].sum[1]+tr[u<<1|1].sum[1])+
				tr[u<<1].sum[0]*tr[u<<1|1].sum[0]);
}
void build(int u,int l,int r){
	tr[u].l=l,tr[u].r=r;
	init_lazy(u);
	if(l==r){
		tr[u].sum[0]=a[l];
		tr[u].sum[1]=0;
		return ;
	}
	int mid=(l+r)>>1;
	build(u<<1,l,mid);
	build(u<<1|1,mid+1,r);
	pushup(u);
}
 
void cal_lazy(int fa,int ch){
	ll a=tr[fa].ki[1],b=tr[fa].ki[0];
	ll len=tr[ch].r-tr[ch].l+1;
	tr[ch].sum[1]=(a*a*tr[ch].sum[1]+a*b*(len-1)*tr[ch].sum[0]+(len-1)*len/2*b*b);
	tr[ch].sum[0]=(a*tr[ch].sum[0]+len*b);
}
void tag_union(int fa,int ch){
	ll a=tr[fa].ki[1],b=tr[fa].ki[0];
	tr[ch].ki[1]=(tr[ch].ki[1]*a);
	tr[ch].ki[0]=(tr[ch].ki[0]*a+b);
}
void pushdown(int u){
	if(tr[u].ki[0]!=0||tr[u].ki[1]!=1){
		cal_lazy(u,u<<1);
		cal_lazy(u,u<<1|1);
		tag_union(u,u<<1);
		tag_union(u,u<<1|1);
		init_lazy(u);
	}
}
void modify(int u,int l,int r,ll k,int type){
	if(tr[u].l>=l&&tr[u].r<=r){
		if(type==1){
			ll len=tr[u].r-tr[u].l+1;
			tr[u].sum[1]=(tr[u].sum[1]+k*(len-1)*tr[u].sum[0]+len*(len-1)/2*k*k);
			tr[u].sum[0]=(tr[u].sum[0]+k*len);
			tr[u].ki[0]=(tr[u].ki[0]+k);
		}
		else{
			tr[u].sum[1]=(tr[u].sum[1]*k*k);
			tr[u].sum[0]=(tr[u].sum[0]*k);
			tr[u].ki[1]=(tr[u].ki[1]*k);
			tr[u].ki[0]=(tr[u].ki[0]*k);
		}
		return ;
	}
	pushdown(u);
	int mid=(tr[u].l+tr[u].r)>>1;
	if(l<=mid)
		modify(u<<1,l,r,k,type);
	if(r>mid)
		modify(u<<1|1,l,r,k,type);
	pushup(u);
}
Node query(int u,int l,int r){
	if(tr[u].l>=l&&tr[u].r<=r)
		return tr[u];
	pushdown(u);
	int mid=(tr[u].l+tr[u].r)>>1;
	Node res;
	if(l>mid){
		return query(u<<1|1,l,r);
	}
	else if(r<=mid){
		return query(u<<1,l,r);
	}	
	else{
		res=query(u<<1,l,r)+query(u<<1|1,l,r);
		return res;
	}
}

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

using ll = long long;
using ar2 = array<int, 2>;
using ar3 = array<int, 3>;
using ar4 = array<int, 4>;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define f3(i,a,b) for (int i=(a);i<(b);i++)
#define r3(i,b,a) for (int i=(b)-1;i>=(a);i--)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void dbg(A x) { cout<<x<<' ';}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	build(1,1,n);
	int opt,l,r,v;
	// Node res=query(1,l,r);
	// printf("%lld\n",res.sum[1]);

    auto c=b_search<ll>(0,1e18,1,[&](ll x){
        int k=1,j=1;
        ll p=0;
        for(int i=2;i<=n;++i) {
        	ll cu=query(1,j,i).sum[1];
        	if(p+cu<=x){
        		p+=cu;
        	}else{
        		k++;
        		p=0;
        		j=i;
        	}
        }
        return k<=m;
    });
    wt(c);
}
 