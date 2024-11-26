#include <bits/stdc++.h>
using namespace std;
/*
链接：https://ac.nowcoder.com/acm/contest/51458/D
来源：牛客网

x魂是一款深受acmer喜爱的立直麻将游戏，在x魂中，认为不点两面听牌的牌是比较安全的，本题需要你求出在只有万子的x魂中，有几种牌是比较安全的。

具体来说，每张牌上有一个数字，数字范围在11到mm之间。场上还有一个对手的牌河，对手的牌河中有若干张对手已经打出的牌。定义比较安全牌为：该牌上写有的数字xx满足x-3x−3或x+3x+3至少在对手牌河里出现过一次。

请你求出，在mm种牌中有几种牌是比较安全的。

对手的牌河初始为空，对手会不断向牌河中加入或移出一张牌共qq次，你需要在每次对手操作后都给出当前状况下的答案。
*/

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define yn(cond) cout << ((cond) ? "Yes" : "No") << "\n";
#define YN(cond) cout << ((cond) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
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
const double PI = acos(-1.0);
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

template <typename T>
struct FenwickTree {
    int n;
    vector<T> a;
    static int lg(unsigned x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}
    FenwickTree(int n) : n(n), a(n) {}
    FenwickTree(vector<T> &A) : FenwickTree((int)A.size()) {
        for (int i = 0; i < n; ++i) add(i, A[i]);
    }
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) a[i - 1] += v;
    }
    T sum(int x) {
        T ans = 0;
        for (int i = min(x + 1, n); i > 0; i -= i & -i) ans += a[i - 1];
        return ans;
    }
    T sum(int l, int r) { //sum[l..r]
        return l <= r ? sum(r) - sum(l - 1) : 0; 
    }
    T get(int x) const {   // 0 <= x < n, get a[x] in O(1), Equivalent to sum(x, x).
        T s = a[x];
        int y = x + 1;
        y -= y & -y;
        while (x != y) s -= a[x - 1], x -= x & -x;
        return s;
    }
    void set(int x, T v) {  // 0 <= x < n, set a[x] = v
        add(x, v - get(x));
    }
    int kth(T k) const {
        if (k < T()) return -1;
        int x = 0;
        for (int i = 1 << lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i, k -= a[x - 1];
            }
        }
        return x;
    }
};


void ac_yyf(int tt) {
    rd(m,q);
    int cnt=0;
    map<int,int>mp;
    vector<int> a(m+1);
    FenwickTree<int> f(m+1);
    while(q--){
    	rd(y,x);
    	if(y==1){
    		if(x-3>=1){
    			if(a[x-3]==0) f.set(x-3,1);
    			a[x-3]++;
    		}
    		if(x+3<=m){
    			if(a[x+3]==0) f.set(x+3,1);
    			a[x+3]++;
    		}
    		cout<<f.sum(m)<<"\n";
    	}else{
    		if(x-3>=1){
    			a[x-3]--;
    			if(a[x-3]==0) f.set(x-3,0);
    			
    		}
    		if(x+3<=m){
    			a[x+3]--;
    			if(a[x+3]==0) f.set(x+3,0);
    			
    		}
    		cout<<f.sum(m)<<"\n";
    	}
    }
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
