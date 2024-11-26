#include <bits/stdc++.h>
using namespace std;

// https://vjudge.net/problem/CSES-1145

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }
    vector<int> res;

    for (int i = 0; i < n; ++i) {
    	auto it = lower_bound(res.begin(), res.end(), a[i]);
    	if (it == res.end()) res.push_back(a[i]);
    	else *it = a[i];
    }

    cout << (int)res.size() << '\n';

    return 0;
}
