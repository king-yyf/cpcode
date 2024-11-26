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

vector<int> get_ans(vector<int> &v, vector<int> &w, int m) {
	int n = v.size();
	vector<int> f(m + 1), cnt(n);
	vector p(n + 1, vector<bool>(m + 1));
	for (int i = 0; i < n; ++i) {
		for (int j = v[i]; j <= m; ++j) {
			if (f[j] < f[j - v[i]] + w[i]) {
				f[j] = f[j - v[i]] + w[i];
				p[i + 1][j] = true;
			}
		}
	}
	for (int i = n, j = m; i > 0 && j > 0; ) {
		if (p[i][j]) {
			cnt[i - 1] ++;
			j -= v[i - 1];
		}else i--;
	}
	return cnt;
};

void ac_yyf(int tt) {
    rd(n);
    vector<int> v{20,25,28};
    vector<int> w{30,50,70};
    cout << 34*28+25+20<<"\n";
    cout<<33*70+50*3<<"\n";
    cout<<34*70+50+30<<"\n";
    auto c = get_ans(v, w, n);
	cout<<"85%:"<<c[2]<<'\n';
	cout<<"75%:"<<c[1]<<'\n';
	cout<<"65%:"<<c[0]<<'\n';
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
