#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
 
void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i) {
	    cin >> a[i];	
	}
 
	long long ans = 0;
	vector<pair<int,int>> p, q;
	for (int i = 0; i < n; ++i) {
		q.emplace_back(a[i], i);
		int k = 0;
		for (int j = 0; j < p.size(); ++j) {
			p[j].first &= a[i];
			if (p[j].first == q[k].first) {
				q[k].second = p[j].second;
			} else {
				q.emplace_back(p[j].first, p[j].second);
				k++;
			}
		}
		p = q;
		q.clear();
		for (int j = k; j >= 0; --j) {
			int l = p[j].second, r = (j > 0 ? p[j - 1].second : i + 1);
			ans += p[j].first * 1ll * (r - l);
		}
	} 
 
	cout << ans << '\n';
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
