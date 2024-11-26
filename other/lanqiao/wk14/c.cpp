#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    string s;
    cin >> n >> s;

    int m;
    cin >> m;

    vector<int> v(n);

    for (int i = 0; i < n - 1; ++i) {
    	if (s[i] == '1' && s[i + 1] == '0') {
    		v[i] = 1;
    	}
    }

    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
    	pref[i + 1] = pref[i] + v[i];
    }

    for (int i = 0; i < m; ++i) {
    	int x, y;
    	cin >> x >> y;
    	x--, y--;
    	cout << pref[y] - pref[x] << '\n';
    }

    return 0;
}
