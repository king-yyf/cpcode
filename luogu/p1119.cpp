#include<bits/stdc++.h>
using namespace std;

const int N = 210;
int a[N],f[N][N];
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int n,m;
	cin>>n>>m;
	for(int i=0;i<n;++i){
		cin>>a[i];
	}
	memset(f, 0x3f, sizeof f);
	int q,x,y,c,t;
	for(int i=0;i<m;++i){
		cin>>x>>y>>c;
		f[x][y]=f[y][x]=c;
	}
	
	for (int i = 0; i < n; ++i) {
		f[i][i]=0;
	}
	cin>>q;
	int k = 0;
	while(q--){
		cin>>x>>y>>t;
		while(k<n&&a[k]<=t){
			for(int i=0;i<n;++i){
				for(int j=0;j<n;++j){
					if(f[i][j]>f[i][k]+f[k][j]){
						f[i][j]=f[j][i]=f[i][k]+f[k][j];
					}
				}
			}
			k++;
		}

		int tmp = max(a[x], a[y]);
		if(tmp > t) {
			cout << -1 << "\n";
			continue;
		}
	
		cout<<(f[x][y]==0x3f3f3f3f?-1:f[x][y])<<"\n";
	}
}