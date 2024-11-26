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

string lexicographicallySmallest(string s, int k) {
    int n = s.size();
    if (__builtin_popcount(n) == 1) k / = 2;
    else k = k * 2;

    if (k == 0) return s;
    if (k >= n) return "-1";

    int t = k;
    string c;
    c += s[0];

    for (int i = 1; i < n; ++i) {
        while (k > 0 && !c.empty() && s[i] < c.back()) {
            c.pop_back();
            --k;
        }
        s.push_back(s[i]);
    }
    c = c.substr(0, n - t);
    return c;
}


int maxDelectEdge(vector<int> &a, vector<vector<int>>& es) {
    int n = a.size(), target, cnt, sum = accumulate(a.begin(), a.end(), 0);
    vector<vector<int>> g(n);
    vector<int> s(n), f, p;

    for (auto & e : es) {
        g[e[0]].push_back(e[1]);
        g[e[1]].push_back(e[0]);
    }

    function<void(int, int)> dfs = [&](int u, int fa) {
        s[u] += a[u];
        for(int v : g[u]){
            if(v != fa){
                dfs(v, u);
                s[u] += s[v];
            }
        }
    };

    dfs(0, -1);  // 计算子树和

    for (int k = 1; k * k <= sum; ++k) {
        if (sum % k == 0) {
            f.push_back(k);
            if (k != sum / k) f.push_back(sum / k);
        }
    }
    sort(f.begin(), f.end());

    function<void(int, int)> dfs1 = [&](int u, int fa) {
        if (s[u] == target) {
            cnt++, p[u] = 1;
            return;
        }
        for (int v : g[u]) {
            if (v != fa) {
                dfs1(v, u);
                p[u] += p[v];
            }
        }
        if (s[u] - p[u] * target == target) cnt++, p[u]++;
    };

    for(int fac : f) {
        target = fac, cnt = 0;
        p.assign(n, 0);
        dfs1(0, -1);
        if (cnt * fac == sum) return cnt - 1;
    }
    return 0;
}

void solve() {
	int n;cin>>n;
	vector<int> a(n);
	rd(a);
	vector<vector<int>> es;
	for(int i=1;i<n;++i){
		int u,v;
		cin>>u>>v;u--,v--;
		es.push_back({u,v});
	}
	cout<<maxDelectEdge(a,es)<<"\n";
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

   	solve();

    return 0;
}
