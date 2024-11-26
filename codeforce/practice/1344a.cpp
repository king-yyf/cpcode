#include <bits/stdc++.h>
using namespace std;

using ll = long long;

bool solve() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for (int i = 0; i < n; ++i) {
	    cin >> a[i];
	    a[i] += i;
	    a[i] = (a[i] % n + n) % n;
	    b[a[i]] = 1;
	}
	return count(b.begin(), b.end(), 1) == n;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	cout << (solve() ? "YES" : "NO") << '\n';
    }

    return 0;
}
