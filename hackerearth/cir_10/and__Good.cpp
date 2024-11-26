#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
	    cin >> a[i];	
	}
 
	long long ans = 0;
	
	for (int i = 0; i < n; ++i) {
		int c = a[i];
		for (int j = i; j < n; ++j) {
			c &= a[j];
			ans += c;
		}
	}
 
	cout << ans << '\n';
}
 
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	solve();
    }
 
    return 0;
}
