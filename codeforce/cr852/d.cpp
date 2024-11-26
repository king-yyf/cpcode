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

vector<long long> countPermulationMEX(vector<int> &a) {
    int l, r, n = a.size();
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[a[i]] = i;
        if (a[i] == 0) l = i, r = i;
    }
    
    vector<long long> ans(n);
    ans[n - 1] = 1;
    for (int i = 0; i < n - 1; ++i) {
        int k = p[i + 1];
        if (l > k) {
            ans[i] = (n - r) * 1ll * (l - k);
            l = k;
        } else if (r < k) {
            ans[i] = (l + 1ll) * (k - r);
            r = k;
        }
    }
    return ans;
}

void ac_yyf(int tt) {
    rd(n);
    vector<int> p(n),q(n);
    f0(n){
    	cin>>p[i];p[i]--;
    }
    f0(n){
    	cin>>q[i];q[i]--;
    }
    int l1,r1,l2,r2;
    vector<int> p1(n),p2(n);
    for (int i = 0; i < n; ++i) {
        p1[p[i]] = i;
        if (p[i] == 0) l1 = i, r1 = i;
        p2[q[i]] = i;
        if (q[i] == 0) l2 = i, r2 = i;
    }

    auto get=[&](int l1, int r1, int l2, int r2)->long long {
        return max(0,min(r1, r2) - max(l1, l2) + 1);
    };

    auto g1=[&](int x)->long long{return x*(x+1ll)/2;};

    long long ans=1;
    if(l1==l2){
        ans+=g1(l1);ans+=g1(n-1-l1);
    }else{
        int mn=min(l1,l2),mx=max(l1,l2);
        ans+=g1(mn);ans+=g1(mx-mn-1);ans+=g1(n-1-mx);
    }
    for (int i = 1; i < n; ++i) {
        int k1 = p1[i],k2 = p2[i];

        if (l1 > k1) {
            if (l2 > k2) {
                ans += get(k1+1,l1,k2+1,l2)*1ll*get(r1,n-1,r2,n-1);
            } else if (r2 < k2) {
                ans += get(k1+1,l1,0,l2)*1ll*get(r1,n-1,r2,k2-1);
            }

        } else if (r1 < k1) {
            if (l2 > k2) {
                ans += get(0,l1,k2+1,l2)*1ll*get(r1,k1-1,r2,n-1);
            } else if (r2 < k2) {
                ans += get(0,l1,0,l2)*1ll*get(r1,k1-1,r2,k2-1);
            }
        }
        if(l1>k1)l1=k1;
        else if(r1<k1)r1=k1;
        if(l2>k2)l2=k2;
        else if(r2<k2)r2=k2;
        
    }
    cout<<ans<<"\n";
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
