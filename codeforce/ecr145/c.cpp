#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define Sm(a) accumulate((a).begin(), (a).end() , 0ll)
#define Mn(a) (*min_element((a).begin(), (a).end()))
#define Mx(a) (*max_element((a).begin(), (a).end()))
#define rev(a) reverse((a).begin(), (a).end())
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

vector<int> get_ans(vector<int> &v, vector<int> &w, int m) {
    int n = v.size();
    vector<int> f(m + 1, 1e8), cnt(n);
    vector p(n + 1, vector<bool>(m + 1));
    f[0]=0;
    for (int i = n-1; i >=0; --i) {
        for (int j = m; j >= w[i]; --j) {
            if (f[j] >=f[j - w[i]] + v[i]) {
                f[j] = f[j - w[i]] + v[i];
                p[i + 1][j] = true;
            }
        }
    }
    for (int i = 1, j = m; i > 0 && j > 0; ) {
        if (p[i][j]) {
            cnt[i - 1] ++;
            j -= w[i - 1];
        }else i++;
    }
    return cnt;
};

void ac_yyf11(int tt) {
    rd(n,k);
    if(k==0){
        f0(n)cout<<(-i)<<" \n"[i==n-1];
        return;
    }
    vector<int> v,w;
    f1(n){
        int m=(n+i-1)/i;
        int x=i*(i+1)/2;
        // v.push_back(x);
        // w.push_back(i);
        f2(j,m){
            v.push_back(x);
            w.push_back(i);
        }
    }
    // m=sz(v);
    // vector f(m+1,vector<int>(k+1,1e9));
    // f[0][0]=0;
    // f1(m){
    //     for(int j=0;j<=k;++j){
    //         f[i][j]=f[i-1][j];
    //         if(j>=w[i])
    //             f[i][j]=min(f[i][j],f[i-1][j-w[i-1]]+v[i-1]);
    //     }
    // }
    
    // wt(c);

    if(k*2<n*(n+1)/2) {
        auto c=get_ans(v,w,k);
        vector<int> p;
        int s=0;
        f0(n){
            if(c[i]>0){
                // for(int j=0;j<c[i];++j){
                    
                // }
                for(int k=0;k<=i;++k){
                        p.push_back(1);

                    }
                    p.push_back(0);
            }
        }
        if(sz(p)&&p.back()==0)p.pop_back();

        s=Sm(p);
        s=-2*s-1;
        each(x,p)if(x==0)x=s;
        while(sz(p)<n)p.push_back(s);
        wt(p);
    }else{
        k=n*(n+1)/2-k;
        auto c=get_ans(v,w,k);
        vector<int> p;
        int s=0;
        f0(n){
            if(c[i]>0){
                for(int j=0;j<c[i];++j){
                    for(int k=0;k<=i;++k){
                        p.push_back(1);

                    }
                    p.push_back(0);
                }
            }
        }
        if(sz(p)&&p.back()==0)p.pop_back();

        s=Sm(p);
        s=-2*s-1;
        each(x,p)if(x==0)x=s;
        while(sz(p)<n)p.push_back(s);
        each(x,p)x=-x;
        wt(p);
    }
}

void ac_yyf(int tt) {
    rd(n,k);
    if(k==0){
        f1(n)cout<<(-i)<<" \n"[i==n];
        return;
    }
    vector<int> p(n);
    for(int i=n-1;i>=0;--i){
        if(k>=i+1){
            p[n-1-i]=1;
            k-=i+1;
        }
    }

    int s1=0,s2=0;
    for(int i=n-1;i>=0;--i){
        if(p[i]==0){
            p[i]=-s2-1;
            s1+=p[i];
        }else{
            p[i]=-s1+3;
            s2+=p[i];
        }
    }

    wt(p);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}
