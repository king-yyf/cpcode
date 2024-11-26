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
const int N = 305;

int n, m, q;

long long a[N];

pair<long long,int> ans[N][N]; 



struct w
{
	long long v;
	int d;
	Edge(long long  _w, int _d): w(_w), d(_d) {}
	bool operator < (const w& o) const {
		if(d!=o.d) {
			return d>o.d;
		}
		return v<o.v;
	}

};

int dis[N];
long long val[N];
void solve(int tt) {
    cin >> n;
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    vector<vector<int>> g(n);
    f0(n){
    	string s;
    	rd(s);
    	f2(j,n) {
    		if(s[j]=='Y'){
    			g[i].push_back(j);
    		}
    	}
    }

    f0(n){

    	priority_queue<w>  q;

    	mst(dis,0x3f);
    	mst(val,0);

    	q.push({i,a[i]});
    	dis[i]=0;
    	val[i]=a[i];

    	while(!q.empty()){
    		w w1=q.top();q.pop();
    		
    	}


    	for(int j=0;j<n;++j){
    		ans[i][j]={d.dis[j],d.V[j]};
    	}
    }
    int q;cin>>q;
    while(q--){
    	int x,y;
    	cin>>x>>y;
    	x--,y--;
    	if(ans[x][y].first>=0x3f3f3f3f){
			cout<<"Impossible\n";
		}else
    	cout<<ans[x][y].first<<" "<<ans[x][y].second<<"\n";
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);

    int T = 1;
    // cin >> T;
    for (int case_i = 1; case_i <= T; ++case_i) {
        solve(case_i);
    }

    return 0;
}
