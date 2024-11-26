#include<bits/stdc++.h>
using namespace std;


vector<int> getMinMaxSubArray(vector<int> &a) {
	int n = a.size();
	vector<int> lmn(n, -1), rmn(n, n), ans(n);
	stack<int> sk;
	for (int i = 0; i < n; ++i) {
	    while(!sk.empty() && a[sk.top()] > a[i]) {
	        rmn[sk.top()] = i;
	        sk.pop();
	    }
	    if (!sk.empty()) lmn[i] = sk.top();
	    sk.push(i);
	}

	for (int i = 0; i < n; ++i) {
		int l = rmn[i] - lmn[i] - 1;
		ans[l - 1] = max(ans[l - 1], a[i]);
	}

	for (int i = n - 2; i >= 0; --i) {
		ans[i] = max(ans[i], ans[i + 1]);
	}
	return ans;
}
 
int main() {
	ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);

    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    auto ans = getMinMaxSubArray(a);
    for (int i = 0; i < n; ++i) {
    	cout << ans[i] << " \n"[i == n - 1];
    }
}
