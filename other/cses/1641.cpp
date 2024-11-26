#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// https://vjudge.net/problem/CSES-1641

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, x; 
    cin >> n >> x;

    vector<pair<int,int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;	
    }

    sort(a.begin(), a.end());

    for (int i = 0; i < n; ++i) {
    	int l = i + 1, r = n - 1, t = x - a[i].first;

    	while (l < r) {
    		if (a[l].first + a[r].first > t) r--;
    		else if (a[l].first + a[r].first == t) {
    			cout << a[i].second + 1<< ' ' << a[l].second + 1 << ' ' << a[r].second + 1 << '\n';
    			return 0;
    		} else l++;
    	}
    }
    cout << "IMPOSSIBLE";
    return 0;
}
