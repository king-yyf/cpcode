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
    	a[i]--;
    }
    

    sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
    	cout << a[i] << " \n"[i == n - 1];
    }

    return 0;
}
