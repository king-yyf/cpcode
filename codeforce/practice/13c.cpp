#include<bits/stdc++.h>
using namespace std;

long long minOperations(vector<int> &a) {
    int n = a.size();
    vector<long long> b(n);
    for (int i = 0; i < n; ++i){
        b[i] = a[i];
    }
    sort(b.begin(), b.end());
    b.erase(unique(begin(b), end(b)), end(b));
    int m = b.size();
    vector<long long> f(n + 1, 1e18);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1) f[j] = min(f[j - 1], abs(a[0] - b[j - 1]));
            else if(j == 1) 
                f[j] = f[j] + abs(a[i - 1] - b[0]);
            else f[j] = min(f[j - 1], f[j] + abs(a[i - 1] - b[j - 1]));
        } 
    }
    long long ans = f[1];
    for (int i = 1; i <= n; ++i)
        ans = min(ans, f[i]);
    return ans;
}

int main() {
	int n; 
	cin >> n;
	vector<int> a(n);
	for (auto &x : a) 
		cin >> x;
	cout << minOperations(a) << "\n";
}