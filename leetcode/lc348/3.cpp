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

template <typename TDATA, typename TRET, typename TQUERY, typename E, typename F, typename G>
struct SegmentTree2D {
    int H, W;
    int hhead, whead;
    TDATA defaultDATA;
    TRET defaultRET;
    E merge_data;
    F data2ret;
    G merge_ret;
    int DH, DW;
    std::vector<TDATA> data;
    inline TDATA &at(int h, int w) { return data[DW * h + w]; }

    inline void _merge_w(int h, int w) {
        if (2 * w + 2 < DW)
            at(h, w) = merge_data(at(h, 2 * w + 1), at(h, 2 * w + 2));
        else if (2 * w + 2 == DW)
            at(h, w) = at(h, 2 * w + 1);
        else
            at(h, w) = defaultDATA;
    }
    inline void _merge_h(int h, int w) {
        if (2 * h + 2 < DH)
            at(h, w) = merge_data(at(2 * h + 1, w), at(2 * h + 2, w));
        else if (2 * h + 2 == DH)
            at(h, w) = at(2 * h + 1, w);
        else
            at(h, w) = defaultDATA;
    }
    SegmentTree2D(const std::vector<std::vector<TDATA>> &mat, TDATA defaultDATA, E merge_data,
                  F data2ret, G merge_ret)
        : H(mat.size()), W(mat[0].size()), defaultDATA(defaultDATA),
          defaultRET(data2ret(defaultDATA, TQUERY(0))), merge_data(merge_data), data2ret(data2ret),
          merge_ret(merge_ret) {
        int Htmp = 1, Wtmp = 1;
        while (Htmp < H) Htmp <<= 1;
        while (Wtmp < W) Wtmp <<= 1;
        hhead = Htmp - 1, whead = Wtmp - 1;
        DH = hhead + H, DW = whead + W;
        data.assign(DH * DW, defaultDATA);
        for (int h = 0; h < H; h++)
            for (int w = 0; w < W; w++) { at(hhead + h, whead + w) = mat[h][w]; }
        for (int h = DH - 1; h >= hhead; h--) {
            for (int w = whead - 1; w >= 0; w--) _merge_w(h, w);
        }
        for (int h = hhead - 1; h >= 0; h--) {
            for (int w = 0; w < DW; w++) _merge_h(h, w);
        }
    }
    void update(int h, int w, TDATA x) {
        h += hhead, w += whead;
        at(h, w) = x;
        for (int pos = h; pos;) {
            pos = (pos - 1) / 2;
            _merge_h(pos, w);
        }
        for (int iw = w; iw;) {
            iw = (iw - 1) / 2;
            for (int ih = h;;) {
                _merge_w(ih, iw);
                if (!ih) break;
                ih = (ih - 1) / 2;
            }
        }
    }
    TRET _get_h(int hl, int hr, int wl, int wr, int lo, int hi, int id_, TQUERY q) {
        if (hr <= lo or hi <= hl) return defaultRET;
        if (hl <= lo and hi <= hr) return _get_w(wl, wr, 0, whead + 1, id_, 0, q);
        return merge_ret(_get_h(hl, hr, wl, wr, lo, (lo + hi) / 2, 2 * id_ + 1, q),
                         _get_h(hl, hr, wl, wr, (lo + hi) / 2, hi, 2 * id_ + 2, q));
    }
    TRET _get_w(int wl, int wr, int lo, int hi, int id_h, int id_w, TQUERY q) {
        if (wr <= lo or hi <= wl) return defaultRET;
        if (wl <= lo and hi <= wr) return data2ret(at(id_h, id_w), q);
        return merge_ret(_get_w(wl, wr, lo, (lo + hi) / 2, id_h, 2 * id_w + 1, q),
                         _get_w(wl, wr, (lo + hi) / 2, hi, id_h, 2 * id_w + 2, q));
    }
    // [hl, hr) * [wl, wr)
    TRET get(int hl, int hr, int wl, int wr, TQUERY q) {
        return _get_h(hl, hr, wl, wr, 0, hhead + 1, 0, q);
    }
    friend std::ostream &operator<<(std::ostream &os, SegmentTree2D s) {
        os << "[SegmentTree" << s.H << "*" << s.W << "\n";
        for (int h = 0; h < s.H; h++) {
            os << "[";
            for (int w = 0; w < s.W; w++) os << s.at(h + s.hhead, w + s.whead) << ",";
            os << "]\n";
        }
        return os << "]";
    }
};

class Solution {
public:
    long long matrixSumQueries(int n, vector<vector<int>>& qs) {
        ll s=0;
        m=sz(qs);
        set<int> s1,s2;
        for(int i=m-1;i>=0;--i){
            int t=qs[i][0],x=qs[i][1],y=qs[i][2];
            if(t==0){
                if(s1.count(x)) continue;
                s+=y*1ll*(n-sz(s2));
                s1.insert(x);
            }else{
                if(s2.count(x)) continue;
                s+=y*1ll*(n-sz(s1));
                s2.insert(x);
            }
        }
        return s;
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
