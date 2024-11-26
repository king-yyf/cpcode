#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    sort(a.begin(), a.end());

    int i = 0, j = n - 1, ans = 0;
    while (i < j) {
    	if (a[i] + a[j] <= x) {
    		i++, j--;
    		ans++;
    	}else {
    		j--;
    		ans++;
    	}
    }
    if (i == j) ans++;
    cout << ans << '\n';
    
    return 0;
}
