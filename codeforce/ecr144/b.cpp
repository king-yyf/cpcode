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

string LCS(string s1, string s2) {
    if(sz(s1)>sz(s2))swap(s1,s2);
    int n = s1.size(), m = s2.size();
    vector<int> dp(m + 1, 0);
    int res = 0, start = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = m; j >= 1; --j) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[j] = dp[j - 1] + 1;
                if (dp[j] > res) {
                    res = dp[j];
                    start = j - dp[j];
                }
            } else dp[j] = 0;
        }
    }
    return res > 0 ? s2.substr(start, res): "";
}
void ac_yyf(int tt) {
    rd(s,t);
    int n=s.size(),m=t.size();
	if(n==1 && m==1){
	    if(s==t){
	        wt("YES",'\n',s,'\n');
	        return;
	    }
	    cout<<"NO"<<endl;
	    return;
	}
	if(s[0]==t[0] or s[n-1]==t[m-1]){
	    wt("YES",'\n');
	    if(s[0]==t[0]) wt(s[0],'*','\n');
	    else wt('*',s[n-1],'\n');
	    return;
	}

	f0(n){
	    f2(j,m){
	        if(s[i]==t[j]){
	            if(i<n-1 && j<m-1){
	                if(s[i+1]==t[j+1]){
	                    wt("YES",'\n');
	                    wt("*",s[i],s[i+1],'*','\n');
	                    return;
	                }
	            }
	        }
	    }
	}
	wt("NO\n");

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
