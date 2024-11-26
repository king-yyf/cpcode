#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void wt(vector<int> &a){
	for(int x:a)cout<<x<<' ';cout<<'\n';
}

vector<long long> cost_tree(vector<int> &a) {
    int n = a.size();
    if (n == 1) return {0ll, 0ll};
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

    long long s1 = 0, s2 = 0;
    int t1 = get_kth_diff(n - 1), t2 = get_kth_diff(n * 1ll * (n - 1) / 2 - n + 2);

    int cnt1 = 0, cnt2 = 0;
    vector<long long> pre(n + 1);
    for (int i = 0; i < n; ++i) {
    	pre[i + 1] = pre[i] + a[i];
    }
    for (int i = 0, j = 0; i < n; ++i) {
    	while (j + 1 < n && a[j + 1] - a[i] < t1) {
    		j++;
    	}
    	int x = j - i;
    	cnt1 += x;
    	s1 += pre[j + 1] - pre[i + 1] - x * 1ll * a[i];
    }
    s1 += (n - 1 - cnt1) * 1ll * t1;
    
    for (int i = 0, j = 0; i < n; ++i) {
    	while (j < n && a[j] - a[i] <= t2) j++;
    	if (j == n) break;
    	int x = n - j;
    	cnt2 += x;
    	s2 += pre[n] - pre[j] - x * 1ll * a[i];
    }
    s2 += (n - 1 - cnt2) * 1ll * t2;
    return {s1, s2};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
    	cin >> a[i];
    }

    auto p = cost_tree(a);

    cout << p[0] << ' ' << p[1] << "\n";

    return 0;
}
