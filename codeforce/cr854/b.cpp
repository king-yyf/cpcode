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
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;
/*
given a string s. You can reorder by permuting the characters of S. find lexicographically smallest string t, t is max s and reverse s.
*/

void ac_yyf(int tt) {
    rd(n);
    vector<int> a(n);rd(a);
    if(is_sorted(all(a))&&a[0]==a[n-1]){
    	cout<<"0\n";return;
    }
    int mn=(*min_element(a.begin(), a.end()));
    int mx=(*max_element(a.begin(), a.end()));
    if(mn==1&&mx>1){
    	cout<<"-1\n";
    	return;
    }
    set<pair<int,int>> s;
    f0(n)s.insert({a[i],i+1});
    vector<array<int,2>> ops;

    while(1){
    	auto it=s.begin();
    	auto rt=s.rbegin();
    	mn=it->first;
    	mx=rt->first;
    	int r=rt->second;
    	int l=it->second;
    	if(mx>mn){
    		ops.push_back({r,l});
    		s.erase(prev(s.end()));
    		mx=(mx+mn-1)/mn;
    		s.insert({mx,r});
    	}else break;
    }
    cout<<ops.size()<<"\n";
    for(auto&e:ops){
    	cout<<e[0]<<" "<<e[1]<<"\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
