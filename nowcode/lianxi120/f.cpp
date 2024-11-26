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
    while(l<=r){T md=(l+r)/2;if(f(md)){c=md; fst ? (r=md-1):(l=md+1);} else fst ? (l=md+1):(r=md-1);}
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

template<typename T, int ALPHABET_SIZE = 26, char CH = 'a'>
struct palindrome_tree {
    // node that represents a palindromic substring
    struct node_t {
        T len, pos, cnt; // 回文子串长度、首次出现位置、出现次数
        T depth, suff;   // suff: node-index of largest palindromic suffix
        T next[ALPHABET_SIZE]; // "A".next['x'] --> "xAx"
    };

    vector<char> _str;    // string of letter ordinals (e.g. 'a' is 0)
    vector<node_t> _nodes;
    T _suff;             // node-index of the current longest palindromic suffix
    long long _total;    // 回文子串总数，可到n*n级别

    palindrome_tree() {_init();}

    palindrome_tree(string &s) {
        _init();
        add_all(s);
    }

    void _init() {
        _str.clear();  _nodes.resize(3);
        _nodes[1].len = -1, _nodes[1].suff = 1;
        _nodes[2].len = 0, _nodes[2].suff = 1;
        _suff = 2, _total = 0;
    }

    template<typename C>
    void reserve_more(C& c, size_t sz) {
        if (c.size() + sz <= c.capacity()) return;
        c.reserve(std::max(c.size() + sz, c.capacity() + c.capacity() / 2));
    }

    T add_all(string &s) {
        size_t len = s.size();
        reserve_more(_str, len), reserve_more(_nodes, len);
        T c = 0;
        for (auto &ch: s) c += add(ch);
        return c;
    }

    T add(char let) {
        let = let - CH;
        _str.push_back(let);
        T i = _find_suffix(_suff, let);
        _suff = _nodes[i].next[let];
        if (_suff != 0) {
            _nodes[_suff].cnt++, _total += _nodes[_suff].depth;
            return 0;
        }
        T suff2 = _find_suffix2(i, let);
        _suff = (T)_nodes.size();
        _nodes.push_back({});
        _nodes[_suff].len = _nodes[i].len + 2;
        _nodes[_suff].pos = (T)_str.size() - _nodes[_suff].len;
        _nodes[_suff].cnt = 1;
        _nodes[_suff].suff = suff2;
        _nodes[_suff].depth = _nodes[suff2].depth + 1;
        _nodes[i].next[let] = _suff;
        _total += _nodes[_suff].depth;
        return 1;
    }

    T _find_suffix2(T i, char let) {
        if (i == 1) return 2;
        i = _find_suffix(_nodes[i].suff, let);
        return _nodes[i].next[let];
    }

    T _find_suffix(T i, char let) {
        T sz = (T)_str.size();
        while (sz < _nodes[i].len + 2 || _str[sz - _nodes[i].len - 2] != let) {
            i = _nodes[i].suff;
        }
        return i;
    }

    // This should be called only once after all elements are added!
    void propagate() {
        for (T i = (T)_nodes.size() - 1; i >= 3; i--) {
            T suff = _nodes[i].suff;
            _nodes[suff].cnt += _nodes[i].cnt;
        }
    }

    // Returns the number of total palindromic substrings, counting their multiplicities.
    long long total() const { return _total;}

    // Returns the number of distinct palindromic substrings, each counted only once.
    T distinct() const { return (T)_nodes.size() - 3;}

    // Returns the index of the node representing the longest palindromic suffix.
    T longest_suffix() const { return _suff;}

    // Returns the <length, index> of longest Palindrome substrings
    array<T, 2> longest_palindrome() const {
        T longest = 0, index = 0;
        for (int i = 3; i < (T)_nodes.size(); ++i) 
            if (_nodes[i].len > longest) 
                longest = _nodes[i].len, index = _nodes[i].pos;
        return {longest, index};
        
    } 

    // Returns the number of nodes.
    T size() const { return (T)_nodes.size();}

    // Accesses node by its index.
    node_t& operator[] (T index) { return _nodes[index];}
};

void ac_yyf(int tt) {
    rd(n,m);
    vector<int> a(n);
    rd(a);
    set<int> s;
    each(x,a)s.insert(x);
    int t=0;
    f1(m){
    	if(!s.count(i))t++;
    	// else{

    	// }
    }
    if(t>0){
    	f1(m) {
    		
    	}
    }
}

int main() {
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
        // cout << ( ac_yyf(cas) ? "Yes" : "No") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
