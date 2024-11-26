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
#define fi first
#define se second
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

int n, m, q;
int x, y, k;
string s, t;

long long countSubarrays(vector<int>& a, int x, int y) {
    int n = a.size(), m = *max_element(a.begin(), a.end());

    vector<vector<int>> p(m + 1);
    for (int i = 0; i < n; ++i) 
        p[a[i]].push_back(i);

    vector<int> lmx(n, -1), rmx(n, n), lmn(n, -1), rmn(n, n), ind(m + 1), sk;

    auto cal_left = [&](function<bool(int,int)> f, vector<int> &v) {
    	sk.clear();
    	for (int i = n - 1; i >= 0; --i) {
	        while (sk.size() && f(a[i],a[sk.back()])) {
	            v[sk.back()] = i;
	            sk.pop_back();
	        }
	        sk.push_back(i);
	    }
    };

    auto cal_right = [&](function<bool(int,int)> f, vector<int> &v) {
    	sk.clear();
    	for (int i = 0; i < n; ++i) {
	        while(sk.size() && f(a[i],a[sk.back()])) {
	            v[sk.back()] = i;
	            sk.pop_back();
	        }
	        sk.push_back(i);
	    }
    };

    auto get = [&](int x1, int y1, int x2, int y2) {
        return max(0, min(y1, y2) - max(x1, x2));
    };

    cal_left(greater<int>(), lmx);
    cal_left(less<int>(), lmn);
    cal_right(greater_equal<int>(), rmx);
    cal_right(less<int>(), rmn);

    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == y) {
            if (ind[x] >= 1) {
                int j = p[x][ind[x] - 1];
                ans += get(lmx[i], i, lmn[j], j) * 1ll * get(i, rmx[i], j, rmn[j]);
            }
            if (ind[x] < p[x].size()) {
                int j = p[x][ind[x]];
                int t = ind[x] >= 1 ? p[x][ind[x] - 1] : -1;
                ans += get(max(t, lmx[i]), i, lmn[j], j) * 1ll * get(i, rmx[i], j, rmn[j]);
            }
        }
        ind[a[i]]++;
    }
    return ans;
}

void solve(int tt) {
    vector<int> a={1,3,5,2,7,5};
    int x=1,y=5;
    auto c=countSubarrays(a,x,y);
    wt(c,'\n');
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
