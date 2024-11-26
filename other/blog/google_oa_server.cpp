#include <bits/stdc++.h>
using namespace std;

using ll = long long;

long long minCost(vector<int> &a, vector<int> &b) {
	int n = a.size();
	vector<long long> f(n);
	f[0] = a[0];
	for (int i = 1; i < n; ++i) {
		// f[i] = f[i - 1] + a[i];
		// if (i > 0) {
		// 	f[i] = min(f[i], f[i - 2] + b[i - 1] + b[i]);
		// }
		// if (i > 1) {
		// 	f[i] = min(f[i], f[i - 3] + b[i - 2] + b[i - 1] + b[i])
		// }
	}
}

void solve() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for(int &x : a) {
		cin >> x;
	}
	for(int &x : b) {
		cin >> x;
	}
	cout << minCost(a, b) << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin>>t;
    while(t--){
    	solve();
    }

    return 0;
}
