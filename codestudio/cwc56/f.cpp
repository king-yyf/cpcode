#include<bits/stdc++.h>

using namespace std;
const int mx_n = 200005;
int sf[mx_n];
void init() {
	for(int i = 1; i < mx_n; ++i) sf[i] = i;
	for(int i = 2; i * i < mx_n; ++i) {
		if(sf[i] == i) {
			int s = i * i;
			for(int j = i * i; j < mx_n; j += i) {
				for(; sf[j] % s == 0; sf[j] /= s);
			}
		}
	}
}

int a[mx_n], b[mx_n];
int main() {
	init();
	int t;
	cin >> t;
  	assert(t <= 1e5);
  	int tn = 0;
	while(t--) {
		int n;
		cin >> n;
	  	assert(n <= 2e5);
	  	tn += n;
	  	assert(tn <= 2e5);
		for(int i = 1; i <= n; ++i) {
			cin >> a[i];
		  	assert(a[i] >= 0 and a[i] <= INT_MAX);
			b[i] = a[i];
		}
		sort(b+1, b+n+1);
		vector<vector<int>> before(n+1), after(n+1);
		for(int i = 1; i <= n; ++i) {
			before[sf[i]].push_back(a[i]);
			after[sf[i]].push_back(b[i]);
		}
		bool ok = true;
		for(int i = 1; i <= n; ++i) {
			sort(before[i].begin(), before[i].end());
			if(before[i] != after[i]) {
				ok = false;
				break;
			}
		}
		
		cout << (ok? "YES": "NO") << endl;
	}
	
	
	return 0;
}