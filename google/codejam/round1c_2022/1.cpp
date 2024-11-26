#include <bits/stdc++.h>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define rall(x) (x).rbegin(), (x).rend() 
#define sz(x) (int)(x).size()
#define sor(x) sort(all(x))
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
    bool f=1;
	each(a, x) if(f==1) {wt(a); f=0;} else {cout<<' ';wt(a);}
}
const int mod = 1e9+7; // 998244353;
const long long INF = 1e18; 
const double PI=acos(-1.0);
const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 
const int fx[8]={-1, -1, 0, 1, 1, 1, 0, -1}, fy[8]={0, 1, 1, 1, 0, -1, -1, -1};
const int N = 2e5 + 5;

int n,m,x,y,k;

bool chk(string s){
	map<char,vector<int> >mp;
	int n=sz(s);
	f0(n)mp[s[i]].push_back(i);
	for(auto&[k,v]:mp){
		int m=sz(v);
		f0(m-1){
			if(v[i+1]-v[i]>1) return 0;
		}
	}
	return 1;
}

// int a[26][26],g[102][102];
void solve(){
	cin>>n;
	vector<string> v;
	string s;
	f0(n){
		cin>>s;
		v.push_back(s);
	}

	vector<string> c;

	set<int> s1;
	vector<string> d(26);
	f0(n){
		set<char> s2(all(v[i]));
		if(s2.size()==1){
			s1.insert(i);
			d[v[i][0]-'A']+=v[i];
		}
	}
	vector<int> vis(26);
	f0(n){
		if(s1.count(i)) {
			if(vis[v[i][0]-'A'])continue;
			c.push_back(d[v[i][0]-'A']);
			vis[v[i][0]-'A']=1;
		}else{
			c.push_back(v[i]);
		}
	}

	n=sz(c);
	map<int,vector<int>> mp;
	vector<int> deg(n);
	for(int i=0;i<n;++i){
		for(int j=i+1;j<n;++j){
			if(c[i][0]==c[j].back()){
				mp[j].push_back(i);
				deg[i]++;
			}
			if(c[j][0]==c[i].back()){
				mp[i].push_back(j);
				deg[j]++;
			}
		}
	}
	wt(deg);wt('\n');
	for(auto&[k,b]:mp){
		wt(k,": ");
		wt(b);wt('\n');
	}

	f0(n){
		if(mp[i].size()>1){
			wt("IMPOSSIBLE\n");
			return ;
		}
	}
	queue<int> q;
	vector<int> hs;
	f0(n){
		if(deg[i]==0){
			if(!mp.count(i)){
				hs.push_back(i);
			}
			else q.push(i);
		}
	}
	string ans;

	vector<int> res;
	while(!q.empty()){
		int t=q.front();q.pop();
		ans+=v[t];
		res.push_back(t);
		for(auto&x:mp[t]){
			q.push(x);
		}
	}
	each(x,hs)ans+=x;
	// if(res.size()+sz(hs)<n){
	// 	wt("IMPOSSIBLE\n");
	// 		return ;
	// }

	// wt(ans,'\n');
	if(chk(ans)){
		wt(ans,'\n');
	}
	else{
		wt("IMPOSSIBLE\n");
			return ;
	}
	// n=sz(c);
	// wt(c);wt('\n');
	// mst(a,0);
	// each(x,v){
	// 	int m=sz(x);
	// 	for(int i=0;i<m-1;++i){
	// 		for(int j=i+1;j<m;++j){
	// 			if(x[i]!=x[j]){
	// 				a[x[i]-'A'][x[j]-'A']=1;
	// 			}
	// 			// else{
	// 			// 	if(j-i>1){
	// 			// 		wt("IMPOSSIBLE\n");
	// 			// 		return ;
	// 			// 	}
	// 			// }
	// 		}
		
	// 	}
	// }
	// map<string,int> mp;
	// f0(n){
	// 	if(!chk(v[i])) {
	// 		wt("IMPOSSIBLE\n");
	// 		return;
	// 	}
	// }
	// f0(26){
	// 	for(int j=0;j<26;++j){
	// 		if(i!=j&&a[i][j]>0&&a[j][i]>0){
	// 			wt("IMPOSSIBLE\n");
	// 			return ;
	// 		}
	// 	}
	// }

	// mst(g,0);
	// f0(n){
	// 	for(int j=i+1;j<n;++j){
	// 		string &s1=v[i],&s2=v[j];
	// 		int n1=sz(s1),n2=sz(s2);
	// 		for(int k=0;k<n1;++k){
	// 			for(int l=0;l<n2;++l){
	// 				if(a[s1[k]-'A'][s2[l]-'A']>0){
	// 					g[i][j]=1;
	// 				}
	// 				if(a[s2[l]-'A'][s1[k]-'A']>0){
	// 					g[j][i]=1;
	// 				}
	// 			}
	// 		}
	// 	}
	// }

	// vector<int> deg(n),red(n);
	// f0(n){
	// 	int c=0,d=0;
	// 	for(int j=0;j<n;++j){
	// 		if(g[j][i]>0)c++;
	// 		if(g[i][j]>0)d++;
	// 	}
	// 	deg[i]=c;
	// 	red[i]=d;
	// }
	// queue<int> q;
	// vector<int> ed;
	// f0(n){
	// 	if(deg[i]==0&&red[i]==0){
	// 		ed.push_back(i);
	// 	}else if(deg[i]==0){
	// 		q.push(i);
	// 	}
		
	// }
	// string ans;
	// vector<int> res;
	// while(!q.empty()){
	// 	int t=q.front();q.pop();
	// 	ans+=v[t];
	// 	res.push_back(t);
	// 	for(int j=0;j<n;++j){
	// 		if(g[t][j]>0&&(--deg[j]==0)){
	// 			q.push(j);
	// 		}
	// 	}
	// }
	// // wt(sz(res),", ",sz(ed),", ",n,'\n');
	// each(x,ed) ans+=v[x];
	// if(sz(res)==n-sz(ed)){
	// 	wt(ans,'\n');
	// }
	// else wt("IMPOSSIBLE\n");
	// for(int i=0;i<n;++i){
	// 	for(int j=0;j<n;++j){
	// 		if()
	// 	}
	// }
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
