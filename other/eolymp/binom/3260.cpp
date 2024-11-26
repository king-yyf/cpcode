#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

// https://www.eolymp.com/en/problems/3260

ull gcd(ull a, ull b) {
	return (!b) ? a : gcd(b,a % b);
}

ull cnk(ull n, ull k) {
	ull c=1,t,i;
	if(k>n-k)k=n-k;
	for(int i=1;i<=k;++i){
		t=gcd(c,i);
		c=(c/t)*((n-i+1)/(i/t));
	}
	return c;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    

    int t = 0;
    ull n, k;
	    cin >> n >> k;

	    if (n < k) {
	    	cout << 0 << '\n';
	    	return 0;
	    }

	    cout << cnk(n,k)<<'\n';
    return 0;
}
