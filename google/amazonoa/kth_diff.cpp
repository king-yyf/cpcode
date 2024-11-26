#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
	for(int x:a)cout<<x<<' ';cout<<'\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    sort(a.begin(), a.end());

    int mn = a[1] - a[0], mx = a[n - 1] - a[0];
    for (int i = 2; i < n; ++i) {
    	mn = min(mn, a[i] - a[i - 1]);
    }
    
    auto get_kth_diff = [&](long long k) {
    	int l = mn, r = mx, res = mx;
    	while (l <= r) {
    		int md = (l + r) / 2;
    		long long s = 0;
    		for (int i = 0, j = 0; i < n; ++i) {
    			while (j + 1 < n && a[j + 1] - a[i] <= md) j++;
    			s += j - i;
    			if (s >= k) break;
    		}
    		if (s >= k) {
    			res = md;
    			r = md - 1;
    		} else l = md + 1;
    	}
    	return res;
    };

    cout << get_kth_diff(k) << '\n';

    return 0;
}
