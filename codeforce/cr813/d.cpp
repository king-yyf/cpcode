#include <bits/stdc++.h>
using namespace std;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define f0(e) for(int i=0;i<(e);++i)
#define f1(e) for(int i=1;i<=(e);++i)
#define f2(i,e) for(int i=0;i<(e);++i)
#define f3(i,e) for(int i=1;i<=(e);++i)
#define Sum(a) accumulate((a).begin(), (a).end() , 0ll)
#define Min(a) *std::min_element((a).begin(), (a).end())
#define Max(a) *std::max_element((a).begin(), (a).end())
#define rev(a) reverse((a).begin(), (a).end())
#define each(x,a) for(auto& x : a)
#define mst(a,x) memset(a, x, sizeof(a))
#define to_uni(a) a.erase(unique(begin(a), end(a)), end(a))
#define ln "\n";
#define fi first
#define se second
typedef long long ll;
mt19937 mrand(random_device{}()); 
int rnd(int x) { return mrand() % x;}
long long gcd(long long a,long long b) { return b?gcd(b,a%b):a;}
int bct(long long x) {return __builtin_popcountll(x);}

template<class A> void rd(vector<A>& v);  // read vector
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
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;
struct w {
    int x;  int y;
    bool operator < (const w& o) const {
        return x!=o.x ? x<o.x : y<o.y;
    }
};


template<typename T, typename less>
struct mulset_cmp {
    bool operator () (const pair<T, size_t>& x, const pair<T, size_t>& y) const {
        return less()(x.first, y.first) ? true : (less()(y.first, x.first) ? false : less()(x.second, y.second));
    }
};
 
template<typename T, typename less>
struct mulset {
    tree<pair<T, size_t>, null_type, mulset_cmp<T, less>, rb_tree_tag, tree_order_statistics_node_update> t;
    map<T, size_t> mp;

    void insert(T v) {
        t.insert({v, ++mp[v]});
    }

    void erase(T v) {
        t.erase({v, mp[v]--});
    }

    size_t order_of_key(T v) {
        return t.order_of_key({v, 0});
    }

    T find_by_order(size_t r) {
        return t.find_by_order(r)->first;
    }

    T prev(T v) {
        auto it = t.lower_bound({v, 0});
        return (--it)->first;
    }

    T next(T v) {
        return t.lower_bound({v + 1, 0})->first;
    }
};


int n,m,x,y,k,q;
void solve(int tt){
	rd(n,k);
	vector<int> a(n);
	rd(a);
	ll mx=1e9;
	if(k==n){
		cout<<mx<<"\n";
		return;
	}

	long long c=0;
	for(int  i=0;i<n-1;++i){
		long long t=min(a[i],a[i+1]);
		c=max(c,t);
	}
	map<int,int> mp;
	f0(n)mp[a[i]]++;

	if(k==1){
		long long ans=0;
		f0(n){
			long long x=0,y=0;
			if(i>0)x=max(x,min(mx,a[i-1]+0ll));
			if(i<n-1)y=max(y,min(mx,a[i+1]+0ll));
			long long t=max(x,y);
			t=max(t,c);
			mp[a[i]]--;
			if(mp[a[i]]==0){
				mp.erase(a[i]);
			}
			auto it=mp.begin();
			long long p=it->first;
			ans=max(ans,min(p*2,t));

			mp[a[i]]++;
		}
		cout<<ans<<"\n";
		return;
	}


	if(c==mx){
		sort(all(a));
		long long p=a[k];

		long long t=min(2*p,mx);	
		cout<<t<<"\n";
		return;
	}

	long long t=Max(a);


	mulset<long long, less<long long>> s1;

	each(x,a)s1.insert(x);

	if(t==mx){

		ll mn=mx;

		f0(n){
			if(a[i]==t){
				if(i>0) mn=min(a[i-1]+0ll,mn);
				if(i<n-1) mn=min(a[i+1]+0ll,mn);
			}
		}


		mp[mn]--;
		if(mp[mn]==0) mp.erase(mn);

		long long tmp=mn;

		// if(tt==2){
		// 	dbg("mn=",mn,'\n');
		// }

		k--;


		// if(tt==2){
		// 	dbg("mn=",mn,"k=",k,'\n');

		// 	dbg(mp);
		// }

		mn=-1;

		for(auto&[x,y]:mp){
			if(y<=k){
				k-=y;
				continue;
			}else{
				mn=x;
			}
		}

		mp[tmp]++;

		long long t1=min(2*mn,mx);	
		cout<<t1<<"\n";

		return;

	}


	// auto b=a;
	// sort(all(b));\


	long long ans=0;



	for(int i=0;i<n-1;++i){
		int x=a[i],y=a[i+1];

		s1.erase(x);
		s1.erase(y);
		int k1=k-2;

		long long p=s1.find_by_order(k1);
		ans=max(ans,min(2*p,mx));

		s1.insert(x);
		s1.insert(y);

	}






	// t=Min(a);

	// long long mn=mx;

	// f0(n){
	// 	if(a[i]==t){
	// 		if(i>0) mn=min(a[i-1]+0ll,mn);
	// 		if(i<n) mn=min(a[i+1]+0ll,mn);
	// 	}
	// }



	cout<<ans<<"\n";
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve(case_i);
	}
	return 0;
}
