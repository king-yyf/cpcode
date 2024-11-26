#include <bits/stdc++.h>
using namespace std;


int longestPath(vector<vector<int>> &es) {
	int n=es.size()+1;
	vector<vector<pair<int,int>>> g(n);

	for(auto&e:es){
		g[e[0]-1].emplace_back(e[1]-1,e[2]);
		g[e[1]-1].emplace_back(e[0]-1,e[2]);
	}

	vector<int> d1(n), d2(n), p(n);
	function<void(int,int)> dfs_d = [&](int u,int fa) {
		for(auto&[v,c]:g[u]) if(v!=fa){
			dfs_d(v,u);
			int d=d1[v]+c;
			if(d>=d1[u]){
				d2[u]=d1[u],d1[u]=d,p[u]=v;
			}else if(d>d2[u]) d2[u]=d;
		}
	};

	dfs_d(0,-1);

	vector<int> up(n);
	function<void(int,int)> dfs_u = [&](int u,int fa) {
		for(auto&[v,c]:g[u]) if(v!=fa){
			if(p[u]==v){
				up[v]=max(up[u],d2[u])+c;
			} else up[v]=max(up[u],d1[u])+c;
			dfs_u(v,u);
		}
	};
	dfs_u(0,-1);
	int ans=1e9;
	for (int i = 0; i < n; ++i) {
		ans=min(ans,max(up[i],d1[i]));	
	}
	return ans;
}

int main() {
	int n;
	cin >> n;
	vector<vector<int>> es(n-1,vector<int>(3));

	for (int i = 0; i < n-1; ++i) {
		cin>>es[i][0]>>es[i][1]>>es[i][2];
	}

	cout<<longestPath(es);


}