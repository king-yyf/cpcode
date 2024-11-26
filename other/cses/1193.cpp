#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,m;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin>>a[i];	
    }

    string s;

    queue<pair<int,int>> q;
    vector d(n,vector<int> (m, -1));
    vector<vector<char>> p(n,vector<char>(m)); 

    for(int i=0;i<n;++i){
    	for(int j=0;j<m;++j){
    		if(a[i][j]=='A'){
    			d[i][j]=0;
    			q.push({i,j});
    		}
    	}
    }

    while(q.size()) {
    	auto [x,y]=q.front();
    	if(a[x][y]=='B'){
    		cout<<"YES\n";
    		cout<<d[x][y]<<"\n";
    		cout<<s<<'\n';
    		return;
    	}
    	q.pop();
    	for(int i=0;i<4;++i){
    		int nx=x+dx[i],ny=y+dy[i];
    		if(nx>=0&&nx<n&&ny>=0&&ny<m&&d[nx][ny]==-1&&a[nx][ny]!='#'){
    			d[nx][ny]=d[x][y]+1;
    			q.push({nx,ny});
    		}
    	}
    }

    cout<<"NO\n";

    return 0;
}
