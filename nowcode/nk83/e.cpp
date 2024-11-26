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

template<typename T>
struct FenwickTree2D{
    vector<vector<T>> tr;
    int n, m;
    FenwickTree2D(int N, int M) : n(N), m(M), tr(N, vector<T>(M, 0)){}

    void add(int x, int y, int val){ // 0 <= x < n, 0 <= y < m
        for(int i = x + 1; i <= n; i += i & -i)
            for(int j = y + 1; j <= m; j += j & -j)
                tr[i - 1][j - 1] += val;
    }
 
    T ask(int x, int y) { // 0 <= x < n, 0 <= y < m
        T ret = 0;
        for(int i = x + 1; i > 0; i -= i & -i)
            for(int j = y + 1; j > 0; j -= j & -j)
                ret += tr[i - 1][j - 1];
        return ret;
    }
    T ask(int x1, int y1, int x2, int y2) {  // sum[x1..x2, y1..y2]
        return ask(x2, y2) - ask(x2, y1 - 1) - ask(x1 - 1, y2) + ask(x1 - 1, y1 - 1);
    }
};

void ac_yyf(int tt) {
    rd(n,m);
    string s="",t="";
    vector<vector<char>> a(n,vector<char>(m));
    rd(a);
    map<pair<int,int>,int> m1,m2;
    int idx=0;
    for(int i=0;i<n;++i){
        if(i%2==0){
            for(int j=0;j<m;++j){
                m1[{i,j}]=idx++;
                s+=a[i][j];
            }
        }else{
            for(int j=m-1;j>=0;--j){
                m1[{i,j}]=idx++;
                s+=a[i][j];
            }
        }
    }
    idx=0;
    for(int i=0;i<m;++i){
        if(i%2==0){
            for(int j=0;j<n;++j){
                m2[{j,i}]=idx++;
                t+=a[j][i];
            }
        }else{
            for(int j=n-1;j>=0;--j){
                m2[{j,i}]=idx++;
                t+=a[j][i];
            }
        }
    }

    // dbg(s);

    // dbg(t);

    rd(q);

    FenwickTree2D<int> f(26,n*m);
    FenwickTree2D<int> g(26,n*m);

    for(int i=0;i<n*m;++i){
        f.add(s[i]-'a',i,1);
        g.add(t[i]-'a',i,1);
    }

    int k=n*m;

    f0(q){
        int op;
        cin>>op;
        if(op==1){
            int x,y;
            char ch;
            rd(x,y,ch);
            x--,y--;
            

            int p1=m1[{x,y}],p2=m2[{x,y}];

            f.add(s[p1]-'a',p1,-1);
            g.add(t[p2]-'a',p2,-1);

            t[p2]=ch;
            s[p1]=ch;

            f.add(s[p1]-'a',p1,1);
            g.add(t[p2]-'a',p2,1);


        }else if(op==2){
            int x,y;
            rd(x,y);
            x--,y--;

            int id=m1[{x,y}];

            int d=s[id]-'a';

            //  T ask(int x1, int y1, int x2, int y2) {  // sum[x1..x2, y1..y2]
            //     return ask(x2, y2) - ask(x2, y1 - 1) - ask(x1 - 1, y2) + ask(x1 - 1, y1 - 1);
            // }

            int l=1,r=k-id,c=l;
            while(l<=r){
                int md=(l+r)/2;
                if(f.ask(d,id,d,id+md-1)==md){
                    c=md;l=md+1;
                }else r=md-1;
            }
            wt(c,nl);


        }else{
            int x,y;
            rd(x,y);
            x--,y--;

            int id=m2[{x,y}];

            int d=t[id]-'a';

            //  T ask(int x1, int y1, int x2, int y2) {  // sum[x1..x2, y1..y2]
            //     return ask(x2, y2) - ask(x2, y1 - 1) - ask(x1 - 1, y2) + ask(x1 - 1, y1 - 1);
            // }
            // dbg(t,nl);
            // dbg(id,d,k,nl);

            int l=1,r=k-id,c=l;
            // dbg(l,r,c,nl);
            while(l<=r){
                int md=(l+r)/2;

                // dbg("md=",md,"id+md-1=",id+md-1,g.ask(d,id,d,id+md-1),nl);
                if(g.ask(d,id,d,id+md-1)==md){
                    c=md;l=md+1;
                }else r=md-1;
            }
            wt(c,nl);
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
