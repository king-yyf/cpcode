#ifdef sigma-yyf
#include "/Users/yangyf/Desktop/cpcode/leetcode/lc_help.hpp"
#endif
using namespace std;

using ll = long long;
#define ar(x) array<int,x> 
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
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
int pct(long long x) {return __builtin_popcountll(x);} 
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
int clg(int x) {return x <= 1 ? 0 : 32 - __builtin_clz(x - 1);}
template<class t,class u> bool cmx(t &a, const u &b){return a < b ? a = b, 1 : 0;}
template<class t,class u> bool cmn(t &a, const u &b){return b < a ? a = b, 1 : 0;}
template <class T> T f_div(const T x, const T y) { T q = x / y, r = x % y; return q - ((x ^ y) < 0 and (r != 0));}
template <class T> T c_div(const T x, const T y) { T q = x / y, r = x % y; return q + ((x ^ y) > 0 and (r != 0));}
template <class T> int lb(const vector<T> &v, const T &x) { return distance(begin(v), lower_bound(begin(v), end(v), x));}
template <class T> int rb(const vector<T> &v, const T &x) { return distance(begin(v), upper_bound(begin(v), end(v), x));}
template<class T,class A> void psum(vector<T>& s, const vector<A>&a){
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
    return c;
}
template <typename T, typename U> // pair
ostream& operator<<(ostream& out, const pair<T, U>& a) {return out << a.first << ' ' << a.second;}
template <typename T>  // vector
ostream& operator<<(ostream& out, const vector<T>& a) {for(int i=0,n=a.size(); i<n; ++i) out<<a[i]<<" \n"[i==n-1]; return out;}
template <typename T, size_t N> // array
ostream& operator<<(ostream& out, const array<T, N>& a) {for(int i=0;i<N;++i)cout<<a[i]<<" \n"[i==N-1];return out;}
template <typename T, typename U> // pair
istream& operator>>(istream& in, pair<T, U>& a) {return in >> a.first >> a.second;}
template <typename T> // vector
istream& operator>>(istream& in, vector<T>& a) {for (auto &x: a) in >> x; return in;}
template <typename T, size_t N> // array
istream& operator>>(istream& in, array<T, N>& a) {for (int i=0;i<N;++i) in >> a[i]; return in;}
template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
bool is_vo(char c){return c=='a' || c=='e' || c=='i' || c=='o' || c=='u';}
int s2t(string &s){return s[0]*600 + s[1]*60 + s[3]*10 + s[4] - 32208;} //s: "HH:MM" 
#ifdef sigma-yyf
#define dbg(...) debug_impl(#__VA_ARGS__, __VA_ARGS__)
template <class H, class... Ts> void debug_impl(const char* s, const H& h, const Ts&... t) {
    cerr << s << ": " << h, ((cerr << ", " << t), ..., (cerr << "\n"));
}
#else
#define dbg(...) void(0)
#endif
template<class Fun> class Y_comb {
    Fun _f;
public:
    template<class T> explicit Y_comb(T &&fun): _f(forward<T>(fun)) {}
    template<class ...Args> decltype(auto) operator()(Args &&...As) {return _f(ref(*this), forward<Args>(As)...);}
};
template<class Fun> decltype(auto) y_comb(Fun &&fun) { return Y_comb<decay_t<Fun>>(forward<Fun>(fun));}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;
constexpr char nl = '\n';
constexpr int inf = 1'061'109'567;
constexpr ll infll = 2'000'000'000'000'000'000;
constexpr int N = 2e5 + 5;
int n, m, k;

template <typename T>
struct Range: map<T, T> {
    T siz = 0;
    using map<T, T>::map, map<T, T>::upper_bound, map<T, T>::begin, map<T, T>::end, map<T, T>::emplace, map<T, T>::erase;
    static T len(const pair<T, T> &p) {return p.second - p.first + 1;}
    pair<vector<pair<T, T>>, typename map<T, T>::iterator> add(pair<T, T> p) {
        vector<pair<T, T>> ds;
        auto it = upper_bound(p.first);
        if (it != begin() && prev(it)->second + 1 >= p.first) {
            if (prev(it)->second >= p.second) return {{*prev(it)}, prev(it)};
            p.first = prev(it)->first;
            ds.emplace_back(*prev(it));
            it = erase(prev(it));
        }
        for (; it != end() && it->first <= p.second + 1; it = erase(it)) {
            if (it->second > p.second) p.second = it->second;
            ds.emplace_back(*it);
        }
        for (auto &range : ds) siz -= len(range);
        auto inserted = emplace(p.first, p.second).first;
        siz += len(*inserted);
        return {ds, inserted};
    }
    pair<vector<pair<T, T>>, vector<pair<T, T>>> del(pair<T, T> p) {
        vector<pair<T, T>> ds, as;
        auto it = upper_bound(p.first);
        if (it != begin() && prev(it)->second + 1 >= p.first) {
            it = prev(it);
            ds.emplace_back(*it);
            if (it->second >= p.second) {
                if (it->second > p.second) as.emplace_back(*emplace(p.second + 1, it->second).first);
                if (it->first < p.first) {
                    it->second = p.first - 1;
                    as.emplace_back(*it);
                } else
                    erase(it);
                for (auto &range : ds) siz -= len(range);
                for (auto &range : as) siz += len(range);
                return {ds, as};
            }
            if (it->first < p.first) {
                it->second = p.first - 1;
                as.emplace_back(*it);
                it = next(it);
            } else
                it = erase(it);
        }
        for (; it != end() && it->first <= p.second; it = erase(it)) {
            ds.emplace_back(*it);
            if (it->second > p.second) as.emplace_back(*emplace(p.second + 1, it->second).first);
        }
        for (auto &range : ds) siz -= len(range);
        for (auto &range : as) siz += len(range);
        return {ds, as};
    }
    typename map<T, T>::const_iterator any(const pair<T, T> &p) const {
        if (auto it = upper_bound(p.second); it != begin() && prev(it)->second >= p.first) return prev(it);
        return end();
    }
    typename map<T, T>::const_iterator all(const pair<T, T> &p) const {
        if (auto it = upper_bound(p.second); it != begin() && prev(it)->first <= p.first && prev(it)->second >= p.second) return prev(it);
        return end();
    }
    template <typename OS>
    friend OS &operator<<(OS &os, const Range &t) {
        os << '[';
        uint32_t index = 0;
        for (auto &[l, r] : t) {
            if (index++) os << ", ";
            os << '[' << l << ", " << r << ']';
        }
        return os << ']';
    }
};


class Solution {
public:
    int countDays(int d, vector<vector<int>>& p) {
        Range<int> f;
        for(auto&e:p){
            f.add({e[0],e[1]});
        }
        return d-f.siz;
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
