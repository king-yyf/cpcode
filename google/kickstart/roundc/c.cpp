#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll);
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))

int bct(long long x){return __builtin_popcountll(x);}
int lg2(int x){return x==0?0:31-__builtin_clz(x);} //x>=0, floor(log2(x)) 
long long fbs(function<bool(long long)> f, long long& lb, long long rb) {  // first true binary search
    while(lb<rb) {
		long long mb=(lb+rb)/2;
		f(mb)?rb=mb:lb=mb+1; 
	} 
	return lb;
}
long long lbs(function<bool(long long)> f, long long& lb, long long rb) {  // last true binary search
	while(lb<rb) {
		long long mb=(lb+rb+1)/2;
		f(mb)?lb=mb:rb=mb-1; 
	} 
	return lb;
}

template<class A> void rd(vector<A>& v);  // read vector
template<class T> void rd(T& x) { cin >> x; }
template<class H, class... T> void rd(H& h, T&... t) {rd(h); rd(t...);}
template<class A> void rd(vector<A>& x) { each(a, x) rd(a);}
template<class A> void wt(A x) { cout << x;}
template<class H, class... T> void wt(const H& h, const T&... t) { wt(h); wt(t...);}
template<class A> void wt(vector<A>& x) {
    for (int i=0,n=x.size();i<n;++i) cout<<x[i]<<" \n"[i==n-1];
}
const int mod = 1e9+7; // 998244353;
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;
struct w {
	int x;  int y;
	int id;
	bool operator < (const w& o) const {
		return x<o.x;
	}
};


vector<int> antDropTime(vector<vector<int>> &ants, int L) {
    int n = ants.size();
    vector<int> ans(n), left, right;
    vector<array<int,3>> a;
    for (int i = 0; i < n; ++i) {
        a.push_back({ants[i][0], ants[i][1], i});
        if (ants[i][1] == 0) left.push_back(ants[i][0]);
        else right.push_back(ants[i][0]);
    }
  	sort(left.begin(), left.end()); 
  	sort(right.begin(), right.end());
    sort(a.begin(), a.end(), [&](auto x, auto y){return x[0] < y[0];});
    for (int i = 0, l = left.size(), r = right.size(); i < n; ++i) {
    	if (i < l) ans[a[i][2]] = left[i];
    	else ans[a[i][2]] = L - right[r + i - n];
    }
    return ans;
}
vector<int> antDropTime1(vector<vector<int>> &ants, int L) {
    int n = ants.size(), l = 0, r = n - 1;
    vector<int> ans(n);
    vector<pair<int,int>> p;
    vector<array<int,3>> a;
    for (int i = 0; i < n; ++i) {
        a.push_back({ants[i][0], ants[i][1], i});
        if (ants[i][1] == 0) p.push_back({ants[i][0], 0});
        else p.push_back({L - ants[i][0], 1});
    }
    sort(p.begin(), p.end());
    sort(a.begin(), a.end(), [&](auto x, auto y){return x[0] < y[0];});
    for (auto &[x, y]: p) {
        if (y == 0) ans[a[l++][2]] = x;
        else ans[a[r--][2]] = x;
    }
    return ans;
}

int n,m,x,y,k,q;
void solve(){
	int L;
	cin>>n>>L;
	vector<vector<int>> a(n);
	f0(n){
		cin>>x>>y;
		a[i].push_back(x);a[i].push_back(y);
	}

	auto t=antDropTime1(a,L);
	// wt("\n");
	// wt(t);
	vector<pair<int,int>> ans;
	for(int i=0;i<n;++i){
		ans.push_back({t[i],i});
	} 
	sort(all(ans));
	f0(n){
		cout<<ans[i].second+1<<" \n"[i==n-1];
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
        cout << "Case #" << case_i << ": ";
		solve();
	}
	return 0;
}
