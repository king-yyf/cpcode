#include <bits/stdc++.h>
using namespace std;

string a[110],b[100];
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int n,m,x,y;
	cin>>n>>m;
	for(int i=0;i<n;++i)cin>>a[i];

	cin>>x>>y;
	for(int i=0;i<x;++i)
		cin>>b[i];
	int ans=0;
	for(int i=0;i+x<=n;++i){
		for(int j=0;j+y<=m;++j){
			bool ok=1;
			for(int k=0;k<x;++k){
				for(int l=0;l<y;++l){
					if(a[i+k][j+l]!=b[k][l]){
						ok=0;
						break;
					}
				}
			}
			ans+=ok;
		}
	}
	cout<<ans<<"\n";

	return 0;
}
