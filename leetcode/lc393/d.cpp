#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

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
    int n=a.size(); s.assign(n + 1, 0); 
    for(int i = 0; i < n; ++i) s[i + 1] = s[i] + a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;
int n, m, k;

template<typename F> 
void bitwise_and(vector<int> &a, F &&f) {
    vector<pair<int,int>> p, q;
    for (int n = a.size(), i = 0; i < n; ++i) {
        q.emplace_back(a[i], i);
        int k = 0;
        for (int j = 0; j < p.size(); ++j) {
            p[j].first &= a[i];
            if (p[j].first == q[k].first) {
                q[k].second = p[j].second;
            } else {
                q.emplace_back(p[j].first, p[j].second);
                k++;
            }
        }
        p = q;
        q.clear();
        for (int j = k; j >= 0; --j) {
            // 以[l, r-1]为左端点，i为右端点的所有子数组，按位与的值都为p[j].first
            int l = p[j].second, r = (j > 0 ? p[j - 1].second : i + 1);
            f(i, l, r, p[j].first);
        }
    } 
}

template <class S, S (*op)(S, S), S (*e)()>
struct SegTree {
    int n, size, log;
    vector<S> d;
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<S>(n, e())) {}
    explicit SegTree(const vector<S> &v) : n(int(v.size())) {
        log = ceil_lg(n), size = 1 << log;
        d = vector<S>(2 * size, e());
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) pull(i);
    }
    int ceil_lg(int x) {   // minimum non-neg x s.t. `n <= 2^x`
        return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);
    }
    void set(int p, S x) {  // assert(0 <= p < n)
        p += size, d[p] = x;
        for (int i = 1; i <= log; ++i) pull(p >> i);
    }
    S get(int p) const { return d[p + size];}
    S get(int l, int r) {   // [l, r)
        S sl = e(), sr = e();
        l += size, r += size;
        while (l < r) {
            if (l & 1) sl = op(sl, d[l++]);
            if (r & 1) sr = op(d[--r], sr);
            l >>= 1, r >>= 1;
        }
        return op(sl, sr);
    }
    S get_all() const {return d[1];}

    void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]);}
    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F>     // 0 <= l <= n, f(e()) is true
    int max_right(int l, F f) const { 
        if (l == n) return n;
        l += size;
        S x = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(x, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(x, d[l]))) {
                        x = op(x, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            x = op(x, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }
    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F>  // 0 <= r <= n, f(e()) is true
    int min_left(int r, F f) const {
        if (r == 0) return 0;
        r += size;
        S x = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], x))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], x))) {
                        x = op(d[r], x);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            x = op(d[r], x);
        } while ((r & -r) != r);
        return 0;
    }
};
using S = int;
S op(S x, S y) {
    return min(x,y);
}
S e() {
    return S{(S)1e9};
}

class Solution {
public:
    int minimumValueSum(vector<int>& a, vector<int>& b) {
        n=sz(a),m=sz(b);
        // vector<vector<int>> dp(n+1,vector<int>(m+1,1e8));
        // dp[0][0]=0;
        vector<vector<ar3 >> p(n);
        bitwise_and(a, [&](int i, int l, int r, int val){
	        p[i].push_back({l,r,val});
	    }); 
	    SegTree<S, op, e> seg((m+1)*(n+1));
	    auto get=[&](int x,int y){
	    	return y*(n+1)+x;
	    };
	    seg.set(0,0);
        for(int i=0;i<n;++i){
        	for(int j=0;j<m;++j){
        		for(auto&[l,r,v]:p[i]){
        			
        			if(v==b[j]){
        				// cout<<"i="<<i<<", j="<<j<<", l="<<l<<", r="<<r<<", v="<<v<<", b[j]=" << b[j]<<"\n";
        				int l1=get(l,j),r1=get(r-1,j);
        				auto c=seg.get(l1,r1+1);
        				// for(int x=l;x<r;++x){
        					
        				// 	// if(dp[x][j]<1e7){
        				// 	// 	cmn(c,dp[x][j]+a[i]);
        				// 	// }
        				// 	cmn(c,seg.get(get(x,j))+a[i]);
        				// 	if(i==3){
        				// 		cout<<"--- "<<"x="<<x<<", dp[x][j]="<<seg.get(get(x,j))<<", c="<<c<<'\n';
        				// 	}
        				// }
        				// dp[i+1][j+1]=c;
        				seg.set(get(i+1,j+1),c+a[i]);
        				break;
        			}
        		}
        	}
        }
        // for(int i=0;i<=n;++i){
        // 	for(int j=0;j<=m;++j){
        // 		cout<<dp[i][j]<<' ';
        // 	}
        // 	cout<<"\n";
        // }
        auto c=seg.get((m+1)*(n+1)-1,(m+1)*(n+1));
        return c>1e7?-1:c;
    }
};

#ifdef sigma-yyf
int main(){
    vector<int> a{1,4,3,3,2};
    vector<int> b{0,3,3,2};
    Solution so;
    auto p=so.minimumValueSum(a,b);
    wt(p,nl);
    cout<<'\n';
    return 0;
}
#endif
