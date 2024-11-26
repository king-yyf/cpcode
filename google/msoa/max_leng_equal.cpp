#include <bits/stdc++.h>
using namespace std;

int maxLengEqual(vector<long long> &a, vector<long long> &b) {
    int n = a.size(), m = b.size();
    long long s1 = accumulate(a.begin(), a.end(), 0ll);
    long long s2 = accumulate(b.begin(), b.end(), 0ll);
    if (s1 != s2) return -1;
    int ans = 0;
    for (int i = 0, j = 0; i < n && j < m;) {
    	if (a[i] == b[j]) {
    		ans++, i++, j++;
    	} else if(a[i] > b[j]) {
    		if (j + 1 < m) b[j + 1] += b[j];
    		j++;
    	} else {
    		if (i + 1 < n) a[i + 1] += a[i];
    		i++;
    	}
    }
    return ans;
}

int main() {
	ios::sync_with_stdio(false); 
    cin.tie(nullptr);
    cout << fixed << setprecision(10);
	int n, m;
	cin >> n;
    long long s1 = 0, s2 = 0;
	vector<long long> a(n);
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		s1 += a[i];
	}
	cin >> m;
	vector<long long> b(m);
	for (int i = 0; i < m; ++i) {
		cin >> b[i];
		s2 += b[i];
	}

	if (s1 != s2) {
		cout<<"-1\n";
		return 0;
	}
	cout << maxLengEqual(a, b) << "\n";
    return 0;
}

