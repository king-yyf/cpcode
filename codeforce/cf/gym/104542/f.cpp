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

template <typename T> struct light_forward_list {
    static std::vector<unsigned> ptr;
    static std::vector<T> val;
    unsigned head;
    light_forward_list() : head(0) {}
    void push_front(T x) {
        ptr.push_back(head), val.push_back(x);
        head = ptr.size() - 1;
    }
    struct iterator {
        unsigned p;
        iterator operator++() { return {p = ptr[p]}; }
        T &operator*() { return val[p]; }
        bool operator!=(const iterator &rhs) { return p != rhs.p; }
    };
    iterator begin() { return {head}; }
    iterator end() { return {0}; }
};
template <typename T> std::vector<unsigned> light_forward_list<T>::ptr = {0};
template <typename T> std::vector<T> light_forward_list<T>::val = {T()};

template <class T, int (*char2int)(char)> struct AhoCorasick {
    bool built;
    const int D;
    std::vector<T> node;
    AhoCorasick(int D_) : built(false), D(D_), node(1, D) {}
    AhoCorasick operator=(const AhoCorasick &rhs) { return AhoCorasick(rhs.D); }

    void enter_child(int n, int nn, int c) { node[n].setch(c, nn); }

    std::vector<int> endpos;
    int add(const std::string &keyword) { // Enter_in_tree() in [1]
        built = false;
        int n = 0;
        for (const auto &cc : keyword) {
            int c = char2int(cc), nn = node[n].Goto(c);
            if (!nn) {
                nn = node.size();
                enter_child(n, nn, c), node.emplace_back(D);
            }
            n = nn;
        }
        return endpos.push_back(n), n;
    }

    void complete_failure(int n, int nn, int c) {
        int m = node[n].fail, mm = node[m].Goto(c);
        while (m and !mm) m = node[m].fail, mm = node[m].Goto(c);
        node[nn].fail = mm;
    }

    std::vector<int> visorder; // BFS order of node ids
    void build() {             // Build_failure() in [1]
        visorder.clear();
        for (auto p : node[0]) {
            if (p.second) visorder.push_back(p.second);
        }
        for (size_t p = 0; p < visorder.size(); p++) {
            int n = visorder[p];
            for (auto p : node[n]) {
                int c = p.first, nn = p.second;
                if (nn) visorder.push_back(nn), complete_failure(n, nn, c);
            }
        }
        built = true;
    }

    int step(int now, int d) {
        while (now and !node[now].Goto(d)) now = node[now].fail;
        return node[now].Goto(d);
    }

    // Count occurences of each added keywords in `str`
    std::vector<int> match(const std::string &str) {
        if (!built) build();
        std::vector<int> freq(node.size());
        int now = 0;
        for (const auto &c : str) freq[now = step(now, char2int(c))]++;

        for (auto i = visorder.rbegin(); i != visorder.rend(); i++)
            freq[node[*i].fail] += freq[*i];
        std::vector<int> ret;
        for (auto x : endpos) ret.push_back(freq[x]);
        return ret;
    }
};


struct DSU {
    vector<int> p, siz;
    DSU(int n) : p(n), siz(n, 1) { iota(p.begin(), p.end(), 0); }
    inline int get(int x) { return (x == p[x] ? x : (p[x] = get(p[x])));}
    bool same(int x, int y) { return get(x) == get(y); }
    bool merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        siz[x] += siz[y];
        p[y] = x;
        return true;
    }
    int size(int x) { return siz[get(x)]; }
    vector<vector<int>> groups() {
        vector<vector<int>> res(p.size());
        for (int i = 0; i < p.size(); i++) res[get(i)].push_back(i);
        res.erase(
            remove_if(res.begin(), res.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            res.end());
        return res;
    }
};

struct TrieNodeFL {
    struct smallpii {
        int first : 8;
        int second : 24;
    };
    light_forward_list<smallpii> chlist;
    int fail;
    TrieNodeFL(int = 0) : fail(0) {}
    int Goto(int c) {
        for (const auto x : chlist) {
            if (x.first == c) return x.second;
        }
        return 0;
    }
    void setch(int c, int i) { chlist.push_front({c, i}); }

    struct iterator {
        light_forward_list<smallpii>::iterator iter;
        iterator operator++() { return {++iter}; }
        smallpii operator*() { return *iter; }
        bool operator!=(const iterator &rhs) { return iter != rhs.iter; }
    };
    iterator begin() { return {chlist.begin()}; }
    iterator end() { return {chlist.end()}; }
};

struct TrieNodeV {
    std::vector<int> ch; // 全 bit が行き先
    int fail;
    TrieNodeV(int D = 0) : ch(D), fail(0) {}
    int Goto(int d) { return ch[d]; }
    void setch(int d, int i) { ch[d] = i; }

    struct iterator {
        int i;
        std::vector<int>::iterator iter;
        iterator operator++() { return {++i, ++iter}; }
        std::pair<int, int> operator*() { return std::make_pair(i, *iter); }
        bool operator!=(const iterator &rhs) { return iter != rhs.iter; }
    };
    iterator begin() { return {0, ch.begin()}; }
    iterator end() { return {int(ch.size()), ch.end()}; }
};

struct TrieNodeUM : std::unordered_map<int, int> {
    int fail;
    TrieNodeUM(int = 0) : fail(0) {}
    int Goto(int d) { return count(d) ? (*this)[d] : 0; }
    void setch(int d, int i) { (*this)[d] = i; }
};

int c2i0aA(char c) { return c-'a';}

template <typename T>
vector<int> kmp_table(const T &s) {
    int n = s.size(), k = 0;
    vector<int> p(n);
    for (int i = 1; i < n; ++i) {
        while (k > 0 && !(s[i] == s[k])) k = p[k - 1];
        if (s[i] == s[k]) k++;
        p[i] = k;
    }
    return p;
}

vector<int> kmp(const string  &s, const string  &t) { 
    vector<int> res, p = kmp_table(s);
    int n = s.size(), m = t.size(), k = 0;
    for (int i = 0; i < m; ++i) {
        while (k && (k == n || !(t[i] == s[k]))) k = p[k - 1];
        if (t[i] == s[k]) k++;
        if (k == n) res.push_back(i - n + 1);
    }
    return res;
}

void ac_yyf(int tt) {
    rd(n);
    DSU d(n);
    // trie<'a', 27> emt;
    vector<int> a(n);
    AhoCorasick<TrieNodeFL, c2i0aA> tmp(27);
    vector<AhoCorasick<TrieNodeFL, c2i0aA>> t(n,tmp);
    vector<string> b(n);
    vector<vector<int>> g(n);
    f0(n){
        rd(b[i]);
        t[i].add(b[i]);
        t[i].build();
        g[i].push_back(i);
    } 
    rd(q);

    char ch=char('a'+26);

    f0(q){
        int op;
        cin>>op;
        if(op==1){
            int u,v;
            rd(u,v);
            u--,v--;
            if(!d.same(u,v)){
                u=d.get(u),v=d.get(v);
                if(sz(b[u])>sz(b[v])) {
                    for(auto&ss:g[v]){
                        g[u].push_back(ss);
                        string s1;
                        s1+=ch;
                        s1+=b[ss];
                        t[u].add(s1);
                    }
                    d.p[v]=u;
                    g[v].clear();
                }else{
                    for(auto&ss:g[u]){
                        g[v].push_back(ss);
                    }
                    g[u].clear();
                    d.p[u]=v;
                    // t[v].build();
                }
            }
        }else{
            int u;
            string s1;
            rd(u,s1);
            u--;
            u=d.get(u);
            int ans=0;
            for(auto&s:g[u]){
                auto p =kmp(b[s],s1);
                ans+=sz(p);
            }
            wt(ans,nl);
        }
    }
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
