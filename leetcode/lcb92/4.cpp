#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i = 0; i < (e); ++i)
#define f1(e) for(int i = 1; i <= (e); ++i)
#define f2(i,e) for(int i = 0; i < (e); ++i)
#define fr(i,a,b) for (int i=(a);i<(b);i++)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define yn(cond) if (cond) cout<<"Yes\n"; else cout << "No\n";
#define YN(cond) if (cond) cout<<"YES\n"; else cout << "NO\n";
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class T> void rd(T& x) {cin >> x;}
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
template<class A> void dbg(A x) { cout << x << " ";}
template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
template<class A> void dbg(vector<A>& x) {wt(x);}
template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

const int mod = 1e9+7; // 998244353;
const double PI = acos(-1.0);
const int dx[4]{1, 0, -1, 0}, dy[4]{0, 1, 0, -1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

class Solution {
public:
    int countPalindromes(string s) {
        int n=sz(s);
        long long ans=0;
        

        vector<vector<int>> f(n+1,vector<int>(100));
        vector<vector<int>> g(n+1,vector<int>(100));

        vector<vector<int>> p(n+1,vector<int>(10));

        for(int i=0;i<n;++i){
            for(int j=0;j<10;++j){
                int t=0;
                if(s[i]-'0'==j)t=1;
                p[i+1][j]=p[i][j]+t;
            }
        }

        for(int i=0;i<n;++i){
            int x=s[i]-'0';
            for(int k=0;k<10;++k){
                if(k==x){
                    for(int j=0;j<10;++j){
                        int id=j*10+x;
                        f[i+1][id]=f[i][id]+p[i][j];
                    }
                }else{
                    for(int j=0;j<10;++j){
                        int id=j*10+k;
                        f[i+1][id]=f[i][id];
                    }
                }
            }
            
            
        }

        for(int i=n-1;i>=0;--i){

            int x=s[i]-'0';
            for(int k=0;k<10;++k){
                if(k==x){
                    for(int j=0;j<10;++j){
                        int id=x*10+j;
                        g[i][id]=g[i+1][id]+p[n][j]-p[i+1][j];
                    }
                }else{
                    for(int j=0;j<10;++j){
                        int id=k*10+j;
                        g[i][id]=g[i+1][id];
                    }
                }
            }
            
        }

        f0(n+1){
            f2(j,11)cout<<g[i][j]<<" ";cout<<"\n";
        }


        for(int i=2;i<n-2;++i){
            for(int j=0;j<10;++j){
                for(int k=0;k<10;++k){
                    int l=j*10+k,r=k*10+j;
                    dbg("i=",i,l,r,f[i][l],g[i+1][r],'\n');
                    ans=(ans+f[i][l]*g[i+1][r])%mod;
                }
            }
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    string s="103301";
    Solution so;
    int c=so.countPalindromes(s);
    cout<<c<<"\n";

    return 0;
}
