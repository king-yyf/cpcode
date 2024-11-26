#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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
#define yn(o) cout << ((o) ? "Yes" : "No") << "\n";
#define YN(o) cout << ((o) ? "YES" : "NO") << "\n";
mt19937 mrand(random_device{}()); 
int rng(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int pct(long long x) {return __builtin_popcountll(x);} // 二进制中1的个数
int lg(int x) {return x == 0 ? -1 : 31 - __builtin_clz(x);}  // floor(log(2)),x的最高位1
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
const char nl = '\n';
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

int minIndex(int n, vector<int> &a) {
     map<int,int> mp;
     for (int x : a){
        mp[x]++;
     }
     int mx = 0, res = -1;
     for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = 2; j <= 5; ++j) {
            cnt += mp[a[i] * j];
        }
        if (cnt > mx) {
            mx = cnt;
            res = i;
        }
     }
     return res;

}

int minLength(int n, int k, vector<int> &a) {
    int l=1,r=n,ans=n;
    unordered_map<int,int> mp;
    for(int x:a){
        mp[x]++;
    }
    int cnt = 0;
    for (auto it:mp){
        if(it.second>k)cnt++;
    }
    if(cnt==0)return 0;
    while(l<=r){
        int md=(l+r)/2;
        int c=cnt;
        auto m1=mp;
        bool o=0;
        for(int i=0;i<n;++i){
            if(i>=md){
                m1[a[i-md]]++;
                if(m1[a[i-md]]==k+1){
                    c++;
                }
            }
            unordered_map[a[i]]--;
            if(m1[a[i]]==k){
                c--;
            }
            if(c==0){
                o=1;break;
            }
        }
        if(o){
            ans=md;r=md-1;
        }else l=md+1;
    }
    return ans;
}

unordered_map<,> 

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout << fixed << setprecision(10);
    int n=7;
    vector<int> a{18, 20, 7, 3, 14, 20, 5};
    auto p=minIndex(n,a);
    wt(p);
    return 0;
}
