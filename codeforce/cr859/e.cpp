// #include <bits/stdc++.h>
// using namespace std;

// using ll = long long;
// #define all(c) (c).begin(), (c).end()
// #define rall(x) (x).rbegin(), (x).rend() 
// #define sz(x) (int)(x).size()
// #define f0(e) for(int i = 0; i < (e); ++i)
// #define f1(e) for(int i = 1; i <= (e); ++i)
// #define f2(i,e) for(int i = 0; i < (e); ++i)
// #define rev(a) reverse((a).begin(), (a).end())
// #define each(x,a) for(auto& x : a)
// #define mst(a,x) memset(a, x, sizeof(a))
// #define yn(cond) cout << ((cond) ? "Yes" : "No") << "\n";
// #define YN(cond) cout << ((cond) ? "YES" : "NO") << "\n";
// mt19937 mrand(random_device{}()); 
// int rng(int x) { return mrand() % x;}
// long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
// template<class t,class u> bool cmx(t &a, u b){return a < b ? a = b, 1 : 0;}
// template<class t,class u> bool cmn(t &a, u b){return b < a ? a = b, 1 : 0;}
// template<class T> void rd(T& x) {cin >> x;}
// template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
// template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
// template<class A> void wt(A x) { cout << x;}
// template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
// template<class A> void wt(vector<A>& x) {for(int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];}
// template<class A> void dbg(A x) { cout << x << " ";}
// template<class H, class... T> void dbg(const H& h, const T&... t) { dbg(h); dbg(t...);}
// template<class A> void dbg(vector<vector<A>>& x) {each(c,x)wt(c);}
// template<class A, class T> void dbg(map<A,T>& x) {for(auto&[k,v]:x){cout<<"("<<k<<": "<<v<<"), ";}cout<<"\n";}

// const int mod = 1e9+7; // 998244353;
// const double PI = acos(-1.0);
// const int N = 2e5 + 5;

// int n, m, q;
// int x, y, k;
// string s, t;

// void ac_yyf(int tt) {
//     cin >> n;
//     vector<int> a(n);
//     for (int i = 0; i < n; ++i) {
//     	cin >> a[i];
//     }
//     vector<int> b;
//     int c=0;
//     for(int i=0;i<25;++i){
//     	b.clear();
//     	long long x=0;
//     	for(int j=1;j<=n;++j){
//     		if(j&(1<<i)){
//     			b.push_back(j);
//     			x+=a[j-1];
//     		}
//     	}
//     	int m=sz(b);
//     	if(m==0)continue;
//     	cout<<"? "<<sz(b)<<" ";
//     	for(int k=0;k<m;++k){
//     		if(k<m-1)cout<<b[k]<<' ';
//     		else cout<<b[k]<<endl;
//     	}
//     	long long s;
//     	cin>>s;
//     	if(s>x){
//     		c=c|(1<<i);
//     	}
//     }
//     cout<<"! "<<c<<endl;

// }

// int main() {
//     // ios::sync_with_stdio(false); cin.tie(nullptr);
//     // cout << fixed << setprecision(10);

//     int T = 1;
//     cin >> T;
//     for (int cas = 1; cas <= T; ++cas) {
//         ac_yyf(cas);
//     }

//     return 0;
// }
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

void ac_yyf(int tt) {
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    vector<long long> s(n+1);
    f0(n)s[i+1]=s[i]+a[i];
    int l=0,r=n-1,cnt;
    long long s1;
    while(l<=r){
        int md=(l+r)/2;
        s1=s[md+1]-s[l];
        cout<<"? "<<md-l+1<<' ';
        for(int i=l;i<=md;++i){
            cout<<i+1<<" \n"[i==md];
        }
        cin>>x;
        if(x!=s1){
            cnt=md+1;
            r=md-1;
        }else l=md+1;
    }
    cout<<"! "<<cnt<<endl;

}

int main() {
    // ios::sync_with_stdio(false); cin.tie(nullptr);
    // cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int cas = 1; cas <= T; ++cas) {
        ac_yyf(cas);
    }

    return 0;
}

