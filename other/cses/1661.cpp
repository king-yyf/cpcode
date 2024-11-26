#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1661

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    vector<long long> s(n + 1);
    for (int i = 0; i < n; ++i) {
        s[i + 1] = s[i] + a[i];	
    }

    map<long long, int> mp;

    long long ans = 0;

    for (int i = 0; i <= n; ++i) {
    	if (mp.count(s[i] - x)) ans+=mp[s[i] - x];
    	mp[s[i]]++;
    }
    cout << ans << '\n';

    return 0;
}
