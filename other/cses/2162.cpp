#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// https://vjudge.net/problem/CSES-2162

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
    	q.push(i);
    }

    for (int i = 1; i <= n; ++i) {
    	q.push(q.front());
    	q.pop();
    	cout << q.front() << " \n"[i == n];
    	q.pop();
    }

    return 0;
}
