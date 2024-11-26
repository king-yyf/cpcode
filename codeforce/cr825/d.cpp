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

void solve(int tt) {
    rd(n,s);
    int x=0,y=0;
    each(c,s)if(c=='0')x++;else y++;
    if(x%2!=0||(y%2!=0)){
    	cout<<"-1\n";
    	return;
    }
    if(x==0||y==0){
    	cout<<"0\n";
    	f1(n)cout<<i<<" \n"[i==n];
    	return;
    }

    auto get_last=[&](char c){
    	int p=2*n-1;
    	while(p>=0&&s[p]!=c)p--;
    	return p;
    };

    auto get_first=[&](char c){
    	int p=0;
    	while(p<2*n&&s[p]!=c)p++;
    	return p;
    };

    if(s[0]=='1'){
    	int r=get_last('1'),l=get_first('0');
    	
    	swap(s[l],s[r]);
    	vector<int> v;
    	int x0=0,x1=0;
    	string s1,s2;
    	for(int i=0;i<2*n;++i){
    		if(s[0]=='0'){
    			if(x1==0) {
    				if(x0>0){
    					 x0--;
    					 s2+=s[i];
    				}
    				else {
    					s[1]+=s[i];
    					x0++;
    					v.push_back(i+1);
    				}
    			}else{
    				s1+=s[i];
    				x0++;
    				v.push_back(i+1);
    			}
    		}else{
    			if(x0==0){
    				if(x1>0){
    					x1--;
    					s[2]+=s[i];
    				}
    				else{
    					s[1]+=s[i];
    					x1++;
    					v.push_back(i+1);
    				}
    			}else{
    				s1+=s[i];
    				x1++;
    				v.push_back(i+1);
    			}
    		}
    	}
    	if(s1!=s2){
    		cout<<"-1\n";
    	}else{
    		cout<<"2 ";
	    	int mn=min(l+1,r+1),mx=max(l+1,r+1);
	    	cout<<mn<<" "<<mx<<"\n";
	    	wt(v);
    	}
    	
    }else{
    	int r=get_last('0'),l=get_first('1');
    	swap(s[l],s[r]);
    	vector<int> v;
    	int x0=0,x1=0;
    	string s1,s2;
    	for(int i=0;i<2*n;++i){
    		if(s[0]=='0'){
    			if(x1==0) {
    				if(x0>0){
    					 x0--;
    					 s2+=s[i];
    				}
    				else {
    					s[1]+=s[i];
    					x0++;
    					v.push_back(i+1);
    				}
    			}else{
    				s1+=s[i];
    				x0++;
    				v.push_back(i+1);
    			}
    		}else{
    			if(x0==0){
    				if(x1>0){
    					x1--;
    					s[2]+=s[i];
    				}
    				else{
    					s[1]+=s[i];
    					x1++;
    					v.push_back(i+1);
    				}
    			}else{
    				s1+=s[i];
    				x1++;
    				v.push_back(i+1);
    			}
    		}
    	}
    	if(s1!=s2){
    		cout<<"-1\n";
    	}else{
    		cout<<"2 ";
	    	int mn=min(l+1,r+1),mx=max(l+1,r+1);
	    	cout<<mn<<" "<<mx<<"\n";
	    	wt(v);
    	}
    }

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
