#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int a[N];
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cout<<fixed<<setprecision(20);
	int m;
	cin>>m;
	for(int i=1;i<=m;++i){
		cin>>a[i];
	}
	int ans=0;
	for(int i=1;i<=m;++i){
		if(a[i]==-1)continue;
		int x=2*i,y=x+1;
		if(x>m) {
			ans++;
			continue;
		}
		if(y<=m && a[x]==-1&&a[y]==-1) ans++; 
	}
	cout<<ans<<"\n";
	return 0;
}
