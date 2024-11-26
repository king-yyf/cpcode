#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define fr(i,a,b) for (int i=(a);i<(b);i++)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

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
const double PI = acos(-1.0);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;
using ull = unsigned long long;
void solve() {
    rd(s);
    n=sz(s);
    vector<int> a(n);
    rd(a);

    set<char> sc;
    each(x,s){
    	sc.insert(x);
    }


    if(sz(sc)==1){

    	vector<int> c(n);

    	stack<int> sk;

    	for(int k=n;k>=1;--k){
    		while(!sk.empty() && sk.top()<=a[k-1]){
    			sk.pop();
    		}
    		sk.push(a[k-1]);
    		c[k-1]=sz(sk);
    	}
    	wt(c);

    	return;
    }

    const int p1=13331;

    vector<ull> h(n+1),p(n+1);
    h[0]=0,p[0]=1;
    f0(n){
    	h[i+1]=h[i]*p1+s[i];
    	p[i+1]=p[i]*p;
    }


    auto get=[&](int l, int r)->ull{
    	return h[r+1]-h[l]*p[r-l+1];
    };

    map<ull,int> mp;

    vector<int> ans(n);

    for(int k=1;k<=n;++k){
    	for(int i=0;i+k<=n;++i){
    		auto hh=get(i,i+k-1);
    		if(!mp.count(hh)) {
    			mp[hh]=a[i+k-1];
    			ans[k-1]++;
    		}
    		else if(a[i+k-1]>mp[hh]) {
    			mp[hh]=a[i+k-1];
    			ans[k-1]++;
    		}
    	}
    }
    wt(ans);

}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    solve();

    return 0;
}
