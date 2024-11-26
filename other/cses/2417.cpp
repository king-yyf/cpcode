#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <class T>
struct Discrete {
    vector<T> xs;
    Discrete(const vector<T>& v) {
        xs = v;
        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());
    }
    int get(const T& x) const {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    }
    inline int operator()(const T& x) const { return get(x); }
    T operator[](int i) { return xs[i]; }
    int size() const { return xs.size(); }
};


int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n, mx = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];	
    }
    sort(a.begin(), a.end());
    vector<int> p(mx + 1);
    for (int i = 0; i < n; ++i) {
    	p[a[i]]++;
    }
    long long ans = n * (n - 1ll) / 2;
    a.erase(unique(a.begin(), a.end()), a.end());
    n = a.size();

    for (int i = 0; i < n; ++i) {
    	if (a[i] == 1) continue;
    	ans -= p[a[i]] * (p[a[i]] - 1) / 2;
    	for (int j = a[i] + a[i]; j <= mx; j += a[i]) {
    		ans -= p[a[i]] * p[j];
    	}
    }

    cout << ans << '\n';

    return 0;
}
