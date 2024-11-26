#include<bits/stdc++.h>
using namespace std;

long long minOperations(vector<int> &a) {
    int n = a.size();
    vector<long long> b(n), f(n);
    for (int i = 0; i < n; ++i) {
        a[i] -= i;
        b[i] = a[i];
    }
    sort(b.begin(), b.end());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            f[j] += abs(a[i] - b[j]);
            if (j > 0 && f[j - 1] < f[j]) f[j] = f[j - 1];
        }
    }
    return f[n - 1];
}

long long minOperations2(vector<int> &a) {
    int n = a.size();
    long long ans = 0;
    priority_queue<int> q;
    for (int i = 0; i < n; ++i) {
        a[i] -= i;
        q.push(a[i]);
        if (q.top() > a[i]) {
            ans += q.top() - a[i];
            q.pop();
            q.push(a[i]);
        }
    } 
    return ans;
}


int main() {
	int n; 
	cin >> n;
	vector<int> a(n);
	for (auto &x : a) 
		cin >> x;
	cout << minOperations2(a) << "\n";
}