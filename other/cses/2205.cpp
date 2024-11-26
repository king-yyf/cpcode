#include <bits/stdc++.h>
using namespace std;

using ll = long long;


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin>>n;
    int m=1<<n;
    for(int i=0;i<m;++i){
    	int x=i^(i>>1);
    	for(int j=n-1;j>=0;--j){
    		if((x>>j)&1)cout<<'1';
    		else cout<<'0';
    	}
    	cout<<'\n';
    }

    return 0;
}
