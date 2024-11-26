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
const int N = 2e5 + 5;

int n, m, q;
int x, y, k;
string s, t;

void solve(int tt) {
    cin>>n;
    vector<int> a(n);
    rd(a);
    if(n==1){
    	cout<<"Yes\n";
    	cout<<"0\n";
    	return;
    }
    if(n==2){
    	if(a[0]!=a[1]){
    		cout<<"No\n";
    	}else{
    		cout<<"Yes\n";
			cout<<"-1 1\n";
    	}
    	return;
    }
    int cnt=0;
    for(int i=0;i<n;++i){
    	if(a[i]==-1){
    		cnt++;
    	}else{
    		if(cnt>0)cnt--;
    	}
    }
    if(cnt==0 || cnt==n){
    	cout<<"No\n";
    	return;
    }
    cnt=0;
    for(int i=0;i<n;++i){
    	if(a[i]==1){
    		cnt++;
    	}else{
    		if(cnt>0)cnt--;
    	}
    }
    if(cnt==0 || cnt==n){
    	cout<<"No\n";
    	return;
    }
    vector<long long> ans(n);

    auto get=[&](int l, int r){
    	long long t=0;
    	long long c=0;
    	for(int i=l;i<=r;++i){
    		c+=a[i]*t;
    		t++;
    	}
    	return c;
    };

    if(a[n-1]==1){
    	int idx=n+1,cnt=0;
    	for(int i=n-1;i>=0;--i){
    		if(a[i]==1){
    			cnt++;
    		}else{
    			cnt--;
    		}
    		if(cnt<0){
    			idx=i;
    			break;
    		}
    	}
    	long long s1=get(idx+1,n-1);

    	long long s=0;

    	for(int i=0;i<idx;++i){
    		ans[i]=i;
    		s+=a[i]*i;
    	}

    	ans[idx]=max((long long)idx,s+s1);
		s+=ans[idx]*a[idx];
		for(int i=idx+1;i<n;++i){
			ans[i]=ans[i-1]+1;
			s+=ans[i]*a[i];
		}
		if(s<0) {
			ans[n-1]=ans[n-1]-s;
		}
    }else{
    	int idx=n+1,cnt=0;
    	for(int i=n-1;i>=0;--i){
    		if(a[i]==-1){
    			cnt++;
    		}else{
    			cnt--;
    		}
    		if(cnt<0){
    			idx=i;
    			break;
    		}
    	}
    	long long s1=get(idx+1,n-1);

    	long long s=0;

    	for(int i=0;i<idx;++i){
    		ans[i]=i;
    		s+=a[i]*i;
    	}

    	ans[idx]=max((long long)idx,-(s+s1));
		s+=ans[idx]*a[idx];
		for(int i=idx+1;i<n;++i){
			ans[i]=ans[i-1]+1;
			s+=ans[i]*a[i];
		}
		if(s>0) {
			ans[n-1]=ans[n-1]+s;
		}
    }
    cout<<"Yes\n";
    wt(ans);
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
