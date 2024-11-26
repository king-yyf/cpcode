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
#define yn(cond) if (cond) cout<<"Yes\n"; else cout << "No\n";
#define YN(cond) if (cond) cout<<"YES\n"; else cout << "NO\n";
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


void solve() {
    int n,m1,m2;
    cin>>n>>m1>>m2;
    set<int> s1,s2;
    set<long long> s;
    s.insert(1);
    s1.insert(m1);
    s1.insert(m2);

    auto get=[&](int x, set<int>&s){
    	for(int i=2;i*i<=x;i++){
    		if(x%i==0){
    			s.insert(i);
    			s.insert(x/i);
    		}
    	}
    };

    get(m1,s1);
    get(m1,s1);
    for(auto&p:s1) 
    	s.insert(p);
    for(auto&p:s2) 
    	s.insert(p);
    for(auto&p:s1)for(auto&q:s2){
    	long long x=p*1ll*q;
    	if(x>n*1ll*n) break;
    	s.insert(x);
    }
    long long ans=0;
    for(auto&p:s){
    	
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int T = 1;
    cin >> T;
    while(T--){
    	solve();
    }
    return 0;
}
