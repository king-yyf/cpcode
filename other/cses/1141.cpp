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

    map<int, int> mp;
    int mx = 0, l = 0;
    for (int i = 0; i < n; ++i) {
    	if (mp.count(a[i])) {
    		l = max(l, mp[a[i]] + 1);
    	}
    	mp[a[i]] = i;
    	mx = max(mx, i - l + 1);
    }
    cout << mx << '\n';

    return 0;
}
