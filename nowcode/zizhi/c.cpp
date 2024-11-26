#include <bits/stdc++.h>
using namespace std;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;


template<class T>
using ordered_set = tree<T,null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

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

int n,m,x,y,k,q;
void solve(){
	ordered_set<int> s1,s2;
	cin>>q;

	unordered_map<int, int> mp;
	map<int,int> c1,c2;

	unordered_map<int, int> b1,b2;
	map<int, int> e1,e2;

	f0(q){
        int x,y;
		cin>>k;
		if(k==1){
			cin>>x;
			if(mp.count(x)){
				mp[x]++;
			} else {
				mp[x]++;
				if(x%2==0){
					x=x/2;
					int p=s1.order_of_key(x);
					p--;
					if(p>=0){
						y=*s1.find_by_order(p);
						if(y==x-1){
							int l=y-e1[y]+1,r=y,len=e1[y];
							// b1.erase(l);
							e1.erase(r);
							b1[l]=len+1;
							e1[x]=len+1;
							c1[len]--;
							if(c1[len]==0) c1.erase(len);
							c1[len+1]++;
						}else{
							b1[x]=e1[x]=1;
							c1[1]++;
						}
					}else{
						b1[x]=e1[x]=1;
						c1[1]++;
					}

					if(p<sz(s1)-1){
						p++;
						y=*s1.find_by_order(p);
						if(y==x+1){
							int l=x-e1[x]+1,r=y+b1[y]-1,len=e1[x]+b1[y];
							c1[e1[x]]--;
							if(c1[e1[x]]==0) c1.erase(e1[x]);
							c1[b1[y]]--;
							if(c1[b1[y]]==0) c1.erase(b1[y]);
							e1.erase(x);
							b1.erase(y);
							b1[l]=len;
							e1[r]=len;
							c1[len]++;
						}
					}
					s1.insert(x);
				}
				else {
					x=x/2;
					int p=s2.order_of_key(x);
					p--;
					if(p>=0){
						y=*s2.find_by_order(p);
						if(y==x-1){
							int l=y-e2[y]+1,r=y,len=e2[y];
							// b2.erase(l);
							e2.erase(r);
							b2[l]=len+1;
							e2[x]=len+1;
							c2[len]--;
							if(c2[len]==0) c2.erase(len);
							c2[len+1]++;
							
						}else{
							b2[x]=e2[x]=1;
							c2[1]++;
						}
					}else{
						b2[x]=e2[x]=1;
						c2[1]++;
					}

					if(p<sz(s2)-1){
						p++;
						y=*s2.find_by_order(p);
						if(y==x+1){
							int l=x-e2[x]+1,r=y+b2[y]-1,len=e2[x]+b2[y];
							c2[e2[x]]--;
							if(c2[e2[x]]==0) c2.erase(e2[x]);
							c2[b2[y]]--;
							if(c2[b2[y]]==0) c2.erase(b2[y]);
							e2.erase(x);
							b2.erase(y);
							b2[l]=len;
							e2[r]=len;
							c2[len]++;
						}
					}
					s2.insert(x);
				}
			}
		}else if(k==2){
            cin>>x;
			if(mp.count(x)){
				mp[x]--;
				if(mp[x]==0){
                    mp.erase(x);
					if(x%2==0) {
						x/=2;
						if(b1.count(x)){
							int l=x,r=x+b1[x]-1,len=b1[x];
							b1.erase(l);
							e1.erase(r);
							c1[len]--;
							if(c1[len]==0)c1.erase(len);
							l++;
							if(r>=l){
								b1[l]=len-1;
								e1[r]=len-1;
								c1[len-1]++;
							}
						}else if(e1.count(x)){
							int l=x-e1[x]+1,r=x,len=e1[x];
							b1.erase(l);
							e1.erase(r);
							c1[len]--;
							if(c1[len]==0)c1.erase(len);
							r--;
							if(r>=l){
								b1[l]=len-1;
								e1[r]=len-1;
								c1[len-1]++;
							}
						}else{
							auto it=e1.lower_bound(x);
							auto r=it->first, len=it->second;
							int l=r-len+1;
							c1[len]--;
							if(c1[len]==0)c1.erase(len);
							b1[l]=x-l;
							e1[x-1]=x-l;
							b1[x+1]=r-x;
							e1[r]=r-x;
							c1[x-l]++;
							c1[r-x]++;
							
						}

						s1.erase(x);
					}
					else {
						x/=2;
						if(b2.count(x)){
							int l=x,r=x+b2[x]-1,len=b2[x];
							b2.erase(l);
							e2.erase(r);
							c2[len]--;
							if(c2[len]==0)c2.erase(len);
							l++;
							if(r>=l){
								b2[l]=len-1;
								e2[r]=len-1;
								c2[len-1]++;
							}
						}else if(e2.count(x)){
							int l=x-e2[x]+1,r=x,len=e2[x];
							b2.erase(l);
							e2.erase(r);
							c2[len]--;
							if(c2[len]==0)c2.erase(len);
							r--;
							if(r>=l){
								b2[l]=len-1;
								e2[r]=len-1;
								c2[len-1]++;
							}
						}else{
							auto it=e2.lower_bound(x);
							auto r=it->first, len=it->second;
							int l=r-len+1;
							c2[len]--;
							if(c2[len]==0)c2.erase(len);
							b2[l]=x-l;
							e2[x-1]=x-l;
							b2[x+1]=r-x;
							e2[r]=r-x;
							c2[x-l]++;
							c2[r-x]++;
							
						}

						s2.erase(x);
					}
					
				}
			}
		}else{
			int x=0,y=0;
//             dbg("c2:\n");
//             dbg(c2);
			if(c1.size()) x=c1.rbegin()->first;
			if(c2.size()) y=c2.rbegin()->first;
			cout<<max(x,y)<<"\n";
		}
	}
}
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int T=1;
	// cin >> T;
	for (int case_i = 1; case_i <= T; ++case_i) {
		solve();
	}
	return 0;
}
