#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1630

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<pair<int,int> > a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;	
    }

    sort(a.begin(), a.end());

    long long ans = 0, t = 0;

    for (auto &[x, y] : a) {
    	t += x;
    	ans += y - t;
    }

    cout << ans << '\n';

    return 0;
}
