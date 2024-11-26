#include <bits/stdc++.h>
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
int n, m, q;
int x, y, k;
string s, t;


template <typename T, int bit_len = numeric_limits<make_unsigned_t<T>>::digits>
class XorTrie {
    using U = make_unsigned_t<T>;
    struct Node {
        int siz;
        Node *ch[2] {nullptr, nullptr};
        Node() : siz(0) {}
        ~Node() { delete ch[0]; delete ch[1];}
        inline Node* get_or_new(bool b) noexcept { if (is_absent(b)) ch[b] = new Node(); return ch[b];}
        inline Node* operator[](bool b) const noexcept { return ch[b]; }
        inline bool is_absent (bool b) const noexcept { return ch[b] == nullptr; }
        inline bool is_present(bool b) const noexcept { return ch[b] != nullptr; }
        static inline int size(const Node *const node) noexcept { return node == nullptr ? 0 : node->siz; }
        inline void update_size() noexcept { siz = size(ch[0]) + size(ch[1]); }
    };
    public:
        XorTrie() : root(new Node) {}
        ~XorTrie() { delete root; }

        inline int size() const noexcept { return Node::size(root); }
        inline bool empty() const noexcept { return size() == 0; }

        int add(const U val, const int num = 1) noexcept {
            if (num == 0) return 0;
            Node *cur = root;
            cur->siz += num;
            for (int i = bit_len; i --> 0;) {
                cur = cur->get_or_new(bit(val, i));
                cur->siz += num;
            }
            return cur->siz;
        }
        int del(const U val, const int num = 1) noexcept {
            if (num == 0) return 0;
            return del(root, bit_len - 1, val, num);
        }
        int clear(const U val) noexcept { return del(val, numeric_limits<int>::max());}
        int prefix_count(const U val, const unsigned int l) const noexcept {
            Node *cur = root;
            for (int i = bit_len; i --> l;) {
                if (cur == nullptr) return 0;
                cur = (*cur)[bit(val, i)];
            }
            return Node::size(cur);
        }
        inline int count(const U val) const noexcept { return prefix_count(val, 0); }
        inline bool contains(const U val) const noexcept { return count(val) > 0; }

        inline U xor_kth_min(const U x, const int k) const {
            assert(0 <= k and k < size());
            return xor_kth_ele<false>(x, k);
        }
        inline U xor_kth_max(const U x, const int k) const {
            assert(0 <= k and k < size());
            return xor_kth_ele<true>(x, k);
        }
        inline U xor_min(const U x) const { return xor_kth_min(x, 0);  }
        inline U xor_max(const U x) const { return xor_kth_max(x, 0); }
        int xor_count_lt(const U x, const U val) const noexcept {
            int res = 0;
            Node *cur = root;
            for (int i = bit_len - 1; i >= 0; --i) {
                if (cur == nullptr) break;
                bool bx = bit(x, i);
                bool bv = bit(x ^ val, i);
                if (bx != bv) {
                    res += Node::size((*cur)[bx]);
                }
                cur = (*cur)[bv];
            }
            return res;
        }
        inline int xor_count_leq(const U x, const U val) const noexcept { return xor_count_lt(x, val) + count(val); }
        inline int xor_count_gt (const U x, const U val) const noexcept { return size() - xor_count_leq(x, val);    }
        inline int xor_count_geq(const U x, const U val) const noexcept { return size() - xor_count_lt(x, val);     }
        inline U xor_lower(const U x, const U val, const U default_value = ~U(0)) const noexcept {
            int k = size() - xor_count_geq(x, val) - 1;
            return k < 0 ? default_value : xor_kth_ele(x, k);
        }
        inline U xor_floor(const U x, const U val, const U default_value = ~U(0)) const noexcept {
            int k = size() - xor_count_gt(x, val) - 1;
            return k < 0 ? default_value : xor_kth_ele(x, k);
        }
        inline U xor_higher(const U x, const U val, const U default_value = ~U(0)) const noexcept {
            int k = xor_count_leq(x, val);
            return k == size() ? default_value : xor_kth_ele(x, k);
        }
        inline U xor_ceil(const U x, const U val, const U default_value = ~U(0)) const noexcept {
            int k = xor_count_lt(x, val);
            return k == size() ? default_value : xor_kth_ele(x, k);
        }

        inline U kth_min(const int k) const { return xor_kth_min(0, k); }
        inline U min() const { return xor_kth_min(0, 0); }
        inline U max() const { return xor_kth_min(~U(0), 0); }
        inline int count_lt (const U val) const noexcept { return xor_count_lt(0, val);  }
        inline int count_leq(const U val) const noexcept { return xor_count_leq(0, val); }
        inline int count_gt (const U val) const noexcept { return xor_count_gt(0, val);  }
        inline int count_geq(const U val) const noexcept { return xor_count_geq(0, val); }
        inline U lower (const U val, const U default_value = ~U(0)) const noexcept { return xor_lower (0, val, default_value); }
        inline U floor (const U val, const U default_value = ~U(0)) const noexcept { return xor_floor (0, val, default_value); }
        inline U higher(const U val, const U default_value = ~U(0)) const noexcept { return xor_higher(0, val, default_value); }
        inline U ceil  (const U val, const U default_value = ~U(0)) const noexcept { return xor_ceil  (0, val, default_value); }
    private:
        Node *const root;
        static constexpr bool bit(const U x, const int i) noexcept { return (x >> i) & 1;}
        int del(Node *cur, const int k, const U val, const int num) {
            if (k == -1) {
                int removed = std::min(cur->siz, num);
                cur->siz -= removed;
                return removed;
            }
            bool b = bit(val, k);
            if (cur->is_absent(b)) return 0;
            int removed = del((*cur)[b], k - 1, val, num);
            cur->update_size();
            return removed;
        }
        template <bool is_max_query = false>
        U xor_kth_ele(const U x, const int k) const noexcept {
            U res = 0;
            int rest = k;
            Node *cur = root;
            for (int i = bit_len - 1; i >= 0; --i) {
                bool b = is_max_query ^ bit(x, i);
                int sz = Node::size((*cur)[b]);
                if (sz <= rest) rest -= sz, b = not b;
                res |= U(b) << i;
                cur = (*cur)[b];
            }
            return x ^ res;
        }
};

void ac_yyf(int tt) {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    XorTrie<int,8> t;
    t.add(0);
    int s=0,c=0;
    f0(n){
        s^=a[i];
        cmx(c,t.xor_max(s));
        t.add(s);
    }
    wt(c,nl);
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
