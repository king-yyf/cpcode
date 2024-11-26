#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void ac() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	int p = 0;
	for (int i = n - 1; i > 0; --i) {
		a[i] -= a[i - 1];
		if (a[i] < 0) p -= a[i];
	}
	
	cout << (p <= a[0] ? "Yes" : "No") << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
    	ac();
    }

    return 0;
}
