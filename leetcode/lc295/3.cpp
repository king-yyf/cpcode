#include<bits/stdc++.h>
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
template<typename T>
struct fenwick {
    vector<T> a;
    int n;
    fenwick(int n): n(n), a(n) {}
    void add(int x, T v) {
        for(int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    T qry(int x) {
        T ret = 0;
        for(int i = min(x + 1, n); i > 0; i -= i & -i) ret += a[i - 1];
        return ret;
    }
};
template<typename T>
vector<int>  revpair(vector<T> a) {
    vector<T> b = a;
    int n=sz(a);
    vector<int> c(n);
    sort(b.begin(), b.end());
    b.erase(unique(begin(b), end(b)), end(b));
    fenwick<int> fen(b.size());
    long long ret = 0;
    for(int i=n-1;i>=0;--i){
    	int p = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    	c[i] = fen.qry(p);
    	fen.add(p, 1);
    }
    // for(int i = 0; i < a.size(); ++i) {
    //     int p = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    //     c[i] = i - fen.qry(p); //如果是a[i] >= a[j]，改为 i - fen.qry(p-1)
    //     fen.add(p, 1);
    // }
    return c;
}
vector<int> dailyTemperatures(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 0);
        stack<int> sk;
        for (int i = 0; i < n; ++i) {
            while(!sk.empty() && nums[sk.top()] <= nums[i]) {
                res[sk.top()] = i - sk.top();
                sk.pop();
            }
            sk.push(i);
        }
        return res;
    }
class Solution {
public:
    int totalSteps(vector<int>& a) {
        auto b=dailyTemperatures(a);
        wt(a);
        wt(b);
        return Max(b)-1;
    }
};

#ifdef LOCAL
int main(){
	Solution so;
	vector<int> a{10,1,2,3,4,5,6,1,2,3};
	so.totalSteps(a);
    return 0;
}
#endif

