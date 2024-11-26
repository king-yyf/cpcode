#include <bits/stdc++.h>
using namespace std;

int fun2(long long n){
	return sqt(n-1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long int x=1000000000000000000;

    int t=0;
    while(t<1e6){
    	
    	int x1=fun(x),x2=fun2(x);
    	if(x1!=x2){
    		cout<<x<<" " <<x1<<" " << x2<<'\n';
            return 0;
    	}
    	x--;
    	t++;
    }

    cout<<"ok\n";



    return 0;
}
