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

class Solution {
public:
    int maxPartitionsAfterOperations(string s, int k) {
        if(k==26)return 1;
        int n=sz(s);
        vector<int> dpl(n),dpr(n+1);
        vector<int> sl(n),sr(n);
        vector<int> ml(n),mr(n);
        vector<int> dl(n),dr(n),t(n);
        set<char> st;
        bool x=0;
        for(int i=0,cnt=1,msk=0;i<n;++i){
            if(st.count(s[i])&&sz(st)==k){
                dl[i]=1;
            }
            if(sz(st)==k&&!st.count(s[i])){
                cnt++;st.clear();x=false;msk=0;
            }
            if(st.count(s[i]))x=1;
            st.insert(s[i]);
            msk|=(1<<(s[i]-'a'));
            ml[i]=msk;dpl[i]=cnt;
            sl[i]=sz(st);
            if(sz(st)==k-1&&i+1<n&&!st.count(s[i+1])){
                t[i]=x;
            }
        }
        st.clear();
        for(int i=n-1,cnt=1,msk=0;i>=0;i--){
            if(st.count(s[i])&&sz(st)==k)dr[i]=1;
            if(sz(st)==k&&!st.count(s[i])){
                cnt++;st.clear();msk=0;
            }
            st.insert(s[i]);
            msk|=(1<<(s[i]-'a'));
            mr[i]=msk;dpr[i]=cnt;sr[i]=sz(st);
        }
        int c=dpl[n-1];
        f0(n){
            if(sl[i]==k&&dl[i]){
                int tmp=dpl[i]+dpr[i];
                if(dr[i]&&(ml[i]|mr[i])!=(1<<26)-1)tmp++;
                cmx(c,tmp);
            }
            if(t[i])cmx(c,dpl[i]+dpr[i+1]);
        }
        return c;
    }
};

// class Solution {
// public:
//     int maxPartitionsAfterOperations(string s, int k) {
//         if (k == 26) return 1;
//         vector<char> c(s.begin(), s.end());
//         int n = s.length();

//         vector<int> dpl(n), dpr(n+1);
//         vector<int> sizel(n), sizer(n);
//         vector<int> maskL(n), maskR(n);
//         vector<bool> dupl(n), dupr(n);
//         vector<bool> t(n);
//         unordered_set<char> set;
//         bool x = false;

//         for (int i = 0, cnt = 1, mask = 0; i < n; i++) {
//             if (set.count(c[i]) && set.size() == k) dupl[i] = true;
//             if (set.size() == k && !set.count(c[i])) {
//                 cnt++;
//                 set.clear();
//                 x = false;
//                 mask = 0;
//             }
//             if (set.count(c[i])) x = true;
//             set.insert(c[i]);
//             mask |= 1<<(c[i]-'a');
//             maskL[i] = mask;
//             dpl[i] = cnt;
//             sizel[i] = set.size();

//             if (set.size() == k-1 && i+1<n && !set.count(c[i+1])) {
//                 t[i] = x;
//             }
//         }
        
//         set.clear();
        
//         for (int i = n-1, cnt = 1, mask = 0; i >= 0; i--) {
//             if (set.count(c[i]) && set.size() == k) dupr[i] = true;
//             if (set.size() == k && !set.count(c[i])) {
//                 cnt++;
//                 set.clear();
//                 mask = 0;
//             }
            
//             set.insert(c[i]);
            
//             mask |= 1<<(c[i]-'a');
            
//             maskR[i] = mask;
            
//             dpr[i] = cnt;
            
//             sizer[i] = set.size();
//         }
        
//         int re = dpl[n-1];
        
//         for (int i=0; i<n; i++) {
//             if (sizel[i]==k && dupl[i]) {
//                 int tmp=dpl[i]+dpr[i];
                
//                 if(dupr[i] && (maskL[i]|maskR[i])!=(1<<26)-1) tmp++;
                
//                 re=max(re,tmp);
                
//                 if(t[il]) re=max(re,dpl[i]+dpr[i+1]);
                
//                 return re;
                
//     }
// };


void ac_yyf(int tt) {
    Solution so;
    string s;
    int k;
    cin>>s>>k;
    cout<<so.maxPartitionsAfterOperations(s,k)<<nl;
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
