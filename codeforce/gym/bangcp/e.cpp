#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }

    vector<long long> s(n + 1);
    for (int i = 0; i < n; ++i) {
        s[i + 1] = s[i] + a[i];	
    }

    vector dp(n + 1, vector<int>(n + 1));

    for (int i = n - 1; i >= 0; --i) {
    	for (int j = i; j <= n - 1; ++j) {
    		if (j == n - 1) {
    			dp[i][j] = 1;
    		} else {
    			
    		}
    	}
    }

    return 0;
}
