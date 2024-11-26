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



template <bool _Forward, typename _Iterator>
void FWT_bitxor(_Iterator first, _Iterator last) {
    const uint32_t length = last - first;
    for (uint32_t i = 1; i < length; i <<= 1)
        for (uint32_t j = 0; j < length; j += i << 1)
            for (auto it = first + j, it2 = first + j + i, end = first + j + i; it != end; ++it, ++it2) {
                auto x = *it, y = *it2;
                if constexpr (_Forward)
                    *it = x + y, *it2 = x - y;
                else
                    *it = (x + y) / 2, *it2 = (x - y) / 2;
            }
}

void ac_yyf(int tt) {
	int n,k;
	cin >> n>>k;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	
    int N = 1 << 17;
    vector<long long> cnt(N);
    for (int i = 0; i < n; ++i) {
        if (i > 0) a[i] ^= a[i - 1];
        cnt[a[i]]++;
    }
    FWT_bitxor<true, vector<long long>::iterator>(cnt.begin(), cnt.end());
    for (int i = 0; i < N; ++i) 
        cnt[i] *= cnt[i];
    FWT_bitxor<false, vector<long long>::iterator>(cnt.begin(), cnt.end());
    cnt[0] -= n;   
    for (auto &x : cnt) 
        x /= 2;
    for (int i = 0; i < n; ++i) 
        ++cnt[a[i]];  
    long long ans=0;
    for(int i=0;i<N&&i<k;++i){
    	ans+=cnt[i];
    }
    cout<<ans<<"\n";
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
