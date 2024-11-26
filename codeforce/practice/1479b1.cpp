#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a) {
	for (int x : a) cout << x << ' ';
		cout << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n), p(n), nxt(n, -1);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    	a[i]--;
    }
    iota(p.begin(), p.end(), 0);

    for (int i = n - 1; i >= 0; --i) {
    	nxt[i] = p[a[i]];
    	p[a[i]] = i;
    }
    
    vector<int> b, c;
    for (int i = 0; i < n; ++i) {
    	if (b.size() == 0) b.push_back(a[i]);
    	else if(c.size() == 0) c.push_back(a[i]); 
    	else if (a[i] == b.back()) c.push_back(a[i]);
    	else if(a[i] == c.back()) b.push_back(a[i]);
    	else if(nxt[b.back()] < nxt[c.back()]) b.push_back(a[i]);
    	else c.push_back(a[i]);
    }

    auto get = [&](vector<int> &x) {
    	int ans = (x.size() > 0);
    	for (int i = 1; i < x.size(); ++i) 
    		if (x[i] != x[i - 1]) ans++;
    	return ans;
    };
    cout << get(b) + get(c) << '\n';
    return 0;
}
