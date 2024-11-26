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

template <class S, S (*op)(S, S)> class BiLiftring {
    int n = 0;
    vector<vector<int>> _nexts;
    vector<vector<S>> _prods;

    void build_next() {
        vector<int> t(n);
        vector<S> p(n);

        for (int i = 0; i < n; ++i) {
            if (int j = _nexts.back()[i]; isin(j)) {
                t[i] = _nexts.back()[j], p[i] = op(_prods.back()[i], _prods.back()[j]);
            } else t[i] = j, p[i] = _prods.back()[i];
        }
        _nexts.emplace_back(move(t));
        _prods.emplace_back(move(p));
    }

    inline bool isin(int i) const noexcept { return 0 <= i and i < n; }

public:
    // (up to) 2^d steps from `s`
    // Complexity: O(d) (Already precalculated) / O(nd) (First time)
    int pow_next(int s, int d) {
        assert(isin(s));
        while (int(_nexts.size()) <= d) build_next();
        return _nexts.at(d).at(s);
    }

    // Product of (up to) 2^d elements from `s`
    const S &pow_prod(int s, int d) {
        assert(isin(s));
        while (int(_nexts.size()) <= d) build_next();
        return _prods.at(d).at(s);
    }

    BiLiftring() = default;
    BiLiftring(const vector<int> &g, const vector<S> &w)
        : n(g.size()), _nexts(1, g), _prods(1, w) {
        assert(g.size() == w.size());
    }

    // (up to) k steps from `s`
    template <class Int> int kth_next(int s, Int k) {
        for (int d = 0; k > 0 and isin(s); ++d, k >>= 1) {
            if (k & 1) s = pow_next(s, d);
        }
        return s;
    }

    // Product of (up to) `len` elements from `s`
    template <class Int> S get(int s, Int len) {
        assert(isin(s)); assert(len > 0);
        int d = 0;
        while (!(len & 1)) ++d, len /= 2;

        S ret = pow_prod(s, d);
        s = pow_next(s, d);
        for (++d, len /= 2; len and isin(s); ++d, len /= 2) {
            if (len & 1) ret = op(ret, pow_prod(s, d)), s = pow_next(s, d);
        }
        return ret;
    }

    // `start` から出発して「`left_goal` 以下または `right_goal` 以上」に到達するまでのステップ数
    // 単調性が必要
    int dis_mono(int start, int left_goal, int right_goal) {
        assert(isin(start));

        if (start <= left_goal or right_goal <= start) return 0;

        int d = 0;
        while (left_goal < pow_next(start, d) and pow_next(start, d) < right_goal) {
            if ((1 << d) >= n) return -1; ++d;
        }
        int ret = 0, cur = start;
        for (--d; d >= 0; --d) {
            if (int nxt = pow_next(cur, d); left_goal < nxt and nxt < right_goal) {
                ret += 1 << d, cur = nxt;
            }
        }
        return ret + 1;
    }

    template <class F> long long max_len(const int s, F f, const int maxd = 60) {
        assert(isin(s));
        int d = 0;
        while (d <= maxd and f(pow_prod(s, d))) {
            if (!isin(pow_next(s, d))) return 1LL << maxd; ++d;
        }
        if (d > maxd) return 1LL << maxd;
        --d;
        int cur = pow_next(s, d);
        long long len = 1LL << d;
        S p = pow_prod(s, d);
        for (int e = d - 1; e >= 0; --e) {
            if (S nextp = op(p, pow_prod(cur, e)); f(nextp)) {
                swap(p, nextp);
                cur = pow_next(cur, e);
                len += 1LL << e;
            }
        }
        return len;
    }
};

using S = long long;
S op(S l, S r) {
	return l + r;
}

class Solution {
public:
    long long getMaxFunctionValue(vector<int>& a, long long k) {
    	int n = a.size();
    	vector<long long> w(n);
    	iota(w.begin(), w.end(), 0);
        BiLiftring<S, op> b(a, w);
        long long res = 0;
	    for (int i = 0; i < n; ++i)
	    	res = max(res, b.get(i, k + 1));
	    return res;
	}
};

#ifdef sigma-yyf
int main(){
    vector<int> v,a,b;
    string s,t;
    vector<string> sv;
    vector<vector<int>> vv;
    // ListNode* head = nullptr, *l1,*l2;
    // TreeNode* root = nullptr,*p,*q;
    // Solution so;
    // rd(a,k);
    // auto ans = so.;
    // wt(ans);
    cout<<'\n';
    return 0;
}
#endif