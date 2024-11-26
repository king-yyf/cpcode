#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://projecteuler.net/problem=9

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    long long s = 0;

    int n = 1000;

    for (int i = 0; i <= n; ++i) {
    	for (int j = i + 1; j <= n; ++j) {
    		int k = n - j - i;
    		if (j < k && i * i + j * j == k * k) {
    			cout << i * 1ll * j * k << '\n';
    			return 0;
    		} 
    	}
    }

    return 0;
}
