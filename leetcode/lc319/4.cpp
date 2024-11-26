#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
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



class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n=sz(s);
        vector<int> d1(n), d2(n);
	    for (int i = 0, l = 0, r = -1; i < n; i++) {
	        int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
	        while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) k++;
	        d1[i] = k--;
	        if (i + k > r) l = i - k, r = i + k;
	    }
	    for (int i = 0, l = 0, r = -1; i < n; i++) {
	        int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
	        while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) k++;
	        d2[i] = k--;
	        if (i + k > r) l = i - k - 1, r = i + k;
	    }
        auto is_palindrome = [&](int l, int r) { // check s[l..(r-1)]
		    if ((r - l) % 2 == 0) return d2[(l + r) / 2] >= (r - l) / 2;
		    return d1[(l + r) / 2] >= (r - l + 1) / 2;
		}; 
		int c=0;

		vector<int> f(n+1);

		// f[0]


		for(int i=1;i<=n;++i){
			f[i]=f[i-1];
			for(int j=i;j>=k;--j){
				if(is_palindrome(i-j,i)){
					f[i]=max(f[i],f[i-j]+1);
				}
			}
			c=max(c,f[i]);
		}

		// wt(f);

		
		return c;
    }
};

#ifdef sigma-yyf
int main(){
    Solution so;
    string s;
    int n;
   

    rd(s,n);
     int c=so.maxPalindromes(s,n);
     wt(c,'\n');
    return 0;
}
#endif
