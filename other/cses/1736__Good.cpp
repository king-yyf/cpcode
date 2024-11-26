#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n,q;
    cin>>n>>q;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin>>nums[i];	
    }

    for(int i=0;i<q;++i){
    	int t,a,b;
    	cin>>t>>a>>b;
    	a--,b--;
    	if(t==1){
    		for(int j=a,k=1;j<=b;++j,k++){
    			nums[j]+=k;
    		}
    	}else{
    		long long s=0;
    		for(int j=a;j<=b;++j){
    			s+=nums[j];
    		}
    		cout<<s<<'\n';
    	}
    }

    return 0;
}
