#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;

    priority_queue<int> q;
    vector<int> pre(n + 1), nxt(n + 1), a(n + 1), ans(n);
    for (int i = 1, x; i <= n; ++i) {
    	cin >> x;
    	q.push(x);
    	a[x] = i;
    	pre[i] = i - 1;
    	nxt[i] = i + 1;
    } 

    auto del = [&](int i) {
    	pre[nxt[i]] = pre[i];
    	nxt[pre[i]] = nxt[i];
    };

    nxt[n] = 0;
    int now = 1;
    vector<bool> st(n + 1);
    while (!q.empty()) {
    	int u = q.top(); q.pop();
    	if (st[a[u]]) continue;
    	st[a[u]] = true;
    	ans[a[u] - 1] = now;
    	for (int loc = nxt[a[u]], i = 1; i <= k && loc; i++, loc = nxt[loc]) {
    		ans[loc - 1] = now, st[loc] = true;
    		del(loc);
    	}
    	for (int loc = pre[a[u]], i = 1; i <= k && loc; i++, loc = pre[loc]) {
    		ans[loc - 1] = now, st[loc] = true;
    		del(loc);
    	}
    	del(a[u]);
    	now = 3 - now;
    } 
    for (int x : ans) 
    	cout << x;
    cout << "\n";
    return 0;
}
