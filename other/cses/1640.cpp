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

    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
    	if (mp.count(x - a[i])) {
    		cout << mp[x - a[i]] + 1 << ' ' << i + 1 << '\n';
    		return 0;
    	}
    	mp[a[i]] = i;
    }
    

    cout << "IMPOSSIBLE\n";

    return 0;
}
