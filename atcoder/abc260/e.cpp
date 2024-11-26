#include <bits/stdc++.h>
using namespace std;

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

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<A>& x) {wt(x);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

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

vector<int> smallestRange(vector<vector<int>>& nums) {
    int rangeLeft = 0, rangeRight = INT_MAX;
    int size = nums.size();
    vector<int> next(size);
    
    auto cmp = [&](const int& u, const int& v) {
        return nums[u][next[u]] > nums[v][next[v]];
    };
    priority_queue<int, vector<int>, decltype(cmp)> pq(cmp);
    int minValue = 0, maxValue = INT_MIN;
    for (int i = 0; i < size; ++i) {
        pq.emplace(i);
        maxValue = max(maxValue, nums[i][0]);
    }

    while (true) {
        int row = pq.top();
        pq.pop();
        minValue = nums[row][next[row]];
        if (maxValue - minValue < rangeRight - rangeLeft) {
            rangeLeft = minValue;
            rangeRight = maxValue;
        }
        if (next[row] == nums[row].size() - 1) {
            break;
        }
        ++next[row];
        maxValue = max(maxValue, nums[row][next[row]]);
        pq.emplace(row);
    }

    return {rangeLeft, rangeRight};
}



int n,m,x,y,k,q;
void solve(int tt){
	rd(n,m);
	vector<vector<int>> g(n);
	f0(n){
		rd(x,y);
		if(x>y) swap(x,y);
		g[i].push_back(x);
		g[i].push_back(y);
	}
	vector<int> a=smallestRange(g);
	int l=a[0],r=a[1],d=r-l+1;

	dbg(l,r,'\n');

	vector<int> c(m);
	for(int i=d;i<=m;++i){
		int mi=max(1,r-i+1),mx=min(m,l+i-1);
		c[i-1]=min(m-i+1,)
	}
	wt(c);
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	// cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve(case_i);
	}
	return 0;
}
