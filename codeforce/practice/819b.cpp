#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T>
struct RangeGeoSum {
    int n;
    vector<T> d1, d2;
    RangeGeoSum(int N) : n(N), d1(N), d2(N) {}
    RangeGeoSum(vector<T> &A) : RangeGeoSum((int)A.size()) {
        for (int i = 0; i < n; ++i) d2[i] = A[i];
    }
    void add(int l, int r, const T a1, const T &d) { //[l,r) 首项为a1,公差为d的等差数列
        d1[l] += d;
        d2[l] += a1 - d * l;
        if (r < n) {
        	d1[r] -= d;
        	d2[r] -= a1 - d * l;
        }
    }
    vector<T> get() {
    	vector<T> ret(n);
    	for (int i = 0; i < n; ++i) {
    		ret[i] = d1[i] * i + d2[i];
    		if (i < n - 1) {
    			d1[i + 1] += d1[i];
    			d2[i + 1] += d2[i];
    		}
    	}
    	return ret;
    }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
    	cin >> p[i];
    	p[i]--;
    }

    RangeGeoSum<ll> f(n);

    for (int i = 0; i < n; ++i) {
    	if (p[i] > i) {
    		f.add(0, p[i] - i + 1, p[i] - i, -1);
	        int r = min(n, p[i] - i + n - p[i]);

	        if (p[i] - i + 1 < r) {
	        	f.add(p[i] - i + 1, r, 1, 1);
	        }

	        if (r < n) {
	        	f.add(r, n, p[i], -1);
	        }

    	} else {
    		f.add(0, n - i, i - p[i], 1);

	        int r = min(n - i + p[i] + 1, n);
	        if (n - i < r) {
	        	f.add(n - i, r, p[i], -1);
	        }

	        if (r < n) {
	        	f.add(r, n, 1, 1);
	        }
    	}
    }

    long long mn = 1e18;
    int id = -1;
    auto d = f.get();
    for (int i = 0; i < n; ++i) {
    	if (d[i] < mn) {
    		mn = d[i];
    		id = i;
    	}
    }

    cout << mn << ' ' << id << '\n';

    return 0;
}
