#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int minOperations(vector<int> &a) {
	int n = a.size(), i = 0, j = n - 1, ans = 0;
	long long x = a[0], y = a[n - 1]; 
	while (i < j) {
		if (x < y) {
			i ++;
			x += a[i];
			ans++;
		} else if (x > y) {
			j--;
			y += a[j];
			ans++;
		} else {
			i++, j--;
			x += a[i], y += a[j];
		}
	}
	return ans;
}

void sovle() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	cout << minOperations(a) << '\n';
	
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while(t--){
    	sovle();
    }

    return 0;
}
