#include<bits/stdc++.h>
using namespace std;
const int N=1e4+10;
const long long INF = 0x3f3f3f3f;
struct E{
	int to;
	long long  cost;
	bool operator <(const E& o)const {
		return cost > o.cost;
	}
};
vector<E> g[N]; 
long long  dis[N];
int vis[N];
void dijkstra(int s){
	memset(vis, 0, sizeof vis);
	priority_queue<E> q;
	q.push({s,0}); 
	dis[s]=0;
	while(!q.empty()){
		auto t=q.top();q.pop();
		if(vis[t.to]) continue;
		vis[t.to]=1;
		for(auto&p:g[t.to]){
			if(dis[p.to]>t.cost+p.cost){
				dis[p.to]=t.cost+p.cost;
				q.push({p.to,dis[p.to]});
			}
		}
	}
}
map<pair<int,int>,int> mp;
int main(){
	int n,m,s,x,y,c;
	cin>>n>>m>>s;
	// memset(e, -1, sizeof e);
	for(int i=0;i<m;++i){
		cin>>x>>y>>c;
		if(!mp.count({x,y}))mp[{x,y}]=c;
		else mp[{x,y}]=min(mp[{x,y}],c);
	}
	for(auto&[e,cs]:mp){
		g[e.first].push_back({e.second,cs});
	}
	for(int i=1;i<=n;++i) dis[i]=2e9;
	dijkstra(s);

	for(int i=1;i<=n;++i){
		if(i==n){
			cout<<(dis[i]==INF?-1:dis[i])<<"\n";
		}else cout<<(dis[i]==INF?-1:dis[i])<<" ";
	}
	return 0;
}