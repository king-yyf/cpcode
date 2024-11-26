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

/*
//chatgpt
def game(n, m, p):
    if n == 1:
        # 剩余一个糖果，当前轮到的人无法取走，所以他会输掉比赛
        return False

    if p == 0:
        # 当前轮到的是 Alice
        if m >= n:
            # Alice 可以取走所有剩余的糖果，她会赢得比赛
            return True
        if m >= 2 and game(n - m, m, 1):
            # Alice 有连取机会，并且选择连续取两次糖果，递归判断下一轮 Bob 的情况
            return True
        if game(n - 1, m, 1):
            # Alice 没有连取机会，取走一个糖果，递归判断下一轮 Bob 的情况
            return True
        return False

    else:
        # 当前轮到的是 Bob
        if m >= n:
            # Bob 可以取走所有剩余的糖果，他会赢得比赛
            return False
        if m >= 2 and game(n - m, m, 0):
            # Bob 有连取机会，并且选择连续取两次糖果，递归判断下一轮 Alice 的情况
            return False
        if game(n - 1, m, 0):
            # Bob 没有连取机会，取走一个糖果，递归判断下一轮 Alice 的情况
            return False
        return True

# 示例输入
n = 10  # 糖果总数
m = 3   # 最多可以取走的糖果数
p = 0   # 硬币结果，0 表示正面，1 表示反面

# 判断谁会取得胜利
if game(n, m, p):
    print("Alice 胜利")
else:
    print("Bob 胜利")

*/

bool get(int n, int m, int p, bool vis) {
    if(n<=1)return 0;
	if(p==0){ // 先手连取
        if(!vis) {
            if(n>1&&n<=2*m+1) return 1;

            for(int i=1;i<=min(n,m);++i){
                if(!get(n-i,m,1,0)) return 1;
            }
            for(int i=m+1;i<=min(n,2*m);++i){
                if(!get(n-i,m,1,1)) return 1;
            }
        }else{
            if(n>1&&n<=m+1) return 1;

            for(int i=1;i<=min(n,m);++i){
                if(!get(n-i,m,1,0)) return 1;
            }
        }
        return 0;
    }else{
        if(n>1&&n<=m+1)return 1;
        for(int i=1;i<=min(n,m);++i){
            if(!get(n-i,m,0,0)) return 1;
        }
        return 0;
    }
}

bool ac_yyf(int tt) {
	// vector a(10,vector<int>(10));
	// vector b(10,vector<int>(10));
    // for(int i=1;i<=10;++i){
    // 	for(int j=1;j<=10;++j){
    // 		a[i-1][j-1]=get(i,j,0,0);
    // 		b[i-1][j-1]=get(i,j,1,0);
    // 	}
    // }
    // wt(a);
    // wt(b);
    int p;
    rd(n,m,p);
    if(p==0){
        if(n==1)return 0;
        return 1;
    }

    if(n==1) return 0;
    return n<=m+1;

}

int main() {
    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        // ac_yyf(cas);
        cout << ( ac_yyf(cas) ? "XiaoNian" : "YangQiShaoNian") << '\n';
        // cout << ( ac_yyf(cas) ? "YES" : "NO") << '\n';
    }
    return 0;
}
