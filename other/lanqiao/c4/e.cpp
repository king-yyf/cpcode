#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")

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
    int n=a.size();s.resize(n+1);s[0]=0;for(int i=0;i<n;++i)s[i+1]=s[i]+a[i];  
};
template<typename T, typename F> T b_search(T l, T r, bool fst, F &&f) {
    T c = fst ? r : l;
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md;fst?(r=md-1):(l=md+1);} else fst?(l=md+1):(r=md-1);}
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
template<class A> void dbg(A x) { cout<<x<<' ';}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
struct fast_ios { 
    fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(10);};
} fast_ios_;

const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

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

template <typename T>
struct RangeAddTree {
    int n;
    vector<T> a;
    RangeAddTree(int N) : n(N), a(N) {}
    RangeAddTree(vector<T> &A) : RangeAddTree((int)A.size()) {
        for (int i = 1; i <= n; i++) {
            a[i - 1] = A[i - 1] - (i > 1 ? A[i - 2] : 0);
            for (int k = (i & -i) >> 1; k > 0; k >>= 1) 
                a[i - 1] += a[i - k - 1];
        }   
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    void add(int l, int r, const T &v) {  // [l, r]
        add(l, v), add(r + 1, -v);
    }
    T get(int x) const {
        T ans = 0;
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
};


void ac_yyf(int tt) {
    rd(n,m,q);
    vector<int> a(m);
    rd(a);
    vector<Range<int>> qs(n); 
    f0(q){
        rd(x,k);
        int l=k,r=min(k+a[x-1]-1,n);
        l--,r--;
        qs[x-1].add({l,r});
    }
    RangeAddTree<int> t(n);
    f0(n){
        for(auto&[l,r]:qs[i]){
            t.add(l,r,1);
        }
    }
    f0(n)cout<<t.get(i)<<" ";
}

int main() {
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}