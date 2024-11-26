#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// #define all(c) (c).begin(), (c).end()
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
#define yn(o) cout << ((o) ? "Yes" : "No") << "\n";
#define YN(o) cout << ((o) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
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

void ac_yyf(int tt) {
    Range<ll> p,q;
    rd(n);
    vector<pair<ll,ll> > a(n);
    f0(n){
        ll x,y;
        rd(x,y);
    	a[i]={x,y};
    }
    
    p.add(a[0]);
    int mx=p.siz;
    for(int i=1;i<n;++i){
        p.add(a[i]);
        q=p;
        q.del(make_pair(a[i].second+1,1e9+2));
        cmx(mx,q.siz);
    }
    wt(mx);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
