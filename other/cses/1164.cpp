#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-1164

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n;
    cin >> n;
    vector<array<int,3>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;	
    }
    sort(a.begin(), a.end(), [&](auto &x, auto &y){
    	if (x[0] != y[0]) return x[0] < y[0];
    	return x[1] < y[1];
    });

    priority_queue<pair<int,int> , vector<pair<int,int> >, greater<pair<int,int> >> q;

    vector<int> p(n);
    p[a[0][2]] = 1;
    q.push({a[0][1], 1});
    int cnt = 1;
    for (int i = 1; i < n; ++i) {
    	auto [k, v] = q.top();
    	if (a[i][0] > k) {
    		q.pop();
    		p[a[i][2]] = v;
    	} else {
    		p[a[i][2]] = ++cnt;
    	}
        q.push({a[i][1], p[a[i][2]]});
    }

    cout << cnt << '\n';

    for (int i = 0; i < n; ++i) {
        cout << p[i] << " \n"[i == n - 1];	
    }

    return 0;
}
