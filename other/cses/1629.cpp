#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int,int> > a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;	
    }

    sort(a.begin(), a.end(), [&](auto &x, auto &y){
    	if (x.second != y.second) return x.second < y.second;
    	return x.first < y.first;
    });

    int ans = 0, lst = -1e9;
    for (int i = 0; i < n; ++i) {
    	if (a[i].first >= lst) {
    		ans++;
    		lst = a[i].second;
    	}
    }

    cout << ans << '\n';

    return 0;
}
