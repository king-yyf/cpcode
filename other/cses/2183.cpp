#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    sort(a.begin(), a.end());
    long long lst = 1;
    for (int i = 0; i < n; ++i) {
    	if (a[i] > lst) {
    		cout << lst << '\n';
    		return 0;
    	}
    	lst += a[i];
    }
    cout << lst << "\n";

    return 0;
}
