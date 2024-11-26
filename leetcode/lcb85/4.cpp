

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define ln "\n";
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) {cout << x << " ";}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void wt(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void wt(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};

typedef long long ll;
const int MAX = 100010;

int n, m;
int a[MAX];
struct node{
	ll sum_l, sum_r, sum;
	ll tot;
}tree[MAX * 4];


void update(ll u, int x, int y) {
	tree[u].sum = max(max(tree[u << 1].sum, tree[u << 1 | 1].sum), tree[u << 1].sum_r + tree[u << 1 | 1].sum_l);
	//从（左边和右边的区间最大字段和 还有 左边的sum_r加右边的sum_l ）得到 
	tree[u].tot = tree[u << 1].tot + tree[u << 1 | 1].tot;
	tree[u].sum_l = max(tree[u << 1].sum_l, tree[u << 1].tot + tree[u << 1 | 1].sum_l);
	//从（左边延伸（tree[u << 1].tot + tree[u << 1 | 1]) 或 左边的sum_l）得到.....下同 
	tree[u].sum_r = max(tree[u << 1 | 1].sum_r, tree[u << 1 | 1].tot + tree[u << 1].sum_r);
}
void build(ll u, int x, int y) {
	if(x == y) {
		tree[u].sum = tree[u].sum_l = tree[u].sum_r = tree[u].tot = a[x];
		return ;
	}
	int mid = (x + y) >> 1;
	build(u << 1, x, mid);
	build(u << 1 | 1, mid + 1, y);
	update(u, x, y);
}
node ask(ll u, int x, int y, int a, int b) {//询问要返回node 
	if(a <= x && b >= y) return tree[u];
	int mid = (x + y) >> 1;
	if(a > mid) return ask(u << 1 | 1, mid + 1, y, a, b);
	if(b <= mid) return ask(u << 1, x, mid, a, b);
	node son_l = ask(u << 1, x, mid, a, b), son_r = ask(u << 1 | 1, mid + 1, y, a, b);
	node ans;
	ans.tot = son_l.tot + son_r.tot;
	ans.sum = max(max(son_l.sum, son_r.sum), son_l.sum_r + son_r.sum_l);
	ans.sum_l = max(son_l.sum_l, son_l.tot + son_r.sum_l);
	ans.sum_r = max(son_r.sum_r, son_r.tot + son_l.sum_r);
	return ans;
}
void change(ll u, int x, int y, int a, ll k) {
	if(x == y && x == a) {
		tree[u].sum = tree[u].sum_l = tree[u].sum_r = tree[u].tot = k;
		return ;
	}
	int mid = (x + y) >> 1;
	if(a <= mid) change(u << 1, x, mid, a, k);
	if(a > mid) change(u << 1 | 1, mid + 1, y, a, k);
	update(u, x, y);
}

class Solution {
public:
    vector<long long> maximumSegmentSum(vector<int>& a1, vector<int>& q) {
        int n=sz(a1);

        f1(n){
        	a[i]=a1[i-1];
        }
        build(1,1,n);
        long long s=Sum(a1);
        vector<long long> c(n);
       	f0(n){
       		change(1, 1, n, q[i]+1, -s);
       		s-=a[i];
       		c[i]=ask(1, 1, n, 1, n).sum;

       	}
        c[n-1]=0;
       	return c;
        
    }
};


