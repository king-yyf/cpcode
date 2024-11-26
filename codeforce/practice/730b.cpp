#include <bits/stdc++.h>
using namespace std;

using ll = long long;

char query(int x, int y) {
	cout << "? " << x << ' ' << y << endl;
	char res;
	cin >> res;
	return res;
}

void solve() {
	int n;
	cin >> n;
	vector<int> a, b;
	for (int i = 0; i < n; i += 2) {
		if (i == n - 1) {
			a.push_back(n);
			b.push_back(n);
			continue;
		}
		int x = i + 1, y = i + 2;
		char op = query(x, y);
		if (op == '>') {
			swap(x, y);
		}
		a.push_back(x);
		b.push_back(y);
	}

	int mn = a[0], mx = b[0];

	for (int i = 1; i < a.size(); i ++) {
		char op = query(mn, a[i]);
		if (op == '>') {
			mn = a[i];
		}

	}

	for (int i = 1; i < b.size(); i ++) {
		char op = query(mx, b[i]);
		if (op == '<') {
			mx = b[i];
		}

	}

	cout << "! " << mn << ' ' << mx << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
    	solve();
    }

    return 0;
}
