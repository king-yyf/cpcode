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

struct Sieve {
    vector<int> min_fact, primes;
    int N;
    Sieve(int n): N(n), min_fact(n + 1) {
        for (int d = 2; d <= N; d++) {
            if (!min_fact[d]) {
                min_fact[d] = d;
                primes.push_back(d);
            }
            for (const auto &p : primes) {
                if (p > min_fact[d] or d * 1ll * p > N) break;
                min_fact[d * p] = p;
            }
        }
    }
    bool is_prime(int x) {
        if (x < N + 1) return min_fact[x] == x;
        assert(N * 1ll * N >= x);
        for (const auto &p : primes) if (x % p == 0) return false;
        return true;
    }
    template <class T> map<T, int> factorize(T x) const {
        map<T, int> ret;
        for (const auto &p : primes) {
            if (x < T(N + 1)) break;
            while (!(x % p)) x /= p, ret[p]++;
        }
        if (x >= T(N + 1)) ret[x]++, x = 1;
        while (x > 1) ret[min_fact[x]]++, x /= min_fact[x];
        return ret;
    }
    template <class T> vector<T> divisors(T x) const {
        vector<T> ret{1};
        for (const auto p : factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                for (T a = 1, d = 1; d <= p.second; d++) {
                    a *= p.first;
                    ret.push_back(ret[i] * a);
                }
            }
        }
        // sort(ret.begin(), ret.end()); // if need sort
        return ret; 
    }
    template <class T> map<T, T> euler_of_divisors(T x) const {
        assert(x >= 1);
        map<T, T> ret; ret[1] = 1;
        vector<T> divs{1};
        for (auto p : factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                ret[divs[i] * p.first] = ret[divs[i]] * (p.first - 1);
                divs.push_back(divs[i] * p.first);
                for (T a = divs[i] * p.first, d = 1; d < p.second; a *= p.first, d++) {
                    ret[a * p.first] = ret[a] * p.first;
                    divs.push_back(a * p.first);
                }
            }
        }
        return ret;
    }
    vector<int> moebius_table() const {
        vector<int> ret(N + 1);
        for (unsigned i = 1; i <= N; i++) {
            if (i == 1) ret[i] = 1;
            else if ((i / min_fact[i]) % min_fact[i] == 0) ret[i] = 0;
            else ret[i] = -ret[i / min_fact[i]];
        }
        return ret;
    }
};

Sieve s(N);
void ac_yyf(int tt) {
    rd(n,k);
    // if(n==1){
    //     if(s.is_prime(k)){
    //         wt(1,nl);
    //     }else{
    //         wt(0,nl);
    //     }
    //     return;
    // }

    

    // 能凑出多少个2

    if(k<=2*n) {
        int d = 2*n-k; // cnt of 1
        wt(d*1ll*d,nl);
        return;
    }

    // 1.全偶数，分值为0
    if((k%2==0)){
        wt(0,nl);
        return;
    }

    if(n==1){

        wt(0,nl);

    }else if(n==2){
        if(k==5){
            wt(1,nl);
        }else{
            wt(0,nl);
        }
    }else{
        if(k==2*n+1){
            wt(2,nl);
        }else{
            wt(0,nl);
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
