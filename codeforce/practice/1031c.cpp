#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    ll a, b;
    cin >> a >> b;


    long long s = a + b;

    int l = 1, r = 1;

    while (r * 1ll * (r + 1) / 2 <= s) r++;
    vector<int> v1, v2;

    while (l <= r) {
    	int mid = (l + r) / 2;
    	vector<int> x, y;
    	bool o = 1;
    	int A = a, B = b;
    	for (int i = mid; i >= 1; --i) {
	    	if (A >= i) {
	    		A -= i;
	    		x.push_back(i);
	    	} else if (B >= i) {
	    		B -= i;
	    		y.push_back(i);
	    	} else {
	    		o = 0;
	    	}
    	}

    	if (o) {
    		v1 = x;
    		v2 = y;
    		l = mid + 1;
    	} else {
    		r = mid - 1;
    	}
    }

    cout << v1.size() << '\n';
    for (int x : v1) {
    	cout << x << ' ';
    }
    cout << '\n';
    cout << v2.size() << '\n';
    for (int x : v2) {
    	cout << x << ' ';
    }
    cout << '\n';

    return 0;
}
