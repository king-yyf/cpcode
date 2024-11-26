#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    ll sum = 0;

    for (int i = 0; i < n; ++i) {
    	sum += a[i];
    }

    if (sum == 0) {
    	cout << 'Y' << '\n';
    	return 0;
    } 

    int mx = -1E9, mn = 1e9;

    for (int i = 0; i < n; ++i) {
    	mx = max(mx, a[i]);
    	mn = min(mn, a[i]);
    }

    if (sum > 0 and sum - mx > 0) {
    	cout << 'N' << '\n';
    	return 0;
    } 

    if (sum < 0 and sum + mn < 0) {
    	cout << 'N' << '\n';
    	return 0;
    } 

    cout << 'Y' << '\n';

    return 0;
}
