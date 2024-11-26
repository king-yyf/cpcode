#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,m,x,y;
    cin>>n>>m;
    queue<pair<int,int>> q;
    vector<vector<int>> d(n,vector<int>(m,1e9));
    vector<vector<int>> da(n,vector<int>(m,-1));
    vector<string > a(n);

    for (int i = 0; i < n; ++i) {
    	cin>>a[i];
        for(int j=0;j<m;++j){
        	if(a[i][j]=='A'){
        		x=i,y=j;
        	}else if(a[i][j]=='M'){
        		q.push({i,j});
        		d[i][j]=0;
        	}
        }	
    }

    while(q.size()) {
    	auto [x,y]=q.front();
    	q.pop();
    	for(int i=0;i<4;++i){
    		int nx=x+dx[i],ny=y+dy[i];
    		if(nx>=0&&nx<n&&ny>=0&&ny<m){
    			if(a[nx][ny]!='#'&&d[nx][ny]>d[x][y]+1){
    				d[nx][ny]=d[x][y]+1;
    				q.push({nx,ny});
    			}
    		}
    	}
    }

    q=queue<pair<int,int>>();
    q.push({x,y});
    da[x][y]=0;
    while(q.size()) {
    	auto [u,v]=q.front();
    	q.pop();
    	if(u==0||u==n-1||v==0||v==m-1){
    		cout<<"YES\n";
    		return 0;
    	}
    	for(int i=0;i<4;++i){
    		int nx=u+dx[i],ny=v+dy[i];
    		if(nx>=0&&nx<n&&ny>=0&&ny<m){
    			if(a[nx][ny]!='#'&&da[nx][ny]==-1){
    				
    				if(da[u][v]+1<d[nx][ny]){
    					da[nx][ny]=da[u][v]+1;
    					q.push({nx,ny});
    				}
    				
    			}
    		}
    	}
    }
    // for (int i = 0; i < n; ++i) {
    //     for(int j=0;j<m;++j){
    //     	cout<<da[i][j]<<' ';
    //     }	
    //     cout<<'\n';
    // }

    cout<<"NO\n";

    return 0;
}
