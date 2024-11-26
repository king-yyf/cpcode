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

int n, m, q;
int x, y, k;
string s, t;

const int N = 2e5 + 2, K = 31, M = K * N;
int tr[M][2], idx, cnt[M]; 
void add(int x) {
    int p = 0;
    for (int i = K - 1; ~i; --i) {
        int b = (x >> i) & 1;
        if (!tr[p][b]) tr[p][b] = ++idx;
        cnt[p = tr[p][b]]++;
    }
}

void del(int x) {
    int p = 0;
    for (int i = K - 1; ~i; --i) 
        cnt[p = tr[p][(x >> i) & 1]]--;
}

int query(int x) {
    int p = 0, ans = 0;
    for (int i = K - 1; ~i; --i) {
        int b = (x >> i) & 1;
        ans = ans << 1;
        if (cnt[tr[p][b]]) ans++, p = tr[p][b];
        else p = tr[p][!b];
    }
    return ans;
}

void solve(int tt) {
	rd(n);
	vector<int> a(n);
	rd(a);
	sort(rall(a));

	set<int> s;
	int p=0;

	vector<int> vis(n);
	vector<int> ans;
	
	while(1){

		int mx=0,id=0;
		for(int i=0;i<n;++i){

			if(!vis[i]){
				int t=a[i]|p;
				if(t-p>mx){
					mx=t-p;
					id=i;
				}
			}
		}

		if(mx==0)break;

		vis[id]=1;
		ans.push_back(a[id]);
		p=p+mx;

	}


	for(int i=0;i<n;++i) if(!vis[i]) ans.push_back(a[i]);



	wt(ans);

}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
