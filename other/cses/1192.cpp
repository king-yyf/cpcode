#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1}; 

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,m;
    cin>>n>>m;
    int c=0;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin>>a[i];	
    }
    function<void(int, int)> dfs = [&](int x, int y) {
    	a[x][y]='*';
    	for(int i=0;i<4;++i){
    		int nx=x+dx[i],ny=y+dy[i];
    		if(nx>=0&&nx<n&&ny>=0&&ny<m&&a[nx][ny]=='.') dfs(nx,ny);
    	}
    };
    for (int i = 0; i < n; ++i) {
        for(int j=0;j<m;++j){
        	if(a[i][j]=='.'){
        		dfs(i,j);
        		c++;
        	}
        }	
    }
    cout<<c;

    return 0;
}
