#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/*

link: https://www.codechef.com/problems/ISS
rating: 2071
*/

void solve() {
	int k;

	vector<int> a(41);

	for (int k = 1; k <= 40; ++k) {
		int last = -1, cur = 0, s = 0;
		for (int i = 1; i <= 2 * k + 1; ++i) {
			cur = i * i + k;
			if (last != -1) {
				s += gcd(last, cur);
			}
			last = cur;
		}
		a[k] = s;
		cout << "k = " << k << ", sum = " << a[k] << "\n";
	}

	for (int k = 1; k <= 40; ++k) {
		cout << a[k] << " "[k == 40];
	}
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
